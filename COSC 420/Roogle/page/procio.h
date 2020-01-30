#ifndef PROCIO
#define PROCIO

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <stdarg.h>
#include "debug.h"
#include "kwtree.h"
#include "ditree.h"

static FILE* locallog;

void getFilePath(char* dir, int dirlen, int me, char** filepath) {
	int nodenumlen;
	if(me == 0)
		nodenumlen = 1;
	else
		nodenumlen = floor(log10(abs(me))) + 1;
	int pathlen = dirlen+nodenumlen+4;
	*filepath = calloc(pathlen, sizeof(char));
	strcpy(*filepath, dir);
	strcat(*filepath, "%d.txt");
	sprintf(*filepath, *filepath, me);
	if(debug) {
		char* out = calloc(pathlen+7, sizeof(char));
		strcpy(out, "(%d) ");
		strcat(out, *filepath);
		strcat(out, "\n");
		printf(out, me);
		free(out);
	}
}

bool setup_procio(time_t t) {
  int worldsize;
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldsize);

  int rank;
  if(worldsize != 0)
    MPI_Comm_rank(world, &rank);
  else
    rank = 0;

  const int dirlen = 25;
  char* dir = calloc(dirlen, sizeof(char));
  if(rank == 0) {
    struct tm tm = *localtime(&t);
    if(debug) {
      printf("System Date is: %02d/%02d/%04d\n",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
      printf("System Time is: %02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    char* dirformat = "logs/%02d-%02d-%04d_%02d:%02d:%02d/";
    sprintf(dir, dirformat, tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    int dir1 = mkdir("logs", 0700);
    int dir2;
    if(debug) {
      if(dir1 == -1) {
        puts("Failed to create logs folder. (Does it already exist?)");
      } else if(dir1 == 0) {
        puts("Logs Folder Created.");
      }
		}
    dir2 = mkdir(dir, 0700);
		if(debug) {
      if(dir2 == -1) {
        puts("Failed to create folder for the current run of the program.\nFurther file logging abored.");
        logtofile = false;
      } else if(dir2 == 0) {
        puts("Folder successfully created for the current run of the program.");
      }
    }
  }

  MPI_Bcast(dir, dirlen, MPI_CHAR, 0, world);

  char* filepath;
  getFilePath(dir, dirlen, rank, &filepath);

  locallog = NULL;
  locallog = fopen(filepath, "w");
  bool localfileexists;
  if(locallog == NULL) {
    if(debug)
      printf("(%d) Failed to create log file for this processor. Further file logging for this processor has been aborted.\n", rank);
    localfileexists = false;
  } else {
    if(debug)
      printf("(%d) Log file for this processor created successfully.\n", rank);
    localfileexists = true;
  }
  return true;
}

void flogs(const char* str) {
  fprintf(locallog, "%s\n", str);
}

void flogf(const char* format, ...) {
  va_list args;
  va_start(args, format);

  vfprintf(locallog, format, args);
}
void flog_KWTree_recursive(struct KWNode* n, int level) {
  if(n == KWNIL)
    return;
  flog_KWTree_recursive(n->left, level+1);
  flogf("%s, ", n->data);
  flog_KWTree_recursive(n->right, level+1);

}
void flog_KWTree(struct KWTree* tree) {
  if(tree->size < 1) {
    flogs("Empty KWTree.");
    return;
  }
  flogs("KWTree:");
  flog_KWTree_recursive(tree->root, 0);
  flogf("\n");
}

void flog_DITree_recursive(struct DINode* n, int level) {
  if(n == DINIL)
    return;
  flog_DITree_recursive(n->left, level+1);
  flogf("{%s, %d}, ", n->data->doc->id, n->data->matrix_index);
  flog_DITree_recursive(n->right, level+1);

}
void flog_DITree(struct DITree* tree) {
  if(tree->size < 1) {
    flogs("Empty KWTree.");
    return;
  }
  flogs("DITree:");
  flog_DITree_recursive(tree->root, 0);
  flogf("\n");
}
#endif

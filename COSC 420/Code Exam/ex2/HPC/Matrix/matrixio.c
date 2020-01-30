#ifndef MATRIXIO
#define MATRIXIO

#include "../func2.c"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "matrix.c"

// Based on: https://stackoverflow.com/questions/23564715/pass-array-as-argument-to-printf

int mprintf(const char* fmt, struct Matrix* A) {
  int n = 0;
  bool even = false;
  const char* p = fmt;
  const double* x = A->arr;
  while(*p) {
    if(*p == '%') {
      if(*(p+1) != 'm' && (*(p+1) != 'r') && (*(p+1) != 'c')) {
        putchar(*p);
      } else if(*(p+1) == 'r') {
        p++;
        n+= printf("%d", ROWS(A));
      } else if(*(p+1) == 'c') {
        p++;
        n+= printf("%d", COLS(A));
      } else {
        p++;
        n += printf("%0.4f", *x++);
      }
    } else {
      putchar(*p);
      n++;
    }
    p++;
  }
  return n;
}
int mfprintf(FILE* f, const char* fmt, struct Matrix* A) {
  int n = 0;
  bool even = false;
  const char* p = fmt;
  const double* x = A->arr;
  while(*p) {
    if(*p == '%') {
      if(*(p+1) != 'm' && (*(p+1) != 'r') && (*(p+1) != 'c')) {
        fputc(*p, f);
      } else if(*(p+1) == 'r') {
        p++;
        n+= fprintf(f, "%d", ROWS(A));
      } else if(*(p+1) == 'c') {
        p++;
        n+= fprintf(f, "%d", COLS(A));
      } else {
        p++;
        n += fprintf(f, "%0.4f", *x++);
      }
    } else {
      fputc(*p, f);
      n++;
    }
    p++;
  }
  return n;
}

void prepare_string(struct Matrix* m, char** output) {
  if(ROWS(m) < 1 || COLS(m) < 1 || m->arr == NULL)
    return;
  //if(output != NULL)
    //free(output);

  char* nonlastnum = "%m ";
  char* lastnum = "%m\n";

  unsigned int rowstrlen = 3*COLS(m)+1;
  //printf("%d %d\n", COLS(m), rowstrlen);
  char* rowstr = malloc(rowstrlen*sizeof(char));
  if(COLS(m) == 1) {
    strcpy(rowstr, lastnum);
  } else {
    strcpy(rowstr, nonlastnum);
    for(int a = 2; a < COLS(m); a++) {
      strcat(rowstr, nonlastnum);
    }
    strcat(rowstr, lastnum);
  }
  //printf("%s\n",rowstr);

  unsigned int outputlen = 6+rowstrlen*ROWS(m);
  *output = malloc(outputlen*sizeof(char));
  strcpy(*output, "%r %c\n");

  for(int a = 0; a < ROWS(m); a++) {
    strcat(*output, rowstr);
  }

  //printf("%d\n%s\n", strlen(*output), *output);
}

void print_to_path(char* filepath, char* format, struct Matrix* m) {
  FILE* f;
  f = fopen(filepath, "w");
  mfprintf(f,format,m);
  fclose(f);
}
#endif

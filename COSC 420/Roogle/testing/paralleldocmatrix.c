#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//#include <time.h>
#include <math.h>
#include <string.h>
#include <mpi.h>
#include <assert.h>
#include "../page/debug.h"
#include "../page/document.h"
#include "../page/kwtree.h"
#include "../page/ditree.h"
#include "../page/construction.h"
/*#include "../page/dictlist.h"
#include "../page/document.h"
#include "../page/ditree.h"
#include "../page/kwtree.h"
#include "../page/treeops.h"
*/
/*
int parse_into_KWTree(struct KWTree* tree, char* abstract, int index) {
  int start = 0; int next;
  int len = strlen(abstract);
  // printf("%s\n", abstract);
  for(int next = start+1; next < len; next++) {
    if((abstract[next] == ' ' || abstract[next] == '\0' || abstract[next] == ',' || abstract[next] == '.' || abstract[next] == '-')) {
      int wordlen = next-start;
      if(wordlen > 4) {
        if(abstract[start] == ' ') {
          start++;
          wordlen = next-start;
        }
        //char* word[wordlen];
        char* word = malloc(wordlen*sizeof(char));
        memcpy(word, abstract+start, wordlen);
        //word[wordlen] = '\0';
        if(strcmp(word, "with") != 0 && strcmp(word, "which") != 0 && strcmp(word, "well") != 0 && strcmp(word, "that") != 0 && strcmp(word, "such") != 0 && strcmp(word, "from") != 0) {
          // printf("%s %d %d\n", word, start, next);
          // for(int i = 0; i < strlen(word); i++) {
          //   printf("%d, ", word+i);
          // }
          //puts("");
          KWTree_insert(tree, word, index);
          //puts("Inserted.");
        }
        next++;
        start=next;
      } else {
        next++;
        start=next;
      }
    }
  }
  // puts("Done.");
}
*/
int main(int argc, char **argv){

  MPI_Init(NULL, NULL);
  int worldsize;
  MPI_Comm world, sub;
  world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldsize);
  int rank, subrank;
  if(worldsize != 0)
    MPI_Comm_rank(world, &rank);
  else
    rank = 0;

  //if(argc > 1 && strcmp(argv[1],"-d") == 0)
  //  debug = true;

  const char* meta_path = "../data/examples/longermeta-mod.txt";
  MPI_File meta_file;

  int missing = MPI_File_open(world, meta_path, MPI_MODE_RDONLY, MPI_INFO_NULL, &meta_file);
  if(missing) {
    printf("(%d) Unable to find meta file located at %s\n", rank, meta_path);
    MPI_Finalize();
    return 0;
  }
  MPI_Barrier(world);

  MPI_Offset meta_len;
  MPI_File_get_size(meta_file, &meta_len);

  const unsigned overhead = meta_len%worldsize;
  const unsigned mincharload = meta_len/worldsize;
  const unsigned localcharload = mincharload+(((int) (bool) (overhead > 0 && rank == worldsize-1))*overhead);
  if(debug)
    printf("(%d) Load: %d\n", rank, localcharload);


  MPI_Barrier(world);
  MPI_File_seek(meta_file, rank*mincharload, MPI_SEEK_SET);

  char* readinput = malloc(localcharload*sizeof(char));
  MPI_File_read(meta_file, readinput/*+subrank*mincharload*/, localcharload, MPI_CHAR, MPI_STATUS_IGNORE);
  //printf("(%d) %s\n\n", rank, readinput);
  MPI_Barrier(world);
  if(debug && rank == 0)
    puts("Meta Data File Read Finished.");
  MPI_Barrier(world);
/*  bool keep = true;
  bool need_recv = false;
  bool need_send = false;
  bool send_part = false;
  bool send_full = false;
  int start, end;

  int ln_cnt = 0;
  for(int a = 0; a < localcharload && ln_cnt < 6; a++) {
    if(readinput[a] == '\n')
      ln_cnt++;
  }
  printf("(%d) %d\n", rank, ln_cnt);
  if(ln_cnt >= 6) {
    int pi1 = -1; bool p1found = false;
    int pi2 = -1; bool p2found = false;
    for(int i = 0; i < localcharload-1 && !p1found; i++) {
      if(readinput[i] == '+' && readinput[i+1] == '\n') {
        pi1 = i+1;
        p1found = true;
      }
    }
    for(int i = localcharload-1; i > 0 && !p2found; i--) {
      if(readinput[i] == '\n' && readinput[i-1] == '+') {
        pi2 = i;
        p2found = true;
      }
    }
    assert(p1found);
    assert(p2found);
    start = pi1+1;
    end = pi2+1;
    //bool loop = readinput[pi1+1] == '+'
    printf("(%d) %d %d\n", rank, pi1, pi2);
    if(end != localcharload) {
      need_recv = true;
    }
    if(start < 7) {
      need_send = true;
      send_part = true;
    }
    if(start==end) {
      keep = false;
    }
  } else if(ln_cnt == 5) {
    //if(readinput[0] == '\n' && readinput[localcharload-1] == '\n') {
    //  start = 1;
    //  end = localcharload-1;
    //} else {

      int pi1 = -1; bool p1found = false;
      int pi2 = -1; bool p2found = false;

      int ln1 = -1; bool l1found = false;
      int ln2 = -1; bool l2found = false;
      for(int i = 0; i < localcharload &&  (!l1found || !l2found) && !(p1found || p2found); i++) {
        if(!l1found && readinput[i] == '\n') {
          l1found = true;
          ln1 = i;
        }
        if(l1found && !p1found && i < localcharload-1 && readinput[i] == '\n' && readinput[i+1] == '\n') {
          p1found = true;
          pi1 = i;
        }
        if(!l2fond && readinput[localcharload-i-1] == '\n') {
          l2found = true;
          ln2 = i;
        }
        if(l2found && !p2found && i < localcharload-1 && readinput[localcharload-i-1] == '\n' && readinput[localcharload-i-2] == '+') {
          p2found = true;
          pi2 = i;
        }
      }
      if(!p1found || !p2found) {

      }
      //start = pi1+1;
      //end = pi2+1;
      if(start == end) {

      }
    //}
  }*/
  bool keep = true;
  bool need_recv = false;
  bool need_send = false;
  bool send_part = false;
  bool send_full = false;
  int start, end;

  int ln_cnt = 0;
  for(int a = 0; a < localcharload && ln_cnt < 6; a++) {
    if(readinput[a] == '\n')
      ln_cnt++;
  }
  //printf("(%d) %d\n", rank, ln_cnt);
  assert(ln_cnt >= 6);

  if(ln_cnt >= 6) {
    int pi1 = -1; bool p1found = false;
    int pi2 = -1; bool p2found = false;
    for(int i = 0; i < localcharload-1 && !p1found; i++) {
      if(readinput[i] == '+' && readinput[i+1] == '\n') {
        pi1 = i+1;
        p1found = true;
      }
    }
    for(int i = localcharload-1; i > 0 && !p2found; i--) {
      if(readinput[i] == '\n' && readinput[i-1] == '+') {
        pi2 = i;
        p2found = true;
      }
    }
    assert(p1found);
    assert(p2found);
    start = pi1+1;
    end = pi2+1;
    printf("(%d) %d %d\n", rank, pi1, pi2);
    printf("(%d) %d %d\n", rank, end, localcharload);
    if(end != localcharload) {
      need_recv = true;
    }
    if(start != 7) {
      need_send = true;
      send_part = true;
    }
    if(start==end) {
      keep = false;
    }

  }

  MPI_Barrier(world);

  if(debug)
  printf("(%d) KEEP: %d, RECV: %d, SEND: %d, PART: %d, FULL: %d\n", rank, keep, need_recv, need_send, send_part, send_full);

  if(rank == 0)
    assert(need_send == false);
  if(rank == worldsize-1)
    assert(need_recv == false);
  if(need_send)
    assert(send_part != send_full);

  int newsize;
  char* workspace;
  MPI_Barrier(world);
  if(need_recv) {
    int rsize;
    MPI_Recv(&rsize, 1, MPI_INT, rank+1, (rank)*100, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    workspace = malloc((localcharload+rsize)*sizeof(char));
    memcpy(workspace, readinput, localcharload);
    //char* test = malloc(rsize*sizeof(char));
    newsize = localcharload+rsize;
    MPI_Recv(workspace+localcharload, rsize, MPI_CHAR, rank+1, rank*100+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //printf("%s\n", test);
  } else {
    workspace = readinput;
    newsize = mincharload;
  }
  if(rank == 2)
    puts("Hello.");
  if(need_send) {
    int ssize = start;
    MPI_Send(&ssize, 1, MPI_INT, rank-1, (rank-1)*100, MPI_COMM_WORLD);
    MPI_Send(workspace, ssize, MPI_CHAR, rank-1, (rank-1)*100+1, MPI_COMM_WORLD);
  }
  MPI_Barrier(world);
  struct KWTree kwtree;
  define_KWTree(&kwtree);
  struct DITree ditree;
  define_DITree(&ditree);

    int i = 0; int index;
    for(int index = start; index < newsize; ) {
      //printf("%d\n", start);
      struct Document* d = malloc(sizeof(struct Document));
      index += process_to_doc(d, workspace+index, newsize-index);
      //printf("%d\n", index);
      //print_document(&d);
      //puts("-------------");
      DocIndex* d_ind = DITree_insert(&ditree, d, i);
      //create_DocIndex(&d_ind, &d, rank*1000000+i);
      i++;
      //DITree_insert_di(&ditree, d_ind);
      parse_into_KWTree(&kwtree, d->abstract, d_ind->matrix_index);
      //puts("");
    }
    for(int i = 0; i < worldsize; i++) {
      if(rank == i) {
        print_KWTree_elements(&kwtree);
      }
      MPI_Barrier(world);
      if(rank == i) {
        print_DITree_elements(&ditree);
      }
      MPI_Barrier(world);
    }

    MPI_Barrier(world);
    struct idList* list;
    char* query = "these";
    bool found = KWTree_fetch_idList(&kwtree, query, &list);
    MPI_Barrier(world);
    if(found) {
      puts("\n");
      printlist(list);
    }



  MPI_Finalize();
  return 0;
}

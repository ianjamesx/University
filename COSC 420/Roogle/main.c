#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <mpi.h>
#include <assert.h>

#include <unistd.h>
#include <fcntl.h>

#include "page/debug.h"
#include "page/document.h"
#include "page/kwtree.h"
#include "page/ditree.h"
#include "page/construction.h"
#include "page/procio.h"
#include "page/customtypes.h"
#include "page/csr.h"
#include "page/graph.h"
#include "page/citehandler.h"

void assignScores(struct Document results[], int auth[], int hub[], float pr[], int doccount){

  int i, j;
  for(i = 0; i < doccount; i++){
    results[i].authscore = auth[i];
    results[i].hubscore = hub[i];
    results[i].pagerank = pr[i];
  }
}

void swap(struct Document *d1, struct Document *d2){

  struct Document temp = *d1;
  *d1 = *d2;
  *d2 = temp;

}

void reverseorder(struct Document *res[], int size){
  int i;
  for(i = 0; i < size; i++){
    swap(res[i], res[(size-1)-i]);
  }
}

int part(struct Document *results[], int low, int high){

  int pivot = results[high]->authscore;
  int i = (low - 1);

  for (int j = low; j <= high-1; j++){
    if(results[j]->authscore > pivot){
      i++;
      swap(results[i], results[j]);
    }
  }
  swap(results[i + 1], results[high]);
  return (i + 1);
}

void quik(struct Document *results[], int low, int high){
  if (low < high){
    int pi = part(results, low, high);
    quik(results, low, pi - 1);
    quik(results, pi + 1, high);
  }
}


int main(int argc, char **argv){
  time_t t = time(0);

  MPI_Init(NULL, NULL);
  define_custom_types();
  int worldsize;
  MPI_Comm world, sub;
  world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldsize);
  int rank, subrank;
  if(worldsize != 0)
    MPI_Comm_rank(world, &rank);
  else
    rank = 0;

    if(argc > 1)
      debug = debugMode(argc, argv);
    else
      debug = false;

    int remainingArgs = argc;
    if(debug) {
      if(rank == 0)
        puts("Debug Mode: TRUE");
      remainingArgs--;
    } else {}

    setup_procio(t);
    flogf("Processor Rank: %d\n\n", rank);

  const char* meta_path = /*"data/arxiv-metadata.txt";*/"data/examples/submission/test-metadata.txt";
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
    printf("(%d) Metadata File Load: %d\n", rank, localcharload);
  flogf("(%d) Metadata File Load: %d\n", rank, localcharload);

  MPI_Barrier(world);
  MPI_File_seek(meta_file, rank*mincharload, MPI_SEEK_SET);

  char* readinput = malloc(localcharload*sizeof(char));
  clock_t start_clock = clock();
  MPI_File_read(meta_file, readinput, localcharload, MPI_CHAR, MPI_STATUS_IGNORE);
  clock_t local_end_clock = clock();
  MPI_Barrier(world);
  clock_t global_end_clock = clock();
  double global_time_spent = (double)(local_end_clock - start_clock) / CLOCKS_PER_SEC;
  flogf("(%d) Meta Data File Read Finished. %0.2f Local, %0.2f Global\n", rank, (double)(local_end_clock - start_clock)/CLOCKS_PER_SEC, global_time_spent);
  if(debug && rank == 0) {
    printf("Meta Data File Read Finished. %0.2f\n", global_time_spent);
    puts("Initialization Complete.\n");
  }
  if(debug) {
    flogf("\nMetadata Read:\n%s\n\n", readinput);
  } else {
    flogf("\nDebug False. Metadata Read output skipped.\n\n");
  }
  MPI_Barrier(world);

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
    //printf("(%d) %d %d\n", rank, pi1, pi2);
    //printf("(%d) %d %d\n", rank, end, localcharload);
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
  flogf("Meta Data Input Redistribution:\n\tKEEP: %d, RECV: %d, SEND: %d, PART: %d, FULL: %d\n", keep, need_recv, need_send, send_part, send_full);
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
  // if(rank == 2)
  //   puts("Hello.");
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
    //if(rank == 0)
    //  print_document(d);
    //puts("-------------");
    DocIndex* d_ind = DITree_insert(&ditree, d, i);
    //create_DocIndex(&d_ind, &d, rank*1000000+i);
    i++;
    //DITree_insert_di(&ditree, d_ind);
    parse_into_KWTree(&kwtree, d->abstract, d_ind->matrix_index);
    //puts("");
  }
  MPI_Barrier(world);

  flogf("\n");
  flog_KWTree(&kwtree);
  flogf("\n");
  flog_DITree(&ditree);
  /*for(int i = 0; i < worldsize; i++) {
    if(rank == i) {
      print_KWTree_elements(&kwtree);
    }
    MPI_Barrier(world);
    if(rank == i) {
      print_DITree_elements(&ditree);
    }
    MPI_Barrier(world);
  }*/

  MPI_Barrier(world);
  // struct idList* list;
  // char* query = "these";
  // bool found = KWTree_fetch_idList(&kwtree, query, &list);
  // MPI_Barrier(world);
  /*if(found) {
    puts("\n");
    printlist(list);
  }*/

  assert(worldsize == 2);
  if(rank == 1) {
    char* words[kwtree.size];
    int* kwindexes[kwtree.size];
    int lengths[kwtree.size];
    KWTree_populate_array(&kwtree, words, kwindexes, lengths);

    struct Document docs[ditree.size];
    int diindexes[ditree.size];
    DITree_populate_array(&ditree, docs, diindexes);

    MPI_Send(&(kwtree.size), 1, MPI_INT, 0, 0, world);
    MPI_Send(lengths, kwtree.size, MPI_INT, 0, 1, world);
    int i;
    for(i = 0 ; i < kwtree.size; i++) {
      int wordlen = strlen(words[i]);
      MPI_Send(&wordlen, 1, MPI_INT, 0, 2+i*3, world);
      MPI_Send(words[i], wordlen, MPI_CHAR, 0, 3+i*3, world);
      //if(i > 35)
      //  flogf("%s\n", words[i]);
      MPI_Send(kwindexes[i], lengths[i], MPI_INT, 0, 4+i*3, world);
    }

    MPI_Send(&(ditree.size), 1, MPI_INT, 0, 5+i*3, world);
    MPI_Send(docs, ditree.size, MPI_DOC, 0, 6+i*3, world);

  }
  if(rank == 0){
    //---------------------------------------------
    // Recv Info From Other Nodes
    //---------------------------------------------
    int recv_kwtree_size;
    MPI_Recv(&recv_kwtree_size, 1, MPI_INT, 1, 0, world, MPI_STATUS_IGNORE);

    int* recv_tree_list_lens = malloc(recv_kwtree_size*sizeof(int));
    MPI_Recv(recv_tree_list_lens, recv_kwtree_size, MPI_INT, 1, 1, world, MPI_STATUS_IGNORE);

    char* recv_words[recv_kwtree_size];
    int* recv_indexes[recv_kwtree_size];
    int i;
    for(i = 0; i < recv_kwtree_size; i++) {
      int wordlen;
      MPI_Recv(&wordlen, 1, MPI_INT, 1, 2+i*3, world, MPI_STATUS_IGNORE);
      recv_words[i] = malloc(wordlen*sizeof(char));
      MPI_Recv(recv_words[i], wordlen, MPI_CHAR, 1, 3+i*3, world, MPI_STATUS_IGNORE);

      recv_indexes[i] = malloc(recv_tree_list_lens[i]*sizeof(int));
      MPI_Recv(recv_indexes[i], recv_tree_list_lens[i], MPI_INT, 1, 4+i*3, world, MPI_STATUS_IGNORE);
    }
    //printf("(%d) %s, %s, %s, %s, %s\n", rank, recv_words[0], recv_words[/*looplen-*/1], recv_words[recv_kwtree_size/3], recv_words[recv_kwtree_size*2/3], recv_words[recv_kwtree_size-1]);

    int recv_ditree_size;
    MPI_Recv(&recv_ditree_size, 1, MPI_INT, 1, 5+i*3, world, MPI_STATUS_IGNORE);

    struct Document recv_docs[recv_ditree_size];
    MPI_Recv(recv_docs, recv_ditree_size, MPI_DOC, 1, 6+i*3, world, MPI_STATUS_IGNORE);
    //---------------------------------------------

    int old_ditree_size = ditree.size;
    //---------------------------------------------
    // Add to Local KWTree
    //---------------------------------------------
    for(int j = 0; j < recv_kwtree_size; j++) {
      struct idList* list = malloc(sizeof(struct idList));
      create_from_array(list, recv_indexes[j], recv_tree_list_lens[j]);
      char* word = recv_words[j];
      KWTree_af(&kwtree, &word, list, old_ditree_size);
    }
    flog_KWTree(&kwtree);

    //---------------------------------------------
    // Add to Local DITree
    //---------------------------------------------
    int from_node = 1;
    for(int j = 0; j < recv_ditree_size; j++) {
      DITree_insert(&ditree, &(recv_docs[j]), ditree.size);
    }
    if(debug)
      print_DITree_elements(&ditree);
    flog_DITree(&ditree);

    struct Document doc_arr[ditree.size];
    DITree_convert_to_array(&ditree, doc_arr);


    // for(int i = 0; i < ditree.size; i++) {
    //   printf("%s\n", doc_arr[i].id);
    // }

    //---------------------------------------------
    // Calculations
    //---------------------------------------------

    //define graph
    struct CSRgraph graph;
    struct CSRgraph *csr = &graph;

    buildCSRfromCiteFile(csr, &ditree, /*"data/examples/testcitations");*/"data/examples/submission/test-citations.txt"); //<-- pass CSRgraph, DItree, and name of citations file

    if(debug)
      statprint(*csr); //<-- prints graph stats, optional

    //calc hub, auth, and pagerank

    int hub[csr->nvertices], auth[csr->nvertices];
    float pagerank[csr->nvertices];

    sparsehub(*csr, hub, csr->nvertices);
    sparseauth(*csr, auth, hub, csr->nvertices);
    sparsepagerank(*csr, pagerank);

    /*
    set authority score, hub score, page rank, for all documents
    */


    assignScores(doc_arr, hub, auth, pagerank, ditree.size);

    if(debug)
      for (int k = 0; k < ditree.size; k++)
        printf("%d %d %0.4f\n", hub[k], auth[k], pagerank[k]);

    if(argc > 1){

      bool included[ditree.size];
      for(int i = 0; i < ditree.size; i++) {
        included[i] = false;
      }

      int total_results = 0;

      int i;
      for(i = 1; i < argc; i++){
        //printf("%s: ", argv[i]);

        struct idList* list;
        bool found = KWTree_fetch_idList(&kwtree, argv[i], &list);
        if(i != 1) {
          appendtolist(list, 6);
        }
        if(found){

          int arr[list->size];
          convertToArr(list, arr);

          for(int j = 0; j < list->size; j++) {
            if(!included[arr[j]]) {
              included[arr[j]] = true;
              total_results++;
            }
            //printf("%d, ", included[j]);
          }
        }
        //puts("");
      }

      struct Document *results[total_results];
      int index = 0;
      for(int i = 0; i < ditree.size; i++) {
        if(included[i]) {
          results[index] = &doc_arr[i];
          index++;
        }
      }
      // Sort results

      quik(results, 0, total_results-1);
      reverseorder(results, total_results);

      for(i = 0; i < total_results; i++){
        printf("%s\n", results[i]->title);
        printf("%s\n", results[i]->authors);
        printf("%s\n", results[i]->abstract);
        printf("pagerank: %.2f\n", results[i]->authscore, results[i]->hubscore, results[i]->pagerank);
        printf("+++\n");
      }

    }
  }
  MPI_Barrier(world);


  if(debug)
    printf("(%d) Done.\n", rank);
  flogf("(%d) Done.\n", rank);

  fclose(locallog);
  MPI_Finalize();
  return 0;
}

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
#include "../page/customtypes.h"
#include "../page/testing.h"

#define DOCNUM 5

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  int worldsize;
  MPI_Comm world;
  world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldsize);
  int rank;
  if(worldsize != 0)
    MPI_Comm_rank(world, &rank);
  else
    rank = 0;

  assert(worldsize == 2);

  struct Document docs[DOCNUM];
  get_sample_docs(docs);

  struct Document* d;
  d = &docs[rank];

  define_custom_types();

  if(rank == 0) {
    MPI_Send(d, 1, MPI_DOC, 1, 0, world);
  } else {
    MPI_Recv(d, 1, MPI_DOC, 0, 0, world, MPI_STATUS_IGNORE);
    print_document(d);
  }



  MPI_Finalize();
  return 0;
}

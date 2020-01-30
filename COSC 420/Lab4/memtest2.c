#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mpi.h>

void numeric(char *shadow, char *username, char *salt){


}

int main(int argc, char **argv){
  int i, flag;

  int nodesize, noderank;
  int size, rank;
  int tablesize, localtablesize;
  int table[10], localtable[10];

  MPI_Comm nodecomm;

  MPI_Aint winsize;
  int windisp;

  //some hard coded details about the words/shadow files

  int dictbytes = 2493109, dictlines = 235886;
  int shadowbytes = 639, shadowlines = 10;

  MPI_Win wintable;

  tablesize = 10;

  MPI_Init(NULL, NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, rank, MPI_INFO_NULL, &nodecomm);
  MPI_Comm_size(nodecomm, &nodesize);
  MPI_Comm_rank(nodecomm, &noderank);

  // Only rank 0 on a node actually allocates memory

  localtablesize = 0;

  if (noderank == 0){
    localtablesize = tablesize;
  }

  for(i = 0; i < tablesize; i++){
    table[i] = localtable[i];
  }

  if (noderank != 0){
    MPI_Win_shared_query(wintable, 0, &winsize, &windisp, &table);
  }

  // All table pointers should now point to copy on noderank 0
  // Initialise table on rank 0 with appropriate synchronisation

  MPI_Win_fence(0, wintable);

  if (noderank == 0){
    for (i=0; i < tablesize; i++){
      table[i] = 1;//rank*tablesize + i;
    }
  }

  MPI_Win_fence(0, wintable);

  // Check we did it right

  int ops = tablesize / size;
  int low = ops * rank, high = low + ops;

  printf("WIND %d\n", tablesize);

  printf("%d: %d %d\n", rank, low, high);

  for (i = 0; i < tablesize; i++){
    //printf("rank %d, noderank %d, word index[%d] = %d\n", rank, noderank, i, table[i]);
  }

  MPI_Finalize();
}

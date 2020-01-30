#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

#include "csr.h"
#include "document.h"

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0){

    int nsize = 5;

    int matr[nsize*nsize];

    initMatrix(matr, nsize);
    printMatrix(matr, nsize);

    struct CSRgraph graph1;

    matrixtocsr(matr, nsize, &graph1);

    statprint(graph1);

    printf("Offsets:\n\n");
    //offsetprint(graph1);
    debugprint(graph1);
    //finalconnprint(graph1);

    freegraph(&graph1);

  }

  MPI_Finalize();

  return 0;
}

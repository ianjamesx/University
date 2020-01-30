#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

    int wsize, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *vect1, *vect2;
    int arrsize;

    int *global, *local;

    //let rank 0 be root node
    if(rank == 0){

      arrsize = 40;//rand() % 100000 + 1;
      printf("randsize: %d\n", arrsize);

      vect1 = malloc(arrsize*sizeof(int));
      vect2 = malloc(arrsize*sizeof(int));
      global = malloc(arrsize*sizeof(int));

      int i;
      for(i = 0; i < arrsize; i++){

        vect1[i] = i;//rand() % 1000 + 1;
        vect2[i] = i;//rand() % 1000 + 1;
        global[i] = i;

      }

      //we need to perfectly distribute the elements across nodes
      //before we scatter

      int opspernode = arrsize / wsize;
      printf("Ops per node: %d\n", opspernode);

      int rootops = arrsize % wsize;
      printf("Left for root: %d\n", rootops);

    }

    MPI_Bcast(&arrsize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int opspernode = arrsize / wsize;
    local = malloc(opspernode*sizeof(int));

    MPI_Scatter(global, opspernode, MPI_INT, local, opspernode, MPI_INT, 0, MPI_COMM_WORLD);

    int i;
    for(i = 0; i < opspernode; i++){

      printf("Processor %d has data at index %d: %d\n", rank, i, local[i]);

    }

/*
    MPI_Bcast(&arrsize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vect1, arrsize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vect2, arrsize, MPI_INT, 0, MPI_COMM_WORLD);
*/



  //  int lowerRange = i * opspernode;
  //  int upperRange = lowerRange + opspernode;




    MPI_Finalize();
    return 0;
}

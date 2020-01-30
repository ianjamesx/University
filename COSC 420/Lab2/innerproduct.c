#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv) {

    int wsize, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*

    we'll create data to hold elements as they exist globally on root
    and what each node will hold individually

    */

    int arrsize;
    int *global1, *local1, *global2, *local2;
    int *result;

    //let rank 0 be root node
    if(rank == 0){

      arrsize = rand() % 1000000000 + 1;
      printf("random array size: %d\n", arrsize);

      global1 = malloc(arrsize*sizeof(int));
      global2 = malloc(arrsize*sizeof(int));

      int i;
      for(i = 0; i < arrsize; i++){

        global1[i] = rand() % 1000 + 1;
        global2[i] = rand() % 1000 + 1;

        //printf("Init: %d) %d, %d\n", i, global1[i], global2[i]);

      }

      //we need to  distribute the elements across nodes before we scatter
      //the reason we use ceil is so we dont have to deal with left over operations that
      //the root will have to cover at the end
      //this way, all the nodes may have an extra operation (and may overloap)
      //but it will be easier on the root

      int opspernode = ceil(arrsize / wsize);
      //printf("Ops per node: %d\n", opspernode);

    }

    MPI_Bcast(&arrsize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int opspernode = arrsize / wsize;
    local1 = malloc(opspernode*sizeof(int));
    local2 = malloc(opspernode*sizeof(int));

    MPI_Scatter(global1, opspernode, MPI_INT, local1, opspernode, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(global2, opspernode, MPI_INT, local2, opspernode, MPI_INT, 0, MPI_COMM_WORLD);

    int i;
    for(i = 0; i < opspernode; i++){

      //printf("Processor %d has data) %d, %d\n", rank, local1[i], local2[i]);

      local1[i] = local1[i] + local2[i]; //just store result in local1

    }

    if(rank == 0){

      //result = malloc(arrsize*sizeof(int));

    }

    //Reduce was giving some issues, Gather works well for collecting results on node
    //collect in global1, this will be our final output

    MPI_Gather(local1, opspernode, MPI_INT, global1, opspernode, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){

      int i;
      for(i = 0; i < arrsize; i++){

       //printf("Sum %d) %d\n", i, global1[i]);
      }

    }

    MPI_Finalize();
    return 0;
}

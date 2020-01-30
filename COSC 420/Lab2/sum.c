#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char **argv){

  MPI_Init(NULL, NULL);

  MPI_Comm world = MPI_COMM_WORLD;

  int nprocs, me;
  MPI_Comm_size(world, &nprocs);
  MPI_Comm_rank(world, &me);

  srand(time(0) + me);

  float myNumber = (float)rand() / (float)RAND_MAX, sum;

  MPI_Allreduce(&myNumber, &sum, 1, MPI_FLOAT, MPI_SUM, world);

  float avg = sum / (float)nprocs;

  printf("Rank %d: %2.4f\n", me, myNumber);

  if(me == 0){
    printf("The average was %2.4f\n", avg);
  }

  MPI_Finalize();

  return 0;
}

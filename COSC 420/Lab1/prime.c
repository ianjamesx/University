#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){

  /*
  shell time command: time mpiexec file.c
  */


  //convert input from *char to int
  int num;
  sscanf(argv[3],"%d",&num);

  MPI_Init(NULL, NULL);

  int wsize;
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &wsize);

  int id;
  MPI_Comm_rank(world, &id);

  int input = num;
  int limit = sqrt(input * 1.0);
  //printf("SQUARE ROOT OF %d: %d\n", input, limit);

  int workPerNode = limit / wsize;
  if(workPerNode < 1) workPerNode = 1;

  int lowerRange = id * workPerNode;
  int upperRange = lowerRange + workPerNode;

  //uncomment this to see the lower, upper and and work done by each node
  //printf("node id: %d, work:%d ops, lower:%d, upper: %d\n", id, workPerNode, lowerRange, upperRange);

  int i, j;
  int isprime = 1; //we need all nodes to agree on it not being prime (if its truly not), we'll communicate this at the end
  for(i = lowerRange; i < upperRange; i++){

    for(j = 0; j < input; j++){

      if(i == input || j == input) continue; //skip case where we have input * 1, false positive

      if(j * i == input){

        printf("its not prime: %d * %d = %d\n",i, j, input);
        isprime = 0; //is not prime

      }

    }

  }

  MPI_Finalize();
	return 0;

}

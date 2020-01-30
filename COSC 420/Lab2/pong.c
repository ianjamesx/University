#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char **argv){

  if(argc < 2){
    printf("Usage: ./bin N\n");
    return 1;
  }

  MPI_Init(NULL, NULL);

  int pingpongLim = atoi(argv[1]);

  int wsize;
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &wsize);

  int id;
  MPI_Comm_rank(world, &id);

  int token = 0;
  while(token < pingpongLim){

    if(token % 2 == id % 2){
      token++;
      MPI_Send(&token, 1, MPI_INT, (id+1)%2, 0, world);
    } else {
      MPI_Recv(&token, 1, MPI_INT, MPI_ANY_SOURCE, 0, world, MPI_STATUS_IGNORE);
      printf("Processor %d recieved %d from %d\n", id, token, (id+1)%2);
      printf("Status tag is %d\n", status.MPI_TAG);
      printf("Status source is %d\n", status.MPI_SOURCE);
    }

  }

  MPI_Finalize();
  return 0;

}

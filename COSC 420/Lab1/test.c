#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
  MPI_Init(NULL, NULL);

  int world_size;
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &world_size);

  int me;
  MPI_Comm_rank(world, &me);

  char name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(name, &name_len);

  printf("Hello, world of size %d!\n", world_size);
  printf("I am processor %s\n", name);
  printf("I am node %d!\n", me);

  MPI_Finalize();

	//1/n * sqrt(n)

	return 0;

}

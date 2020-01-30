#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0){

    int filedes[1];

    filedes[0] = open("smallword.txt", O_RDONLY);
    printf("%d\n", filedes[0]);
    if(filedes[0] == -1){
      printf("Not happening...\n");
      return 0;
    }

    //create buffer to hold one char (one byte)
    char buffer[1];
    int nread;
    while ((nread = read(filedes[0], buffer, 1) > 0)){
      printf("%s - %d\n", buffer, (int)buffer[0]);
    }

  }


  MPI_Finalize();

  return 0;

}

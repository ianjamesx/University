
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "matrix.h"

void randomWalk(matrix){

  int i;

  int s = rand() % (n*n) + 1;
  int k = rand() % 1000 + 1; //random amount of iterations

  printf("Random Node (start): %d, iterations: %d\n", s, k);

  for(i = 0; i < k; i++){

    int possible[n];
    int index = 0;

    for(j = 0; j < n; j++){
      int next = INDEX(n, s, j); //INDEX(Array, s, j);
      if(next == 1){
        possible[index] = i;
        index++;
      }
    }

    //randomly chose some index in possible
    int nextnode = rand() % index + 1;
    s = possible[nextnode];

    printf("Next Node: %d\n", s);

  }

}


int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0){

    int n = 9;

    //just building some temporary arrays
    //looks rough, its the easiest way to hardcode
    int row1[8] = {0, 1, 0, 1, 0, 0, 1, 1};
    int row2[8] = {1, 0, 1, 0, 1, 1, 0, 0};
    int row3[8] = {1, 1, 1, 0, 0, 0, 0, 1};
    int row4[8] = {1, 0, 1, 1, 1, 0, 0, 1};
    int row5[8] = {0, 1, 1, 1, 0, 0, 1, 0};
    int row6[8] = {0, 0, 0, 0, 0, 1, 1, 0};
    int row7[8] = {1, 1, 0, 1, 1, 0, 1, 1};
    int row8[8] = {1, 0, 1, 1, 1, 0, 1, 0};

    int matrix[n*n];

    int i, j;
    for(i = 0; i < n; i++){
      matrix[i] = row1[i];
    }
    for(i = 0; i < n; i++){
      matrix[i] = row2[i];
    }
    for(i = 0; i < n; i++){
      matrix[i] = row3[i];
    }
    for(i = 0; i < n; i++){
      matrix[i] = row4[i];
    }

    for(i = 0; i < n; i++){
      matrix[i] = row5[i];
    }
    for(i = 0; i < n; i++){
      matrix[i] = row6[i];
    }
    for(i = 0; i < n; i++){
      matrix[i] = row7[i];
    }
    for(i = 0; i < n; i++){
      matrix[i] = row8[i];
    }



  }


  MPI_Finalize();

  return 0;

}

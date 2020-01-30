

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "HPC/Matrix/matrix.c"
#include "HPC/Matrix/matrixmath.c"


void randomWalk(struct Matrix *A){

  int i;
  int n = 8;

  int s = rand() % (n*n) + 1;
  int k = rand() % 1000 + 1; //random amount of iterations

  printf("Random Node (start): %d, iterations: %d\n", s, k);

  for(i = 0; i < k; i++){

    int possible[n];
    int index = 0;

    for(j = 0; j < n; j++){
      int next = INDEX(n, n, s, j); //INDEX(Array, s, j);
      if(next == 1){
        possible[index] = j;
        index++;
      }
    }

    //randomly chose some index in possible
    int nextnode = rand() % index + 1;
    s = possible[nextnode];

  }

  return s;

}


int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  struct Matrix A;
  initMatrix(&A, 8, 8);
  //if(rank == 0){

    int n = 9;

    //just building some temporary arrays
    //looks rough, its the easiest way to hardcode
    double row1[8] = {0, 1, 0, 1, 0, 0, 1, 1};
    double row2[8] = {1, 0, 1, 0, 1, 1, 0, 0};
    double row3[8] = {1, 1, 1, 0, 0, 0, 0, 1};
    double row4[8] = {1, 0, 1, 1, 1, 0, 0, 1};
    double row5[8] = {0, 1, 1, 1, 0, 0, 1, 0};
    double row6[8] = {0, 0, 0, 0, 0, 1, 1, 0};
    double row7[8] = {1, 1, 0, 1, 1, 0, 1, 1};
    double row8[8] = {1, 0, 1, 1, 1, 0, 1, 0};


    int i, j;
    for(i = 0; i < n; i++){
      ACCESS((&A), 0, i) = row1[i];
    }
    for(i = 0; i < n; i++){
      ACCESS((&A), 1, i) = row2[i];
    }
    for(i = 0; i < n; i++){
      ACCESS((&A), 2, i) = row3[i];
    }
    for(i = 0; i < n; i++){
      ACCESS((&A), 3, i) = row4[i];
    }

    for(i = 0; i < n; i++){
      ACCESS((&A), 4, i) = row5[i];
    }
    for(i = 0; i < n; i++){
      ACCESS((&A), 5, i) = row6[i];
    }
    for(i = 0; i < n; i++){
      ACCESS((&A), 6, i) = row7[i];
    }
    for(i = 0; i < n; i++){
      ACCESS((&A), 7, i) = row8[i];
    }
  //}
  //MPI_Bcast(A.arr, ROWS((&A))*COLS((&A)), MPI_DOUBLE, 0, MPI_COMM_WORLD);
  if(rank == 0) {
    puts("Matrix A:");
    printMatrix(&A);
    puts("");
  }

  struct Matrix ev;
  initVector(&ev, ROWS((&A)));

  MPI_Barrier(MPI_COMM_WORLD);
  clock_t begin = clock();
  first_pass(&A,&ev);
  clock_t end = clock();

  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  if(rank == 0) {
    puts("Normalized Eigenvector:");
    printMatrix(&ev);
    printf("\nCalculation Time: %0.2f\n", time_spent);
  }

  randomWalk(A);



  MPI_Finalize();

  return 0;

}

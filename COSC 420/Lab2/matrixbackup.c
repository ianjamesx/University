#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

//#define INDEX(r,c,i,j) r*c + j
//#define ACCESS(A,i,j) A->arr[INDEX(A->rows, A->cols, i, j)]

struct matrix {
  int rows;
  int cols;
  int *arr;
};

void initMatrix(struct matrix *A, int r, int c){
  A->rows = r;
  A->cols = c;
  int size = (r*c)*sizeof(int);
  A->arr = malloc(size);

  int i, j;
  for(i = 0; i < r; i++){
    for(j = 0; j < c; j++){
      int index = (i*r) + j;
      A->arr[index] = rand() % 100 + 1;
    }
  }
}

void printMatrix(struct matrix *A){

  printf("\n");
  int i, j;
  for(i = 0; i < A->rows; i++){
    for(j = 0; j < A->cols; j++){
      int index = (i*A->rows) + j;
      printf("%d ", A->arr[index]);
    }
    puts("");
  }
  printf("\n");
}

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //have root node init matrix

  struct matrix A;
  int *size;
  int *a, *b;
  if(rank == 0){

    srand(time(0));
    struct matrix A;
    initMatrix(&A, 14, 14);
    printMatrix(&A);

    /*
    The root node (e.g. 0, this one)
    will decide how much work each of the other nodes have to do
    will distribute enough data to complete a task to other nodes
    */

    int opspernode = (A.rows*A.cols) / wsize;
    if(opspernode < 1) opspernode = 1;

    int lowerRange = rank * opspernode;
    int upperRange = lowerRange + opspernode;

    printf("Ops: %d\n", opspernode);
    size = malloc(3*sizeof(int));
    size[0] = 1;
    size[1] = 2;
    size[2] = 3;

    int i;
    for(i = 1; i < wsize; i++){

      MPI_Send(size, 3, MPI_INT, i, 0, MPI_COMM_WORLD);
      
    }

    //free(A.arr);

  }

  if(rank != 0){

    size = malloc(3*sizeof(int));
    MPI_Recv(size, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    int i;
    for(i = 0; i < 3; i++){
      printf("rank %d, index %d, val %d\n", rank, i, size[i]);
    }
  }

  //printMatrix(&A);
  //printf("%d\n", A.rows);

  MPI_Finalize();

  return 0;
}

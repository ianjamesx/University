#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

//#define INDEX(r,c,i,j) r*c + j
//#define ACCESS(A,i,j) A->arr[INDEX(A->rows, A->cols, i, j)]

#define INDEX(r,c,i,j) i*r + j

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
      int index = INDEX(r,c, i, j);
      A->arr[index] = rand() % 100 + 1;
    }
  }
}

void printMatrix(struct matrix *A){

  printf("\n");
  int i, j;
  for(i = 0; i < A->rows; i++){
    for(j = 0; j < A->cols; j++){
      int index = INDEX(A->rows,A->cols, i, j);//(i*A->rows) + j;
      printf("%d ", A->arr[index]);
    }
    puts("");
  }
  printf("\n");
}

int *multiplyMatrices(int *a, int *b, int *result, int n, int r, int c){

  int i, j, l;
  for(i = 0; i < n; i++){

			result[INDEX(r,c,i,j)] = 0;

      for(j = 0; j < n; j++){

        for(l = 0; l < n; l++){

          result[INDEX(r,c,i,j)] += a[INDEX(r,c,i,j)] * b[INDEX(r,c,i,j)];

        }

			}

   }

   return result;

}

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //have root node init matrix
  //sequential portion

  int msize;
  int *a, *b, *c;

  if(rank == 0){

    int num;
    sscanf(argv[1],"%d",&num);
    msize = num;

    srand(time(0));
    struct matrix A;
    initMatrix(&A, msize, msize);
    printf("\nRandom Matrix A:\n");
  //  printMatrix(&A);

    struct matrix B;
    initMatrix(&B, msize, msize);
    printf("Random Matrix B:\n");
    //printMatrix(&B);

    struct matrix C;
    initMatrix(&C, msize, msize);

    int r = msize;
    int c = msize;

    int i, j, l;
    for(i = 0; i < msize; i++){

  			C.arr[INDEX(r,c,i,j)] = 0;

        for(j = 0; j < msize; j++){
          for(l = 0; l < msize; l++){

            C.arr[INDEX(r,c,i,j)] += A.arr[INDEX(r,c,i,l)] * B.arr[INDEX(r,c,l,j)];

          }

  			}

     }

    //printMatrix(&C);

    //free(a);
    //free(b);

    //initMatrix(&C, msize, msize);

  }

  MPI_Finalize();

  return 0;
}

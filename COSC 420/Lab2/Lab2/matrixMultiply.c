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

void multiplyMatrices(int *a, int *b, int *result, int n, int r, int c){

  int i, j, l;
  for(i = 0; i < n; i++){

			result[INDEX(r,c,i,j)] = 0;

      for(j = 0; j < n; j++){
        for(l = 0; l < n; l++){

          result[INDEX(r,c,i,j)] += a[INDEX(r,c,i,l)] * b[INDEX(r,c,l,j)];

        }

			}

   }

}

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //have root node init matrix

  int msize;
  int *a, *b, *c;

  int lowerRange, upperRange;

  int *final;

  if(rank == 0){

    int num;
    sscanf(argv[1],"%d",&num);
    msize = num;

    srand(time(0));
    struct matrix A;
    initMatrix(&A, msize, msize);
    printf("\nRandom Matrix A:\n");
    printMatrix(&A);

    struct matrix B;
    initMatrix(&B, msize, msize);
    printf("Random Matrix B:\n");
    printMatrix(&B);

    //allocate temp memory
    int i;
    a = malloc((A.rows*A.cols)*sizeof(int));
    b = malloc((B.rows*B.cols)*sizeof(int));
    final = malloc((B.rows*B.cols)*sizeof(int));

    //copy to int arrays so we dont have to pass structs
    for(i = 0; i < (A.rows*A.cols); i++){
      a[i] = A.arr[i];
      b[i] = B.arr[i];
    }

    //preset for node, incase of edge case
    lowerRange = 0;
    upperRange = (msize*msize);

    //dont run on root
    for(i = 1; i < wsize; i++){
      //send a copy of the array to all other nodes
      MPI_Send(a, (msize*msize), MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(b, (msize*msize), MPI_INT, i, 1, MPI_COMM_WORLD);
    }

    printf("%d\n", a[0]);

  }

  //broadcast array size
  MPI_Bcast(&msize, 1, MPI_INT, 0, MPI_COMM_WORLD);
  int arrsize = msize*msize;

  //rank 0 doesnt send anything (so it wouldnt block)
  if(rank != 0){
    a = malloc(arrsize*sizeof(int));
    b = malloc(arrsize*sizeof(int));
    MPI_Recv(a, arrsize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(b, arrsize, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("%d, %d, %d\n", arrsize, a[0], b[0]);
  }

  //how many ops each node will have to do
  int opspernode = ceil(arrsize / wsize);

  //get the range of indices that this node should cover

  if(rank != 0){
    lowerRange = rank * opspernode;
    upperRange = lowerRange + opspernode;
  }

  c = malloc(arrsize*sizeof(int));

  //have this node do its job

  //the only reason for if else
  //used to send from here, changed it, may have to change it back
  if(rank == 0){
    int i;
    for(i = lowerRange; i < upperRange; i++){
      multiplyMatrices(a, b, c, msize, msize, msize);
    }
  } else {
    int i;
    for(i = lowerRange; i < upperRange; i++){
      multiplyMatrices(a, b, c, msize, msize, msize);
    }
  }

  if(rank != 0){
    MPI_Send(c, arrsize, MPI_INT, 0, 0, MPI_COMM_WORLD);
    //printf("Sent\n");
  } else {

    int i, j;
    for(i = 1; i < wsize; i++){
      int lowerRange = rank * opspernode;
      int upperRange = lowerRange + opspernode;
      int *temp = malloc(arrsize*sizeof(int));
    //  printf("Rec'd\n");
      //MPI_Recv(temp, arrsize, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      for(j = lowerRange; j < upperRange; j++){
        final[j] = temp[j];
      }
      //printf("out\n");
    }
  }

  if(rank == 0){

    struct matrix D;
    initMatrix(&D, msize, msize);
    D.arr = final;
    printMatrix(&D);

  }
  //printMatrix(&A);
  //printf("%d\n", A.rows);

  MPI_Finalize();

  return 0;
}

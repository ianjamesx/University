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

int *addMatrices(int *a, int *b, int n){

  int i;
  int *c = malloc(n*sizeof(int));
  for(i = 0; i < n; i++){
    c[i] = a[i] + b[i];
  }

  return c;

}

int *subtractMatrices(int *a, int *b, int n){

  int i;
  int *c = malloc(n*sizeof(int));
  for(i = 0; i < n; i++){
    c[i] = a[i] - b[i];
  }

  return c;

}

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //have root node init matri

  int opspernode;
  int *a, *b, *c;

  struct matrix C;

  if(rank == 0){

    int num;
    sscanf(argv[1],"%d",&num);
    int msize = num;

    srand(time(0));
    struct matrix A;
    initMatrix(&A, msize, msize);
    printf("\nRandom Matrix A:\n");
    //printMatrix(&A);

    struct matrix B;
    initMatrix(&B, msize, msize);
    printf("Random Matrix B:\n");
    //printMatrix(&B);

    initMatrix(&C, msize, msize);

    /*
    The root node (e.g. 0, this one)
    will decide how much work each of the other nodes have to do
    will distribute enough data to complete a task to other nodes
    */

    opspernode = ceil((A.rows * A.cols) / wsize);
    if(opspernode < 1) opspernode = 1;

    //a = malloc(opspernode*sizeof(int));

    int i, j;
    for(i = 0; i < wsize; i++){

      //get the range of indices (essentially the blocks) that this node should cover
      int lowerRange = i * opspernode;
      int upperRange = lowerRange + opspernode;

      //create an array of data relevant to that node
      //we'll need to copy it over to each unique node
      a = malloc(opspernode*sizeof(int));
      b = malloc(opspernode*sizeof(int));

      int localindex = 0;
    //  printf("Copying data from %d to %d for rank %d\n", lowerRange, upperRange, i);
      for(j = lowerRange; j < upperRange; j++){
        a[localindex] = A.arr[j];
        b[localindex] = B.arr[j];
        localindex++;
      }
      //send those temporary arrays (unique node relavancy) to each
      //node we have
      MPI_Send(a, opspernode, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(b, opspernode, MPI_INT, i, 1, MPI_COMM_WORLD);

      //clear a and b since it'll get reallocated next iter
      free(a);
      free(b);

    }

    free(A.arr);
    free(B.arr);

  }

  //size of the array will be the number of ops each node has to cover
  //broadcast this, it will be the same for all nodes
  MPI_Bcast(&opspernode, 1, MPI_INT, 0, MPI_COMM_WORLD);

  //printf("ops: %d, rank: %d\n", opspernode, rank);
  a = malloc(opspernode*sizeof(int));
  b = malloc(opspernode*sizeof(int));
  MPI_Recv(a, opspernode, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  MPI_Recv(b, opspernode, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  //by this point all nodes (that arent root) should know their job
  //to use subtraction instead, uncomment the subtract matrices line,
  //remove addMatrices line

  //c = addMatrices(a, b, opspernode);
  c = subtractMatrices(a, b, opspernode);

  //printf("Output on %d, %d\n", rank, c[0]);
  //printf("Sending back to root on %d\n", rank);
  MPI_Send(c, opspernode, MPI_INT, 0, 2, MPI_COMM_WORLD);

  if(rank == 0){

    //now (on the root) we need to get all our data back from the nodes
    //and throw it into matrix C

    int i, j;
    for(i = 0; i < wsize; i++){
      c = malloc(opspernode*sizeof(int));
      MPI_Recv(c, opspernode, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      //printf("Recieve attempt from %d, %d\n", i, c[0]);
      int lowerRange = i * opspernode;
      int upperRange = lowerRange + opspernode;
      int localindex = 0;
      for(j = lowerRange; j < upperRange; j++){
        C.arr[j] = c[localindex];
        localindex++;
      }

    }

    printf("Ouptut matrix C:\n");
    //printMatrix(&C);

    free(C.arr);

  }

  free(a);
  free(b);
  free(c);

  MPI_Finalize();

  return 0;
}

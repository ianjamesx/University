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
  float *arr;
};

void initMatrix(struct matrix *A, int r, int c){
  A->rows = r;
  A->cols = c;
  int size = ((r+1)*(c+1))*sizeof(int);
  A->arr = malloc(size);

  int i, j;
  for(i = 1; i <= r; i++){
    for(j = 1; j <= c; j++){
      int index = INDEX(r,c, i, j);
      A->arr[index] = rand() % 100 + 1;
    }
  }
}

void printMatrix(struct matrix *A){

  printf("\n");
  int i, j;
  for(i = 1; i <= A->rows; i++){
    for(j = 1; j <= A->cols; j++){
      int index = INDEX(A->rows,A->cols, i, j);//(i*A->rows) + j;
      //printf("%.6f ", A->arr[index]);
    }
    puts("");
  }
  printf("\n");
}

int main(int argc, char **argv){

  int num;
  sscanf(argv[1],"%d",&num);
  int msize = num;

  int bsize = msize * msize;

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //have root node init matrix

  int a[bsize], final[bsize];

  if(rank == 0){

    srand(time(0));
    struct matrix A;
    initMatrix(&A, msize, msize);
    printf("\nRandom Matrix A:\n");
    //printMatrix(&A);

    //allocate temp memory
    int i;

    //copy to int arrays so we dont have to pass structs
    for(i = 0; i < bsize; i++){
      a[i] = A.arr[i];
    }

  }

  //broadcast to the world
  //the values of the random arrays generated
  MPI_Bcast(&a, bsize, MPI_INT, 0, MPI_COMM_WORLD);

  //how many ops each node will have to do
  int opspernode = ceil(msize / wsize),
      lowerRange = rank * opspernode,
      upperRange = lowerRange + opspernode;

  printf("Rank %d gets index %d through %d: work %d\n", rank, lowerRange, upperRange, opspernode);

  int i, j, l, n = msize;

  //printf("rank %d\n", rank);

  for(j = 1; j <= n; j++){

    //printf("rank %d\n", rank);

    for(i = 1; i <= n; i++){

      //printf("rank %d\n", rank);

      if(i != j){

        //c = A[i][j] / A[j][j];
        float tempij = a[INDEX(n,n,i,j)], tempji = a[INDEX(n,n,j,j)];
        float c = tempij / tempji;

        for(l = 1; l <= n+1; l++){

          //printf("rank %d i: %d, j: %d, l: %d\n", rank, i, j, l);

          float tempil = a[INDEX(n,n,i,l)], tempjl = a[INDEX(n,n,j,l)];
          int tempindex = INDEX(n,n,i,l);

          a[tempindex] = tempil - c*tempjl;

          if(tempindex > bsize){

            printf("index accessed > max index, %d, %d, %d\n", tempindex, bsize, rank);

          }

        }

      }

    }

  }

  if(rank == 0){

    struct matrix D;
    initMatrix(&D, msize, msize);
    for(i = 0; i < bsize; i++){
      D.arr[i] = a[i];
    }

    //printMatrix(&D);

    printf("Values in pivot positions:\n");

    for(i = 1; i <= n; i++){

      //printf("%.6f\n", );

    }

  }

/*
    float results[n+1];

    for(i=1; i<=n; i++){

        float temp1 = a[INDEX(n,n,i,(n+1))], temp2 = a[INDEX(n,n,i,i)];

        results[i] = temp1 / temp2;

        printf("\n x%d =  %f\n", i, results[i]);

    }

*/


  MPI_Finalize();

  return 0;
}

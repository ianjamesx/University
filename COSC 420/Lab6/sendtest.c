#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

#define INDEX(r,c,i,j) i*r + j

void initMatrix(float a[], int r, int c){

  int i, j;
  for(i = 0; i < r; i++){
    for(j = 0; j < c; j++){
      int index = INDEX(r, c, i, j);
      a[index] = rand() % 100 + 1;
    }
  }
}

void printMatrix(float a[], int r, int c){

  printf("\n");
  int i, j;
  for(i = 0; i < r; i++){
    for(j = 0; j < c; j++){
      int index = INDEX(r,c, i, j);
      //printf("Index %d\n", index);
      printf("%.2f\t", a[index]);
    }
    printf("\n");
  }
  printf("\n");
}

void printVector(float v[], int size){

  printf("\n");

  int i;
  for(i = 0; i < size; i++){
    printf("%.2f\n", v[i]);
  }
  printf("\n");

}

/*
void matrix_mul(float matrix1[3][3], float matrix2[3][1], float matrix3[3][1]){
    int i,j,k;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 1; j++){
            matrix3[i][j] = 0;
            for(k = 0; k < 3; k++){
                matrix3[i][j] += matrix1[i][k]*matrix2[k][j];
            }
        }
    }
}
*/

void matrvct(float matrix[], float vector[], float product[], int dim, int lower, int upper){

  int i, j, l;

  if(upper > dim) upper = dim;

  for(i = lower; i < upper; i++){
    product[i] = 0;

    for(j = 0; j < dim; j++){
      float m = matrix[INDEX(dim, dim, i, j)], v = vector[j];
      printf("Multiplying %.2f by %.2f\n", m, v);
      product[i] += (m * v);
    }
    printf("%d sum: %.2f\n\n", i, product[i]);
  }

}
/*
void matrix_mul(float matrix1[3][3], float matrix2[3][1], float matrix3[3][1]){
    int i,j,k;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 1; j++){
            matrix3[i][j] = 0;
            for(k = 0; k < 3; k++){
                matrix3[i][j] += matrix1[i][k]*matrix2[k][j];
            }
        }
    }
}
*/
float findmax(float a[], int msize){

  int i;
  float  maximum = a[0];
  for(i = 0; i < msize; i++){
    if(maximum < a[i]){
      maximum = a[i];
    }
  }

  return maximum;

}

int floatcomp(float a, float b){

  //small float comparison function
  //was not converging in some cases when original == was used

  double epsilon = .01f;
  if(fabs(a - b) < epsilon){
    return 1;
  }

  return 0;
}

int isEqual(float a[], float b[], int size){

  //we just want to see if these vectors are the same
  //no need to worry about indexing

  int i;

/*
  for(i = 0; i < size; i++){
    printf("%d  %.2f  %.2f\n",size, a[i], b[i]);
  }
  printf("\n\n");
*/

  for(i = 0; i < size; i++){
    if(floatcomp(a[i], b[i]) == 0){
      return 0;
    }
  }

  return 1;

}

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int l;

//  for(l = 0; l < 80; l++){


      int tempb[1];
      int i, j;
      tempb[0] = rank;
      printf("rank %d has value %d\n", rank, tempb[0]);

      if(rank != 0){

        MPI_Send(tempb, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

      } else {

        int fullbuf[wsize];

        for(i = 1; i < wsize; i++){

          int tempbuf[1];

          MPI_Recv(tempbuf, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          printf("Copying from rank %d, index %d, value %d\n", i, i, tempbuf[0]);
          fullbuf[i] = tempbuf[0];

        }

        for(i = 0; i < wsize; i++){
          printf("%d\n", fullbuf[i]);
        }

      }

//  }

  MPI_Finalize();

  return 0;

}

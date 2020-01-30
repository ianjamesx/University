
#define INDEX(n,i,j) i*n + j
#include "time.h"

//randomize matrix
void initMatrix(int a[], int n){

  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      int index = INDEX(n, i, j);
      a[index] = (rand() % 2);
    }
  }
}

void printMatrix(int a[], int n){

  printf("\n");
  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      int index = INDEX(n, i, j);
      //printf("Index %d\n", index);
      printf("%d\t", a[index]);
    }
    printf("\n");
  }
  printf("\n");

}

void transpose(int matrix[], int n){
  int i, j;
  for(i = 0; i < n; i++){
    for(j = i; j < n; j++){

      int ii = INDEX(n,i,j), jj = INDEX(n,j,i);

      int temp = matrix[ii];
      matrix[ii] = matrix[jj];
      matrix[jj] = temp;

    }
  }
}

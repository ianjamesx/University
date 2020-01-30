#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
  int size = (r*c)*sizeof(int);
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
      printf("%.2f ", A->arr[index]);
    }
    puts("");
  }
  printf("\n");
}

int PerformOperation(float *a, int n){

  int i, j, k = 0, c, flag = 0, m = 0;
  float pro = 0;

  // Performing elementary operations
  for (i = 0; i < n; i++)
  {

      if (a[INDEX(n,n,i,i)] == 0){

          c = 1;
          while (a[INDEX(n,n,(i+c),i)] == 0 && (i + c) < n)
              c++;
          if ((i + c) == n) {
              flag = 1;
              break;
          }

          for (j = i, k = 0; k <= n; k++){

            float temp = a[INDEX(n,n,j,k)];
            a[INDEX(n,n,j,k)] = a[INDEX(n,n,(j+c),k)];
            a[INDEX(n,n,(j+c),k)] = temp;
            printf("Swapping %.2f with %.2f\n",a[INDEX(n,n,j,k)], a[INDEX(n,n,(j+c),k)]);

          }

      }

      for (j = 0; j < n; j++) {

          // Excluding all i == j
          if (i != j) {

              // Converting Matrix to reduced row
              // echelon form(diagonal matrix)
              float pro = a[INDEX(n,n,j,i)] / a[INDEX(n,n,i,i)];

              for (k = 0; k <= n; k++)
                  a[INDEX(n,n,j,k)] = a[INDEX(n,n,j,k)] - (a[INDEX(n,n,i,k)]) * pro;
          }
      }
  }

  return flag;

}

int CheckConsistency(float *a, int n, int flag){

    int i, j;
    float sum;

    // flag == 2 for infinite solution
    // flag == 3 for No solution
    flag = 3;
    for (i = 0; i < n; i++){
        sum = 0;
        for (j = 0; j < n; j++)
            sum = sum + a[INDEX(n,n,i,j)];
        if (sum == a[INDEX(n,n,i,j)])
            flag = 2;
    }

    return flag;

}

int main(int argc, char **argv){

  //have root node init Matrix

  int n = 5;
  int arrsize = n * n;
  float a[arrsize];

  srand(time(0));
  struct matrix A;
  initMatrix(&A, n, n);
  printf("\nRandom Matrix A:\n");
  printMatrix(&A);

  //allocate temp memory
  int i;

  //copy to int arrays so we dont have to pass structs
  for(i = 0; i < arrsize; i++){
    a[i] = A.arr[i];
  }

  int f = PerformOperation(a, n);

  int flag;

  if(f == 1){
    flag = CheckConsistency(a,n,f);
  }

  printf("%d\n", flag);

  struct matrix B;
  initMatrix(&B, n, n);
  for(i = 0; i < arrsize; i++){
    B.arr[i] = a[i];
  }

  printMatrix(&B);

  return 0;

}

#include <stdlib.h>
#include <stdio.h>

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
      printf("%.2f ", A->arr[index]);
    }
    puts("");
  }
  printf("\n");
}

int main(int argc, char **argv){
    int i,j,k,n;

    if(argc < 2){
      return 0;
    }

    int bsize;
    sscanf(argv[1], "%d", &bsize);

    srand(time(0));
    struct matrix A;
    initMatrix(&A, msize, msize);

    float A[100][100], c, x[100];
    printf("\nEnter the size of matrix: ");
    scanf("%d",&n);
    printf("\nEnter the elements of augmented matrix row-wise:\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=(n+1); j++)
        {
            //printf(" A[%d][%d]:", i,j);
            A[i][j] = rand() % 10;
        }
    }

    for(i = 1; i <= n; i++){

      for(j = 1; j <=(n+1); j++){

        printf("%.2f ", A[i][j]);
      }
      printf("\n");
    }
    /* Now finding the elements of diagonal matrix */
    for(j=1; j<=n; j++)
    {
        for(i=1; i<=n; i++)
        {
            if(i!=j)
            {
                c=A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k];
                }
            }
        }
    }

    printf("\nSolved matrix:\n");

    for(i = 1; i <= n; i++){

      for(j = 1; j <=(n+1); j++){

        printf("%.2f ", A[i][j]);
      }
      printf("\n");
    }
    printf("\nThe solution is:\n");
    for(i=1; i<=n; i++)
    {
        x[i]=A[i][n+1]/A[i][i];
        printf("\n x%d=%f\n",i,x[i]);
    }
    return(0);
}

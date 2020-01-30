


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void printMatrix(float A[][20]){

  int i, j;
  for(i = 1; i <= 5; i++){
    for(j = 1; j <= 5; j++){

      printf("%.6f ", A[i][j]);
    }

    printf("\n");
  }
}

int main(){

    int i,j,k,n;
    float A[20][20],c,x[10];
    n = 5;

    for(i=1; i<=n; i++){

      for(j=1; j<=(n+1); j++){

        //printf(" A[%d][%d]:", i,j);
        //scanf("%f",&A[i][j]);
        A[i][j] = rand() % 100 + 1;
        //printf("%d\n", );

      }

    }

    printMatrix(A);
    printf("\n\n");
    for(j = 1; j <= n; j++){

      for(i = 1; i <= n; i++){

        if(i != j){

          c = A[i][j]/A[j][j];

          for(k = 1; k <= n+1; k++){

          //  printf("i: %d, j: %d, l: %d\n", i, j, k);

            A[i][k] = A[i][k] - c*A[j][k];

          }

        }

      }

    }

    printMatrix(A);

    printf("\nThe solution is:\n");
    for(i=1; i<=n; i++){

        x[i] = A[i][n+1] / A[i][i];

        printf("\n x%d =  %f\n", i, x[i]);

    }
    return(0);
}


/*
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void printMatrix(float A[][20]){

  int i, j;
  for(i = 0; i < 5; i++){
    for(j = 0; j < 5; j++){

      printf("%.6f ", A[i][j]);
    }

    printf("\n");
  }
}

int main(){

    int i,j,k,n;
    float A[20][20],c,x[10];
    n = 5;

    for(i=0; i<n; i++){

      for(j=0; j<n+1; j++){

        //printf(" A[%d][%d]:", i,j);
        //scanf("%f",&A[i][j]);
        A[i][j] = rand() % 100 + 1;
        //printf("%d\n", );

      }

    }

    printMatrix(A);
    printf("\n\n");
    for(j = 0; j < n; j++){

      for(i = 0; i < n; i++){

        if(i != j){

          c = A[i][j]/A[j][j];

          for(k = 0; k <n+1; k++){

            A[i][k] = A[i][k] - c*A[j][k];

          }

        }

      }

    }

    printMatrix(A);

    printf("\nThe solution is:\n");
    for(i=0; i<n; i++){

        x[i] = A[i][n+1] / A[i][i];

        printf("\n x%d = %f \n", i, x[i]);

    }
    return(0);
}
*/

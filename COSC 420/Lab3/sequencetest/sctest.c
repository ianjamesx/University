#include <stdlib.h>
#include <stdio.h>
int main()
{
    int i,j,k,n;
    float A[100][100],c,x[100];
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

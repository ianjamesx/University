// C Implementation for Gauss-Jordan
// Elimination Method
#include <stdlib.h>
#include <stdio.h>

#define M 10

// Function to print the matrix
void PrintMatrix(float a[][M], int n)
{

    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++)
          printf("%d ", a[i][j]);
        printf("\n");
    }
}

// function to reduce matrix to reduced
// row echelon form.
int PerformOperation(float a[][M], int n)
{
  int i, j, k = 0, c, flag = 0, m = 0;
  float pro = 0;

  // Performing elementary operations
  for (i = 0; i < n; i++)
  {
      if (a[i][i] == 0)
      {
          c = 1;
          while (a[i + c][i] == 0 && (i + c) < n)
              c++;
          if ((i + c) == n) {
              flag = 1;
              break;
          }
          for (j = i, k = 0; k <= n; k++){
            float temp = a[j][k];
            a[j][k] = a[j+c][k];
            a[j+c][k] = temp;
          }
      }

      for (j = 0; j < n; j++) {

          // Excluding all i == j
          if (i != j) {

              // Converting Matrix to reduced row
              // echelon form(diagonal matrix)
              float pro = a[j][i] / a[i][i];

              for (k = 0; k <= n; k++)
                  a[j][k] = a[j][k] - (a[i][k]) * pro;
          }
      }
  }
  return flag;
}

// Function to print the desired result
// if unique solutions exists, otherwise
// prints no solution or infinite solutions
// depending upon the input given.
void PrintResult(float a[][M], int n, int flag)
{
    printf("Result is : ");

    if (flag == 2)
      printf("INF");
    else if (flag == 3)
      printf("NO SOL");


    // Printing the solution by dividing constants by
    // their respective diagonal elements
    else {
        int i;
        for (i = 0; i < n; i++)
            printf("%d", a[i][n], a[i][i]);
    }
}

// To check whether infinite solutions
// exists or no solution exists
int CheckConsistency(float a[][M], int n, int flag)
{
    int i, j;
    float sum;

    // flag == 2 for infinite solution
    // flag == 3 for No solution
    flag = 3;
    for (i = 0; i < n; i++)
    {
        sum = 0;
        for (j = 0; j < n; j++)
            sum = sum + a[i][j];
        if (sum == a[i][j])
            flag = 2;
    }
    return flag;
}

// Driver code
int main()
{
  float a[M][M];

  int i, j;
  for(i = 0; i < M; i++){
    for(j = 0; j < M; j++){

      a[i][j] = (float)(rand() % 10);
    }

  }

    // Order of Matrix(n)
    int n = 3, flag = 0;

    PrintMatrix(a,n);

    // Performing Matrix transformation
    flag = PerformOperation(a, n);

    if (flag == 1)
        flag = CheckConsistency(a, n, flag);

    // Printing Final Matrix
    printf("Final Augumented Matrix is : ");
    PrintMatrix(a, n);
    printf("\n");

    // Printing Solutions(if exist)
    PrintResult(a, n, flag);

    return 0;
}

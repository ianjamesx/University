#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "csr.h"
#include "document.h"
#include "eigen.h"
#include "rbtree.h"

int main(int argc, char **argv){

  int i;
  int n = 6;
  int matrix[n*n];

  initMatrix(matrix, n);

  int hub[n];
  int authority[n];

  hits(matrix, authority, hub, n);

  for(i = 0; i < n; i++){
    printf("%d ", authority[i]);
  }
  printf("\n");

  for(i = 0; i < n; i++){
    printf("%d ", hub[i]);
  }

  printMatrix(matrix, n);

  struct CSRgraph graph;

  matrixtocsr(matrix, n, &graph);

  debugprint(graph);

  return 0;

}

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <math.h>


/*

MPI Gauss Jordan
Ian Thomas
*/

#define INDEX(r,c,i,j) i*r + j

void initMatrix(float *a, int r, int c){

  int i, j;
  for(i = 0; i < r; i++){
    for(j = 0; j < c+1; j++){
      int index = INDEX(r, c, i, j);
      a[index] = rand() % 100 + 1;
    }
  }
}

void printMatrix(float *a, int r, int c){

  printf("\n");
  int i, j;
  for(i = 0; i < r; i++){
    for(j = 0; j < c+1; j++){
      int index = INDEX(r,c+1, i, j);
      //printf("Index %d\n", index);
      printf("%.2f\t", a[index]);
    }
    printf("\n");
  }
  printf("\n");
}

/*

This algorithm is similar to pseudocode given

However, moreso follows a format found on this reference site:
https://www.codewithc.com/gauss-jordan-method-algorithm-flowchart/

pseudocode I stole from that site and implemented in C:

Do for k=1 to n
  Do for l=k+1 to n+1
    a[k][l] = a[k][l] / a[k][k]
  End for l
  Set a[k][k] = 1
  Do for i=1 to n
    if (i not equal to k) then,
  Do for j=k+1 to n+1
    a[i][j] = a[i][j] – (a[k][j] * a[i][k])
    End for j
  End for i
End for k

*/

void elim(int lower, int upper, float *a, int r, int c){

  int i, j, k;

  //printf("Working on row %d through %d\n", lower, upper);

  for(j=lower; j<upper; j++){

    for(i=0; i<c; i++){

      if(i!=j){

        int indexij = INDEX(r,c, i, j), indexjj = INDEX(r,c,j,j);

        float ratio = a[indexij] / a[indexjj];

        for(k=0; k<r+1; k++){

          int indexik = INDEX(r,c,i,k), indexjk = INDEX(r,c,j,k);
          a[indexik] = a[indexik] - ratio*a[indexjk];

        }

      }

    }

  }

}

int main(int argc, char **argv){

  //setup some mpi stuff
    int wsize, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int i,j,k,n;

    if(argc < 2){
      if(rank == 0){
        printf("aren't enough args\n");
      }
      MPI_Finalize();
      return 0;
    }

    //for inverses
    //we'll have to force the dimensions of the matrix to be the same

    int si, st; //si - width, st - length
    sscanf(argv[1], "%d", &si);
    //sscanf(argv[2], "%d", &st);
    st = si;

    int bsize = (si * st) + 1;
    float a[bsize];

    if(rank == 0){

      if(si < st){
        if(rank == 0){
          printf("Your args are incompatible with GJ\n");
        }
        MPI_Finalize();
        return 0;
      }

      srand(time(0));
      initMatrix(a, si, st);
      //printMatrix(a, si, st);

      //first lets append the inverse Identity matrix on the root

      int i, j, k;

      for(i = 0; i < si; i++){
        for(j = 0; j < st; j++){

          int indexjn = INDEX(n,n,i,(j+n));

          if(i == j){
            a[indexjn] = 1;
          } else {
            a[indexjn] = 0;
          }

        }

      }

    }

    //similar to matrix multiplication, first see if there are a small number of elements
    //if so, its not worth parallelizing

    if(si < 50){

      if(rank == 0){
        elim(0, si, a, si, st);

        for(i = 1; i <= n; i++){

          int tempindex = INDEX(n,n, i, i);
          float temp = a[tempindex];

          for(j = 1; j <= 2*si; j++){
        	  a[tempindex] = a[tempindex]/temp;
          }

        }

      }

    } else {

      int opspernode = ceil(si / wsize)+1,
          lowerRange = rank * opspernode,
          upperRange = lowerRange + opspernode;

    //  printf("rank %d has %d %d\n", rank, bsize, opspernode);

      //manually set last node to cover rest

      if(rank == (wsize -1)){
        upperRange = si;
      }

      //printf("lower: %d, upper: %d, ops: %d, rank: %d\n", lowerRange, upperRange, opspernode, rank);

      //the values of the random array generated
      MPI_Bcast(&a, bsize, MPI_INT, 0, MPI_COMM_WORLD);

      //printMatrix(a, si, st);

      elim(lowerRange, upperRange, a, si, st);

      if(rank != 0){

        //get the data we want to send
        int sendToRoot[opspernode*si];

        int lowcopy = si * rank,
            highcopy = lowcopy + si;

        for(i = lowcopy; i < highcopy; i++){
          sendToRoot[i] = a[i];
        }

        MPI_Send(sendToRoot, opspernode, MPI_INT, 0, 0, MPI_COMM_WORLD);

      } else {

        for(i = 1; i < wsize; i++){

          int tempBuffr[opspernode*si];

          int lowcopy = si * i,
              highcopy = lowcopy + si;

          //again, we force last node to do remainder of the work
          //need to adjust the copy

          if(i == (wsize - 1)){
            highcopy = bsize;
          }

          MPI_Recv(tempBuffr, (opspernode*si), MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          //printf("Receieved from %d, range %d through %d\n", i, currLowerRange, currUpperRange);

          for(j = lowcopy; j < highcopy; j++){
            //printf("Copying from rank %d, index %d, value %d\n", i, j, tempBuffr[j]);
            a[j] = tempBuffr[j];

          }

        }

      }

    }

    if(rank == 0){

      for(i = 1; i <= si; i++){

        int tempindex = INDEX(si,si, i, i);
        float temp = a[tempindex];

        for(j = 1; j <= 2*si; j++){
          a[tempindex] = a[tempindex]/temp;
        }

      }

      //for printing
/*
      for(i=0;i<si;i++){

        for(j=si;j <= 2*si;j++){

          printf("%0.3f\t",a[INDEX(n,n,i,j)]);

        }

        printf("\n");
      }
*/
    }

    MPI_Finalize();

    return 0;
}

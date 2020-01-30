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

    }

    MPI_Bcast(&a, bsize, MPI_INT, 0, MPI_COMM_WORLD);

    //first lets get an array we can broadcast and have other nodes grind away at
    //lets also grab some values that set ranges for nodes to work on for sub array k

    float temp[si+1];
    float ratio;

    int opspernode = ceil(st / wsize)+1,
        lowerRange = rank * opspernode,
        upperRange = lowerRange + opspernode;

    if(rank == (wsize -1)){
      upperRange = st+1;
    }

    for(j=0; j<si; j++){

      for(i=0; i<st; i++){

        MPI_Bcast(&a, bsize, MPI_INT, 0, MPI_COMM_WORLD);

        if(i!=j){

          //lets get the current row we need to work on
          //put them in a temp array
          //send them to other nodes to work

          float ratio;

          //once we have our data, use the ranges to perform row operations

          int indexij = INDEX(si,st, i, j), indexjj = INDEX(si,st,j,j);
          ratio = a[indexij] / a[indexjj];

          for(k=lowerRange; k<upperRange; k++){

            int indexik = INDEX(si,st,i,k), indexjk = INDEX(si,st,j,k);
            a[indexik] = a[indexik] - ratio*a[indexjk];

          }

          if(rank != 0){

            MPI_Send(&temp, si+1, MPI_INT, 0, ((j*si)+i), MPI_COMM_WORLD);

            //we'll have to recollect those row operations on the root

          } else {

            for(i = 1; i < wsize; i++){

              int tempBuffr[opspernode*si];

              //we can actually simulate what each thread's range would look like here:

              int lowcopy = si * i,
                  highcopy = lowcopy + si;

              //again, we force last node to do remainder of the work
              //need to adjust the copy

              if(i == (wsize - 1)){
                highcopy = bsize;
              }

              MPI_Recv(temp, si+1, MPI_INT, i, ((j*si)+i), MPI_COMM_WORLD, MPI_STATUS_IGNORE);

              //printf("Receieved from %d, range %d through %d\n", i, currLowerRange, currUpperRange);

              for(j = lowcopy; j < highcopy; j++){
                //printf("Copying from rank %d, index %d, value %d\n", i, j, tempBuffr[j]);
                a[j] = tempBuffr[j];

              }

            }

          }

        }

      }

    }

    //optionally, you can get the solution set by iterating
    //and dividing the pivot rows by the last element
    //e.g. for(i in r): ans = a[INDEX(r,c,i,r)] / a[INDEX(r,c,i,i)];
/*
    if(rank == 0){

      //for solution set
      for(i=0; i< si; i++){

          float ans = a[INDEX(si,si,i,si)]/a[INDEX(si,si,i,i)];

      }

    }
*/

    MPI_Finalize();

    return 0;
}

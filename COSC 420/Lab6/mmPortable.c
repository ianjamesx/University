#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

//#define INDEX(r,c,i,j) r*c + j
//#define ACCESS(A,i,j) A->arr[INDEX(A->rows, A->cols, i, j)]

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
      printf("%.1f\t", a[index]);
    }
    printf("\n");
  }
  printf("\n");
}


int main(int argc, char **argv){

  int num;
  sscanf(argv[1],"%d",&num);
  int msize = num;

  int bsize = msize * msize;

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //have root node init matrix

  float a[bsize], b[bsize], c[bsize];
  float final[bsize];

  if(rank == 0){

    srand(time(0));
    initMatrix(a, msize, msize);
    //printf("\nRandom Matrix A:\n");
    printMatrix(a, msize, msize);

    initMatrix(b, msize, msize);
    //printf("Random Matrix B:\n");
    printMatrix(b, msize, msize);
  }

  //how many ops each node will have to do
  int opspernode = ceil(msize / wsize),
      lowerRange = rank * opspernode,
      upperRange = lowerRange + opspernode;

  //printf("Rank %d gets index %d through %d: work %d\n", rank, lowerRange, upperRange, opspernode);
  //if not worth parallelizing (e.g. number of work per node wuold be very small) dont even try
  //previous testing showed sequential will be faster anyway

  if(msize < 50){

  if(rank == 0){

    int i = 0, j = 0, l = 0;
      for(i = 0; i < msize; i++){

        c[INDEX(msize,msize,i,j)] = 0;

        for(j = 0; j < msize; j++){
          for(l = 0; l < msize; l++){

          c[INDEX(msize,msize,i,j)] += a[INDEX(msize,msize,i,l)] * b[INDEX(msize,msize,l,j)];
        }
      }
    }
  }

  } else {

    //broadcast to the world
    //the values of the random arrays generated
    MPI_Bcast(&a, bsize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, bsize, MPI_INT, 0, MPI_COMM_WORLD);

    int i, j, l;

    //have each node work on their respective ranges
    for(i = lowerRange; i < upperRange; i++){

        c[INDEX(msize,msize,i,j)] = 0;
        for(j = 0; j < msize; j++){
          for(l = 0; l < msize; l++){
            c[INDEX(msize,msize,i,j)] += (a[INDEX(msize,msize,i,l)] * b[INDEX(msize,msize,l,j)]);
          }
          //printf("Rank %d modified spot %d, val %d\n", rank, INDEX(msize, msize, i, j), c[INDEX(msize,msize,i,j)]);
        }
     }

    if(rank != 0){

      //get the data we want to send
      int sendToRoot[opspernode];

      int lowcopy = msize * rank,
          highcopy = lowcopy + msize;

      for(i = lowcopy; i < highcopy; i++){
        sendToRoot[i] = c[i];
      }

      MPI_Send(sendToRoot, opspernode, MPI_INT, 0, 0, MPI_COMM_WORLD);

    } else {

      for(i = 1; i < wsize; i++){

        int tempBuffr[(opspernode*msize)];

        int lowcopy = msize * i,
            highcopy = lowcopy + msize;

        MPI_Recv(tempBuffr, (opspernode*msize), MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        //printf("Receieved from %d, range %d through %d\n", i, currLowerRange, currUpperRange);

        for(j = lowcopy; j < highcopy; j++){
          //printf("Copying from rank %d, index %d, value %d\n", i, j, tempBuffr[j]);
          c[j] = tempBuffr[j];
        }

      }

    }

  }

  //finally, collect in a matrix
  if(rank == 0){
    printMatrix(c, msize, msize);
  }

  MPI_Finalize();

  return 0;
}

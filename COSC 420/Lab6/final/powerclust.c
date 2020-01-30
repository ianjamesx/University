#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

#define INDEX(r,c,i,j) i*r + j

void initMatrix(float a[], int r, int c){

  int i, j;
  for(i = 0; i < r; i++){
    for(j = 0; j < c; j++){
      int index = INDEX(r, c, i, j);
      a[index] = rand() % 100 + 1;
    }
  }
}

void printMatrix(float a[], int r, int c){

  printf("\n");
  int i, j;
  for(i = 0; i < r; i++){
    for(j = 0; j < c; j++){
      int index = INDEX(r,c, i, j);
      //printf("Index %d\n", index);
      printf("%.2f\t", a[index]);
    }
    printf("\n");
  }
  printf("\n");
}

void printVector(float v[], int size){

  printf("\n");

  int i;
  for(i = 0; i < size; i++){
    printf("%.2f\n", v[i]);
  }
  printf("\n");

}

//we disregard my matrix multiplication calculator
//we only do matrix vector products here
//faster to just redo it
void matrvct(float matrix[], float vector[], float product[], int dim, int lower, int upper){

  int i, j, l;

  if(upper > dim) return;

  for(i = lower; i < upper; i++){
    product[i] = 0;

    for(j = 0; j < dim; j++){
      float m = matrix[INDEX(dim, dim, i, j)], v = vector[j];
      //printf("Multiplying %.2f by %.2f\n", m, v);
      product[i] += (m * v);
    }
    //printf("%d sum: %.2f\n\n", i, product[i]);
  }

}

float findmax(float a[], int msize){

  int i;
  float  maximum = a[0];
  for(i = 0; i < msize; i++){
    if(maximum < a[i]){
      maximum = a[i];
    }
  }

  return maximum;

}

int floatcomp(float a, float b){

  //small float comparison function
  //was not converging in some cases when original == was used

  double epsilon = .01f;
  if(fabs(a - b) < epsilon){
    return 1;
  }

  return 0;
}

int isEqual(float a[], float b[], int size){

  //we just want to see if these vectors are the same
  //no need to worry about indexing

  int i;

/*
  for(i = 0; i < size; i++){
    printf("%d  %.2f  %.2f\n",size, a[i], b[i]);
  }
  printf("\n\n");
*/

  for(i = 0; i < size; i++){
    if(floatcomp(a[i], b[i]) == 0){
      return 0;
    }
  }

  return 1;

}

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  clock_t begin = clock();

  int msize = 25000;
  int bsize = msize * msize;

  float eigenValue;
  int i,j,k;
  float matrix[bsize], vector[msize], res[msize];

  //set operations each node is responsible for
  int opspernode = (msize / wsize),
      lowerRange = rank * opspernode,
      upperRange = lowerRange + opspernode;

  //force last node to cover remainder left out by integer divsion cutoff
  if(rank == wsize - 1){
    upperRange = msize;
  }

  //uncomment to see which ranges each node will cover
  //printf("Rank %d will cover %d through %d\n", rank, lowerRange, upperRange);

  if(rank == 0){
    //populate matrix with random values on root, we'll broadcast later
    srand(time(0));
    initMatrix(matrix, msize, msize);
    matrix[bsize] = 0.0;
    //printMatrix(matrix, msize, msize);
  }

  //keep in mind, vector and res are just arrays
  //we can treat them as such, do not need to INDEX them
  for(i = 0; i < msize; i++){
    vector[i] = 1.0; //'let x be all 1 vector in appropriate dimmension'
    res[i] = 0.0;
  }

  //if we have more nodes than rows in our matrix, just do it on root
  //it will be much faster
  //we arbitrarily set to 50 to make it easy

  if(msize < 50){

    //printf("wsize > msize\n");

    if(rank == 0){

      matrvct(matrix, vector, res, msize, 0, msize);
      //printVector(vector, msize);
      //printVector(res, msize);

      while(1){

        matrvct(matrix, vector, res, msize, 0, msize);

        eigenValue = findmax(res, msize);
        for(i = 0; i < msize; i++){
          res[i] /= eigenValue;
        }

        if(isEqual(vector, res, msize) == 1){
          break;
        }

        for(i = 0; i < msize; i++){
          vector[i] = res[i];
        }

      }

      printf("largest eigenvalue = %.2f", eigenValue);
      printf("\neigenvector:\n");
      printVector(res, msize);

    }

    MPI_Finalize();
    return 0;
  }

  MPI_Bcast(&matrix, bsize, MPI_INT, 0, MPI_COMM_WORLD);

  int done = 0;

  while(1){

    matrvct(matrix, vector, res, msize, lowerRange, upperRange);

    if(rank != 0){

      //get the data we want to send
      int sendToRoot[opspernode];

      int lowcopy = opspernode * rank,
          highcopy = lowcopy + opspernode;

      for(i = lowcopy; i < highcopy; i++){
      //  printf("Sending from rank %d, index %d, value %.2f\n", rank, i, res[i]);
        sendToRoot[i] = res[i];
      }

      MPI_Send(sendToRoot, opspernode, MPI_INT, 0, 0, MPI_COMM_WORLD);

    } else {

      for(i = 1; i < wsize; i++){

        int tempBuffr[opspernode];

        int lowcopy = opspernode * i,
            highcopy = lowcopy + opspernode;

        if(i == wsize -1){
          highcopy = msize;
        }

        MPI_Recv(tempBuffr, opspernode, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        //printf("Receieved from %d, range %d through %d | ops: %d\n", i, lowcopy, highcopy, opspernode);

        for(j = lowcopy; j < highcopy; j++){
        //  printf("Receieved from rank %d, index %d, value %.2f\n", i, j, tempBuffr[j]);
          res[j] = tempBuffr[j];
        }

      }

    }

    //once we rebuilt the result vector, update all other nodes of it
    MPI_Bcast(&res, msize, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
      eigenValue = findmax(res, msize);
      for(i = 0; i < msize; i++){
        res[i] /= eigenValue;
      }
      if(isEqual(vector, res, msize) == 1){
        //set this converge flag to 1
        done = 1;
      }
    }

    //have root tell other nodes if we finish up
    MPI_Bcast(&done, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(done == 1){
      break;
    }

    for(i = 0; i < msize; i++){
      vector[i] = res[i];
    }

  }

  if(rank == 0){

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    //uncomment to see the output (disabled for large input testing)

    printf("largest eigenvalue = %.2f\n", eigenValue);
/*    printf("\nsome eigenvector: \n");
    printVector(res, msize);
*/
  }

  MPI_Finalize();

  return 0;

}

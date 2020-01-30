#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

/*

Euler project, #85

There is no coordinate grid that can fit two mil rectangles
find the closest area that can fit a number of rectangles closest to 2 mil.

*/

int rects(int xMax, int yMax){

  //figure out how many rectangles we can shove into
  //an xMax-by-yMax grid

  int rcount = 0, i, j;

  for (i = 0; i < xMax; i++){
    for (j = 0; j < yMax; j++){
      rcount += (xMax - i) * (yMax - j);
    }
  }

  return rcount;

}

int main(int argc, char **argv){

  int wsize, rank;
  clock_t begin;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0){
    clock_t begin = clock();
  }

  //setup for all nodes
  int i, j, approxmax = 0, approxmaxrects = 0;
  int tar = 2000000;
  int maxdim = ceil(sqrt(tar));

  //array of data to send to root to compare, see which node did best
  int compdata[2];

  //printf("Rank %d will stride by %d\n", rank, wsize);

  //stride by wsize
  //we need to use a stride to evenly distribute work throughout nodes
  //smaller values of i call rects() with smaller values
  //leading to load unbalance
  //stride fixes this

  for (i = rank; i < maxdim; i += wsize){
    for (j = i; j < maxdim; j++){

      int r = rects(i,j);

      if (abs(approxmaxrects - tar) > abs(r - tar)){

        approxmax = (i * j);
        approxmaxrects = r;

      }

      //if we go over our tar (of 2 mil rects)
      //we can just leave
      if (r > tar){
        //printf("Rank %d leaving party\n", rank);
        break;
      }

    }

  }

  //printf("Rank %d largest number of rectangles: %d\n", rank, approxmaxrects);

  if(rank != 0){

    //pack up and send this nodes results to the root for comparison

    compdata[0] = approxmaxrects;
    compdata[1] = approxmax;
    MPI_Send(&compdata, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);

  } else {

    int rectcomp[wsize*2];
    rectcomp[0] = approxmaxrects;
    rectcomp[1] = approxmax;

    //collect results

    int temp[2];
    for(i = 1; i < wsize; i++){

      //store results from each node in rectcomp

      MPI_Recv(&temp, 2, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      int currindex = i * 2; //find indices to store results on root
      rectcomp[currindex] = temp[0];
      rectcomp[currindex+1] = temp[1];

    }

    //compare each nodes result
    //see which one is closest to our target val
    int closestindex = 0;
    for(i = 0; i < wsize*2; i += 2){
      if(abs(rectcomp[i] - tar) < abs(rectcomp[closestindex] - tar)){
        closestindex = i;
      }
    }

    printf("The closest area to hold ~2 mil rectangles: %d\n", rectcomp[closestindex+1]);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Finished in %.3f seconds\n", time_spent);

  }

  MPI_Finalize();

  return 0;

}

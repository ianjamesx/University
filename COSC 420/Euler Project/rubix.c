#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

/*

Euler project, #599

READ THIS PART:
all cube operations (move front vertically, move side horizonally, move face clockwise) work
all functions take the cube, and the index of whichever side (as 2x2x2) as params

goal: find way to do every (all 3.6 mil) unique rubiks cube moves for a distinct colouring
and store them in an array so we can compare them later (use saveRubikState(...))

I've been testing by running my brute force alg, then doing some random moves (see lines 402-407)
then comparing with compareToSaves to see if we get a match (we sometimes do, sometimes dont)
goal is to always get a match (unless we change the entire cubes colouring)

some testing has been done, but not successfully (yet)

good luck,
-Ian

*/

struct Cubelet {

  int faces[3]; //colors of cubelet faces
  int id; //id is only used for debugging, so we can track a cubelet during cube shifts

};


/*
print the facade (coloring) of each individual cubelet
*/
void printfacade(struct Cubelet cube[][2][2]){

  int i, j, l;
  for(i = 0; i < 2; i++){
    for(j = 0; j < 2; j++){

      printf("[ ");
      for(l = 0; l < 3; l++){
        printf(" %d ", cube[i][j][0].faces[l]);
      }
      printf(" ]\n");

      printf("[ ");
      for(l = 0; l < 3; l++){
        printf(" %d ", cube[i][j][1].faces[l]);
      }
      printf(" ]\n");

    }
  }

}

/*
print unique id of cubelets
*/

void printcubelets(struct Cubelet cube[][2][2]){

  int i, j, l;
  for(i = 0; i < 2; i++){
    for(j = 0; j < 2; j++){
      printf("%d %d\n", cube[i][j][0].id, cube[i][j][1].id);
    }
  }

}

/*
save the colors of the rubiks cube in an array
basically make an exact copy of the cube at this point in time
*/

void saveRubikState(struct Cubelet cube[][2][2], int save[][24], int move){

  printf("move %d\n", move);

  int i, j, l, k;
  int counter = 0;
  //manually store facade data from 3d array into 1d
  for(i = 0; i < 2; i++){ //iter dimmensions of cube
    for(j = 0; j < 2; j++){ //iter rows of cube
      for(l = 0; l < 2; l++){ //iter cubelets in row
        for(k = 0; k < 3; k++){ //iter color faces of cubelet
          save[move][counter] = cube[i][j][l].faces[k];
          counter++;
        }
      }
    }
  }
}

void searchArr(int arr[], int size, int stride, int np){

  int i, j;
  for(i = 0; i < size; i += stride){
    for(j = i; j < size; j++){
      int curr = np * i;
    }
  }

}

void permutateArr(int arr[], int size, int stride, int nc){

  int i, j, l;
  for(i = 0; i < size; i += stride){

    int currindex = nc * i;
    for(j = currindex; j < (currindex+nc); j++){
      for(l = j; l < (currindex+nc); l++){


      }
    }
  }

}

void swap(int *x, int *y){

  int temp = *x;
  *x = *y;
  *y = temp;

}

void permute(int arr[], int fullarr[][4], int curr, int max, int fullsize, int *iter, int nc){

  int i;
  if (curr == max){

    int currentwrite = (*iter) * nc;
    int localindex = 0;
    for(i = currentwrite; i < currentwrite + nc; i++){
      printf("copying fullarr %d = arr %d\n", i, arr[localindex]);
      fullarr[i] = arr[localindex];
      localindex++;
    }

  } else {

    (*iter)++;
    for(i = curr; i <= max; i++){
      swap(&arr[curr], &arr[i]);
      permute(arr, fullarr, curr+1, max, fullsize, iter, nc);
      swap(&arr[curr], &arr[i]);
    }

  }
}

/*
compare the current rubiks cube state to the saved states
if we get a match return 1
if not, return 0
*/
int compareToSaves(struct Cubelet cube[][2][2], int save[][24], int numSaves){

  //get the save data for the cubes current state (for easier comparison)
  int currstate[1][24];
  saveRubikState(cube, currstate, 0);

  //search movement saves for a match
  int i, j, match;
  for(i = 0; i < numSaves; i++){
    match = 1;
    for(j = 0; j < 24; j++){
      if(currstate[0][j] != save[i][j]){
        match = 0;
      }
    }
    if(match == 1){
      return 1; //if we found at least one match in saves, return 1
    }
  }

  return 0; //no matches found
}

int factorial(int n){
  int fac = 1, i;
  for (i = 2; i <= n; i++){
      fac *= i;
  }
  return fac;
}

int power(int b, int p){

  int i, pow = 1;
  for(i = p; i > 0; i--){
    pow *= b;
    printf("pow: %d\n", pow);
  }

  return pow;
}

/*

rubiks cube movement operations

essentially, there are only three operations that you can perform (when viewing from one distinct angle)
-move the front downwards vertically
-move the side to the left horizonally
-move a face clockwise

we do not need to worry about opposite directions as they will be reached
with enough iterations

Since we have a 2x2x2, we can simply pass in which side/level/face we
want to move (no need to worry about equaters)

loops would not be easy to use here, since the cube is small
we can simply set the movements manually through indices

*/

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int dim = 2;
  int colors = 2;
  int numCubeletes = dim*dim*dim;

  if(rank == 0){

    int numPermutes = factorial(numCubeletes);
    int arrsize = numPermutes * numCubeletes;

    printf("Number permutations: %d, Arr size: %d\n", numPermutes, arrsize);

    int permutations[arrsize];

    int nc = 3 * colors;
    int colors[nc];

    int arr[4] = {0,1,2,4};

    int fullarr[factorial(4)*10][4];

    int count = 0;

    permute(arr, fullarr, 0, 4, factorial(4)*5, &count, nc);

    int i, j;
    for(i = 0; i < factorial(4); i += 4){
      for(j = i; j < i+4; j++){
        printf("%d \n", fullarr[j]);
      }
      printf("\n");
    }

    printf("%d\n", count);

  }

  MPI_Finalize();

  return 0;

}

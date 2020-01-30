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

//define some functions up here, they all call each other and need previous definitions

void bruteforceAllRubiks(struct Cubelet cube[][2][2], int *count, int save[][24]);
void bruteforceFC(struct Cubelet cube[][2][2], int *count, int save[][24]);
void bruteforceSH(struct Cubelet cube[][2][2], int *count, int save[][24]);
void bruteforceFV(struct Cubelet cube[][2][2], int *count, int save[][24]);


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

void assignCubeFacade(struct Cubelet *c1, struct Cubelet c2){

  //overwrite c1's facade with c2's
  //c1 is a pointer as that is the one we want to modify

  int k;
  for(k = 0; k < 3; k++){
    c1->faces[k] = c2.faces[k];
  }

  c1->id = c2.id; //and also its ID

}

void moveFrontVertically(int side, struct Cubelet cube[][2][2]){

  struct Cubelet temp1 = cube[0][0][side], temp2 = cube[0][1][side],
      temp3 = cube[1][0][side], temp4 = cube[1][1][side];

  assignCubeFacade(&cube[0][0][side], temp4);
  assignCubeFacade(&cube[0][1][side], temp1);
  assignCubeFacade(&cube[1][0][side], temp2);
  assignCubeFacade(&cube[1][1][side], temp3);

}

void moveSideHorizontally(int level, struct Cubelet cube[][2][2]){

  struct Cubelet temp1 = cube[level][0][0], temp2 = cube[level][0][1],
      temp3 = cube[level][1][0], temp4 = cube[level][1][1];

  assignCubeFacade(&cube[level][0][0], temp3);
  assignCubeFacade(&cube[level][0][1], temp1);
  assignCubeFacade(&cube[level][1][0], temp4);
  assignCubeFacade(&cube[level][1][1], temp2);

}

void moveFaceClockwise(int face, struct Cubelet cube[][2][2]){

  struct Cubelet temp1 = cube[0][face][0], temp2 = cube[0][face][1],
      //apply to opposite end of the lower dimension of cube
      temp3 = cube[1][abs(face-1)][0], temp4 = cube[1][abs(face-1)][1];

  assignCubeFacade(&cube[0][face][0], temp3);
  assignCubeFacade(&cube[0][face][1], temp1);
  assignCubeFacade(&cube[1][abs(face-1)][0], temp4);
  assignCubeFacade(&cube[1][abs(face-1)][1], temp2);

}


/*
BEGIN BRUTE FORCE TESTING ATTEMPT
*/

void bruteforceFC(struct Cubelet cube[][2][2], int *count, int save[][24]){

  int i, j;
  for(i = 0; i < 4; i++){
    for(j = 0; j < 2; j++){
      moveFaceClockwise(j, cube);
      saveRubikState(cube, save, (*count));
      (*count)++;
    }
  }

}


void bruteforceSH(struct Cubelet cube[][2][2], int *count, int save[][24]){

  int i, j;
  for(i = 0; i < 4; i++){
    for(j = 0; j < 2; j++){
      moveSideHorizontally(j, cube);
      bruteforceFC(cube, count, save);
      saveRubikState(cube, save, (*count));
      (*count)++;
    }
  }

}

void bruteforceFV(struct Cubelet cube[][2][2], int *count, int save[][24]){

  int i, j;
  for(i = 0; i < 4; i++){
    for(j = 0; j < 2; j++){
      moveFrontVertically(j, cube);
      bruteforceSH(cube, count, save);
      saveRubikState(cube, save, (*count));
      (*count)++;
    }
  }

}

void bruteforceAllRubiks(struct Cubelet cube[][2][2], int *count, int save[][24]){

}

/*
END BRUTE FORCE TESTING
*/

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int dim = 2;
  int colors = 2;
  int numcubeletes = dim*dim*dim;

  if(rank == 0){

    struct Cubelet cube[dim][dim][dim];

    int i, j, l;
    int counter = 0;
    for(i = 0; i < dim; i++){
      for(j = 0; j < dim; j++){
        for(l = 0; l < dim; l++){
          int col1 = rand() % 2, col2 = rand() % 2, col3 = rand() % 2;
          cube[i][j][l].faces[0] = col1;
          cube[i][j][l].faces[1] = col2;
          cube[i][j][l].faces[2] = col3;
          cube[i][j][l].id = counter;
          counter++;
        }
      }
    }

    int count = 0;

    int save[5000][24];
/*
    printcubelets(cube);

    storeRubiks(cube, save, 0);
    moveFrontVertically(0, cube);
    storeRubiks(cube, save, 1);

    printcubelets(cube);
*/

    //take initial cube save
    saveRubikState(cube, save, 0);
    count++;

    bruteforceAllRubiks(cube, &count, save);

    printfacade(cube);

    printf("\n\n");

    for(i = 0; i < 3; i++){

      for(j = 0; j < 24; j++){

        printf("%d ", save[i][j]);

      }

      printf("\n");

    }

    //some random moves to see if we can find a case that isnt stored

    moveFrontVertically(0, cube);
    moveFrontVertically(0, cube);
    moveFrontVertically(0, cube);
    moveFrontVertically(1, cube);
    moveSideHorizontally(1, cube);
    moveSideHorizontally(1, cube);
    moveFaceClockwise(1, cube);

    int match = compareToSaves(cube, save, count);

    printf("match status: %d\n", match);
    printf("count: %d\n", count);

    printf("\n");

    //printf("count: %d\n", count);

    //printfacade(cube);

    //printcubelets(cube);

/*
    printcubelets(cube);

    for(i = 0; i < 3; i++){

      printf("\nITER %d\n", i);

      moveFrontVertically(0, cube);
      //moveSideHorizontally(0, cube);
      //moveFaceClockwise(1, cube);

      printf("\n");

      printcubelets(cube);

    }
*/
    //printfacade(cube);

  }

  MPI_Finalize();

  return 0;

}

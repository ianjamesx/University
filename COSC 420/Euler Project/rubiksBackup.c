#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

/*

Euler project, #599

*/

struct Cubelet {
  int faces[3];
}

void printcube(int cube[][2][2]){

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
void printcubevoid(int cube[][2][2]){

  printf("[ [ [%d %d],\n", cube[0][0][0], cube[0][0][1]);
  printf("    [%d %d] ]\n", cube[0][1][0], cube[0][1][1]);
  printf("  [ [%d %d],\n", cube[1][0][0], cube[1][0][1]);
  printf("    [%d,%d] ] ]\n", cube[1][1][0], cube[1][1][1]);
}
*/

/*

rubiks cube movement operations

essentially, there are only three operations that you can perform
-move the front downwards vertically
-move the side to the left horizonally
-move a face clockwise

we do not need to worry about opposite directions as they will be reached
with enough iterations

Since we have a 2x2x2, we can simply pass in which side/level/face we
want to move

for loops would not be easy to use here, since the cube is small
we can simply set the movements manually through indices

*/

void moveFrontVertically(int side, int cube[][2][2]){

  int temp1 = cube[0][0][side], temp2 = cube[0][1][side],
      temp3 = cube[1][0][side], temp4 = cube[1][1][side];

  cube[0][0][side] = temp4;
  cube[0][1][side] = temp1;
  cube[1][0][side] = temp2;
  cube[1][1][side] = temp3;

}

void moveSideHorizontally(int level, int cube[][2][2]){

  int temp1 = cube[level][0][0], temp2 = cube[level][0][1],
      temp3 = cube[level][1][0], temp4 = cube[level][1][1];

  cube[level][0][0] = temp3;
  cube[level][0][1] = temp1;
  cube[level][1][0] = temp4;
  cube[level][1][1] = temp2;

}

void moveFaceClockwise(int face, int cube[][2][2]){

  int temp1 = cube[0][face][0], temp2 = cube[0][face][1],
      //apply to opposite end of the lower dimension of cube
      temp3 = cube[1][abs(face-1)][0], temp4 = cube[1][abs(face-1)][1];

  cube[0][face][0] = temp3;
  cube[0][face][1] = temp1;
  cube[1][abs(face-1)][0] = temp4;
  cube[1][abs(face-1)][1] = temp2;

}

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int dim = 2;
  int colors = 2;
  int numcubeletes = dim*dim*dim;

  if(rank == 0){

    Cubelet cube[dim][dim][dim];

    int i, j, l;
    int counter = 0;
    for(i = 0; i < dim; i++){
      for(j = 0; j < dim; j++){
        for(l = 0; l < dim; l++){
          cube[i][j][l].faces[0] = 1;
          cube[i][j][l].faces[1] = 2;
          cube[i][j][l].faces[2] = 3;
          counter++;
        }
      }
    }

    printcube(cube);

    //moveFrontVertically(0, cube);
    //moveSideHorizontally(0, cube);
    moveFaceClockwise(1, cube);

    printf("\n\n");

    printcube(cube);

  }

  MPI_Finalize();

  return 0;

}

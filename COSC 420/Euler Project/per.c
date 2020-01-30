#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

/*

here is some legacy code from the first version
where cubes where represented as 3d arrays, brute forced each move
highly innefficient, not functional, was scrapped for this solution

*/
/*

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
*/

/*

end legacy code

newer version uses combinatorics to more efficiently brute force
all permutations and compares them

*/

void storePermutation(int arr[], int cube[][8], int n, int curr){
  int i;
  for(i = 0; i < n; i++){
    cube[curr][i] = arr[i];
  }
}

void init_array(int arr[], int n){
  int i;
  for(i = 0; i < n; i++){
    arr[i] = i;
  }
}

void print_array(int arr[], int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void swap(int *x, int *y){
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
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
    //printf("pow: %d\n", pow);
  }

  return pow;
}

void permute(int arr[], int cube[][8], int start, int end, int n, int *curr){
  if(start == end){
    storePermutation(arr, cube, n, (*curr));
    (*curr)++;
    return;
  }
  int i;
  for(i = start; i < end; i++){
    swap((arr + start), (arr + i));
    permute(arr, cube, start + 1, end, n, curr);
    swap((arr + i), (arr + start));
  }
}

/*
algorithm for generating permutations with repetitions allowed
thanks to rosettacode.org
*/

int colorsPairs(int arr[][3], int colors){

  int curr = 0, temp, numbers = 3;
	int a[numbers+1], upto = colors, temp2;
  int i, j;
	for( temp2 = 1 ; temp2 <= numbers; temp2++){
		a[temp2]=1;
	}
	a[numbers]=0;
	temp=numbers;
	while(1){
		if(a[temp]==upto){
			temp--;
			if(temp==0)
				break;
		}
		else{
			a[temp]++;
			while(temp<numbers){
				temp++;
				a[temp]=1;
			}

			for( temp2 = 1 ; temp2 <= numbers; temp2++){
				//printf("%d ", a[temp2]);
        arr[curr][temp2-1] = a[temp2];
			}
      curr++;
      //printf("| %d\n", curr);
		}
	}

  printf("curr %d\n", curr);
  return curr;

}

/*
  acol - actual colorings
  pcol - potential colorings
*/

void assigncoloring(int acol[][3], int pcol[][3], int cubeindex, int colorindex){

  //printf("assigning coloring %d to cubelet %d\n", colorindex, cubeindex);

  int i;
  //printf("cube %d: ", cubeindex);
  for(i = 0; i < 3; i++){
    acol[cubeindex][i] = pcol[colorindex][i];
    //printf("%d ", acol[colorindex][i]);
  }
  //printf("\n");

}

void printcurrfaces(int currfaces[][3]){

  int i, j;
  for(i = 0; i < 8; i++){
    printf("currface: ");
    for(j = 0; j < 3; j++){
      printf("%d ", currfaces[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int comparecolorings(int cube[][8], int colorings[][3], int c1, int c2){

  int i, j, matched = 1;
  for(i = 0; i < 8; i++){

    int c1facade = cube[c1][i];
    int c2facade = cube[c2][i];

    for(j = 0; j < 3; j++){
      if(colorings[c1facade][j] != colorings[c2facade][j]){
        matched = 0;
      }
    }
  }

  return matched;
}

//do not need to pass cubelets, will always be 8 color cubeletes
int compareCubes(int cube[][8], int colorings[][3], int permutes){

  int i, j, l;

  for(i = 0; i < permutes; i++){
    for(j = i+1; j < permutes; j++){

      if(comparecolorings(cube, colorings, i, j) == 1){
        //printf("cube recreated\n");
        return 1; //return if we found a match, this cube can be recreated
      }

    }
  }

  return 0; //cube could not be recreated, is essentially distinct

}

void facade(int pairs[][3], int colours[][3], int currentindex, int currentcolour, int c, int cube[][8], int np, int *distinct){

  int i;

  //colorshift
  for(i = 0; i < 3; i++){
    colours[currentindex][i] = pairs[currentcolour][i];
  }

  //printf("%d %d\n", currentindex, currentcolour);
  printcurrfaces(colours);

  currentcolour++;
  if(currentcolour == 8){
    currentindex++;
    currentcolour = 0;
  }

  if(currentindex == c){
    return;
  }

  //printf("comparing...\n");
  int res = compareCubes(cube, colours, np); //compare to other permutations
  if(res == 0){
    //(*distinct)++;
  }

  facade(pairs, colours, currentindex, currentcolour, c, cube, np, distinct);

}

int main(int argc, char** argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //if(rank == 0){

    int numCubeletes = 8;

    int numPermutes = factorial(numCubeletes);
    int colors = 2;

    int arr[numCubeletes];
    int cube[numPermutes][numCubeletes];

    int col[numCubeletes][3];

    init_array(arr, numCubeletes);

    int count = 0;
    permute(arr, cube, 0, numCubeletes, numCubeletes, &count);

    int fbuffer = power(colors, 3);

    int facepairs[fbuffer][3];

    int paircount = colorsPairs(facepairs, colors);

    //printf("%d\n", paircount);

    int i, j, l;
  /*
    for(i = 0; i < numPermutes; i++){
      for(j = 0; j < numCubeletes; j++){
        printf("%d ", cube[i][j]);
      }
      printf(" | %d\n", i);
    }

    for(i = 0; i < paircount; i++){
      for(j = 0; j < 3; j++){
        printf("%d ", facepairs[i][j]);
      }
      printf(" | %d\n", i);
    }
    printf("\n");
*/

    int currfaces[8][3]; //current facade of each cubelet
    int distinct = 0;
    //facade(facepairs, currfaces, 0, 0, 8, cube, numPermutes, &distinct);

    printf("distinct %d\n", distinct);


/*
    for(i = 0; i < numCubeletes; i++){
      for(j = 0; j < paircount; j++){

        assigncoloring(currfaces, facepairs, i, j); //assign a new coloring to the cube
        //printcurrfaces(currfaces);
        int res = compareCubes(cube, currfaces, numPermutes); //compare to other permutations

        if(res == 0){
          distinct++;
        }

      }
      printf("\n");
    }

    printf("distinct: %d\n", distinct);
*/

//  }

  clock_t begin = clock();
  unsigned long int allcolourings = pow(10,10);
  for (i = rank; i < allcolourings; i += wsize){
    for(j = 0; j < numPermutes; j++){
      for(l = j; l < numPermutes; l++){
        if(comparecolorings(cube, currfaces, i, j) == 1){
          //printf("cube recreated\n");
        }
      }
    }
  }


  if(rank == 0){
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Finished in %.3f seconds\n", time_spent);
  }

  MPI_Finalize();

  return 0;
}

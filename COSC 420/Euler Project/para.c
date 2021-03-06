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


struct cubeletColors{
  int x;
  int y;
  int z;
};

void print_clist(struct cubeletColors clist){
  printf("%d, %d, %d\n", clist.x, clist.y, clist.z);
}

void swap(int *x, int *y){
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

void copy_to_colors(struct cubeletColors clist[], int arr[], int n, int i){
    clist[i].x = arr[0];
    clist[i].y = arr[1];
    clist[i].z = arr[2];
}


void all_combinations(int arr[], int pos, int n, int *count, struct cubeletColors clist[]) {
    const int NUM_OF_COLORS = 1;
    int i;
    if(pos < (n - 1)){
        for(i = 0; i < NUM_OF_COLORS; i++) {
            arr[pos] = i;
            all_combinations(arr, pos + 1, n, count, clist);
        }
    }else{
        for(i = 0; i < NUM_OF_COLORS; i++) {
            arr[pos] = i;
      	    copy_to_colors(clist, arr, n, *count);
      	    //print_clist(clist[*count]);
      	    (*count)++;
        }
    }
}


void all_color_combinations(struct cubeletColors all_color_choices[], int pos, int n, struct cubeletColors color[], /**/int cube[][8], int permutes, int *counter, int rank, int wsize){
    const int NUM_OF_COLORS = 1;
    int ncubed = NUM_OF_COLORS*NUM_OF_COLORS*NUM_OF_COLORS;
    int i;
    if(pos < (n - 1)){
        for(i = rank; i < ncubed; i += wsize) {
            color[pos] = all_color_choices[i];
            all_color_combinations(all_color_choices, pos + 1, n, color, cube, permutes, counter, rank, wsize);
        }

    } else {

        for(i = 0; i < ncubed; i++) {
            color[pos] = all_color_choices[i];
      	    int a;
            int i, j, l;
            for(i = 0; i < permutes; i++){
              for(j = i+1; j < permutes; j++){

                //if we get a 0, the cube could not be recreated
                if(comparePermutations(color, cube, i, j) == 0){
                  //printf("cube is essentially distinct\n");
                  (*counter)++;
                }
              }
            }
/*
    	    for(a = 0; a < n; a++){
    	      //printf("%d: ", a);
    	      //prints each set of 8 color combinations
    	      //print_clist(color[a]);
    	      //printf("\n");

    	    }
*/       }
    }
}

int comparePermutations(struct cubeletColors facecolor[], int cubepermutations[][8], int c1, int c2){

  int i, j, matched = 1;
  for(i = 0; i < 8; i++){

    int c1facade = cubepermutations[c1][i];
    int c2facade = cubepermutations[c2][i];

    if(facecolor[c1facade].x != facecolor[c2facade].x ||
       facecolor[c1facade].y != facecolor[c2facade].y ||
       facecolor[c1facade].z != facecolor[c2facade].z){
      matched = 0;
    }

  }

  return matched;

}

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

  //printf("curr %d\n", curr);
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

  //for generating the number of permutations for the array

  /*

  this portion of the program is not intensive computationally
  does not matter if we do it on all nodes

  */

  int numCubeletes = 8;

  int numPermutes = factorial(numCubeletes);
  int colors = 2;
  int n = 3; //faces
  int cArr[numCubeletes];
  int cube[numPermutes][numCubeletes];
  int col[numCubeletes][3];
  init_array(cArr, numCubeletes);

  int pcount = 0;
  permute(cArr, cube, 0, numCubeletes, numCubeletes, &pcount);

  int fbuffer = power(colors, 3);

  int facepairs[fbuffer][3];

  int paircount = colorsPairs(facepairs, colors);

  //generating all colourings of a Rubik's cube

  const int NUM_OF_COLORS = 1;

  int count = 0;

  int* arr;
  arr = (int*) malloc(n*sizeof(int));

  //c - all combinations of colours for three faces (e.g. three colours)
  struct cubeletColors *c;
  c = (struct cubeletColors*) malloc(NUM_OF_COLORS*NUM_OF_COLORS*NUM_OF_COLORS*sizeof(struct cubeletColors));
  all_combinations(arr, 0, n, &count, c);

  //color_choices - 8 colors, will change on each recursive call of all_combinations
  struct cubeletColors *color_choices;
  color_choices = (struct cubeletColors*) malloc(8*sizeof(struct cubeletColors));

  int result = 0;
  all_color_combinations(c, 0, 8, color_choices, cube, numPermutes, &result, rank, wsize);

  int *recv = malloc(sizeof(int));
  MPI_Reduce(&result, &recv, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if(rank == 0){

    printf("result: %d\n", (*recv));

  }



  MPI_Finalize();

  return 0;
}

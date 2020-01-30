#ifndef MATRIX
#define MATRIX

#include <stdlib.h>
#include <stdbool.h>
#include "../Debug/debug.c"
#include "../Debug/procio.c"
#include "../Arrays/doubleops.c"
#include "../Math/doublemath.c"

#define INDEX(n,m,i,j) (m*i+j)
#define ROWS(A) (A->rows)
#define COLS(A) (A->cols)
//#define ARR(A) (A->arr)
#define ACCESS(A,i,j)					(A->arr[INDEX(ROWS(A), COLS(A), i, j)])
#define INVERSEACCESS(A,i,j)	(A->arr[INDEX(COLS(A), ROWS(A), i, j)])
#define dirACCESS(A,i) (A->arr[i])

struct Matrix {
  int rows, cols;
  double* arr;
  bool is_vect;// = false;
};

void printMatrixFull(struct Matrix* A) {
	for(int i = 0; i < ROWS(A); i++) {
		for(int j = 0; j < COLS(A); j++) {
			printf("%0.4f ", ACCESS(A,i,j));
		}
		puts("");
	}
  printf("is_vect: %d\n\n", A->is_vect);
}
void printMatrix(struct Matrix* A) {
	for(int i = 0; i < ROWS(A); i++) {
		if(i != ROWS(A)-1 && i > 15 && ROWS(A) > 16) {
			puts("⋮");
			i = ROWS(A)-2;
		} else {
			for(int j = 0; j < COLS(A); j++) {
				if(j != COLS(A)-1 && j > 15 && COLS(A) > 16) {
					printf("... ");
					j = COLS(A)-2;
				} else
					printf("%0.4f ", ACCESS(A,i,j));
			}
			puts("");
		}
	}
}
void log_matrix(struct Matrix* A) {
  for(int i = 0; i < ROWS(A); i++) {
    for(int j = 0; j < COLS(A); j++) {
      flogf("%0.4f ", ACCESS(A,i,j));
    }
    flogs("");
  }
  flogf("is_vect: %d\n\n", A->is_vect);
}


bool colcompare(struct Matrix* A, struct Matrix* B, int ai, int bi) {
  if(ROWS(A) != ROWS(B))
    return false;

  for(int r = 0; r < ROWS(A); r++)
    if(ACCESS(A,r,ai) != ACCESS(B, r, bi))
      return false;

  return true;
}
bool rowcompare(struct Matrix* A, struct Matrix* B, int ai, int bi) {
  if(COLS(A) != COLS(B))
    return false;

  for(int c = 0; c < COLS(A); c++) {
		int one = ACCESS(A,ai,c);
		int two = ACCESS(A,bi,c);
	  if(one != two)
      return false;
	}

  return true;
}

//------------------------------
// Matrix Creation and Startup
//------------------------------

void defineMatrix(struct Matrix* A, int r, int c) {
	ROWS(A) = r;
	COLS(A) = c;
  A->is_vect = false;
}
void prepareMatrix(struct Matrix* A) {
	int js = ROWS(A)*COLS(A);
	A->arr = calloc(js, sizeof(double));
}
// Initialize Matrix with with the specified dimensions, and all 0 values;
void initMatrix(struct Matrix* A, int r, int c) {
	defineMatrix(A, r, c);
	prepareMatrix(A);
}

void initVector(struct Matrix* A, int size) {
 	defineMatrix(A, size, 1);
 	prepareMatrix(A);
	A->is_vect = true;
}
// Populate the array of matrix A with random values, with a maximum value of max-1
bool populateUniqueMatrix(struct Matrix* A, int max, bool unique) {
	int js = (ROWS(A))*(COLS(A));
	//A->arr = calloc(js,sizeof(double));
	boundedArrPopulate_double(A->arr, js, defaultArrayElemMin, max);
	if(unique) {
		if(debug)
			puts("Unique rows requested. Analyzing Matrix...");
		int uniqueRowPossibilities = pow(max-defaultArrayElemMin+1,COLS(A));
		if(uniqueRowPossibilities < ROWS(A)) {
			if(debug)
				puts("Error! It is impossible to generate uniquely distinct rows with the specified maximum and minimum.\n");
			return false;
		}
		for(int r1 = 0; r1 < ROWS(A)-1; r1++) {
			bool debugprinted = false;
			for(int r2 = r1+1; r2 < ROWS(A); r2++) {
				if(rowcompare(A, A, r1, r2)) {
					if(debug && !debugprinted) {
						printf("Row %d and Rows %d are identical. Randomly repopulating row (%d).\n", r1, r2, r2);
						debugprinted = true;
					}
					boundedArrRangePopulate_double(A->arr, r2*COLS(A), r2*COLS(A)+COLS(A), defaultArrayElemMin, max);
					//printMatrix(A);
					r2 = ROWS(A);
					r1 = -1;
				}
			}
		}
		if(debug)
			puts("Unique rows found for matrix.\n");
	}
	return true;
}
void simpleMatrixPopulate(struct Matrix* A) {
  populateUniqueMatrix(A, defaultArrayElemMax, false);
}

bool createUniqueRowMatrix(struct Matrix* A, int r, int c, bool unique) {
  initMatrix(A, r, c);
  return populateUniqueMatrix(A, defaultArrayElemMax, unique);
}
void createMatrix(struct Matrix* A, int r, int c) {
  createUniqueRowMatrix(A, r, c, false);
}

// Effectively a deconstructor. Used to free memory, but also indicate via updated dimensions that this array should not be used until recreated/reinitialized
void destroyMatrix(struct Matrix* A) {
	ROWS(A) = -1;
	COLS(A) = -1;
	free(A->arr);
}

void copyMatrix(struct Matrix* A, struct Matrix* cb) {
  initMatrix(A, ROWS(cb), COLS(cb));
  for(int a = 0; a < ROWS(cb); a++) {
    for(int b = 0; b < COLS(cb); b++) {
      ACCESS(A,a,b) = ACCESS(cb,a,b);
    }
  }
  A->is_vect = cb->is_vect;
}

void copyMatrixValues(struct Matrix* A, struct Matrix* cb) {
  for(int a = 0; a < ROWS(cb); a++) {
    for(int b = 0; b < COLS(cb); b++) {
      ACCESS(A,a,b) = ACCESS(cb,a,b);
    }
  }
  A->is_vect = cb->is_vect;
}

bool vector_cmp(struct Matrix* A, struct Matrix* B) {
  //printf("%d %d\n", A->is_vect, B->is_vect);
  if(!A->is_vect || !B->is_vect)
    return false;
  //printf("%d %d\n", ROWS(A), ROWS(B));
  if(ROWS(A) != ROWS(B))
    return false;

  for(int a = 0; a < ROWS(A); a++) {
    double one = round_double(ACCESS(A,0,a),10);
    double two = round_double(ACCESS(B,0,a),10);
    //printf("%0.8f %0.8f\n", one, two);
    if(one != two)
      return false;
  }
  return true;
}

#endif

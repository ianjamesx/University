#ifndef MATRIXMATH
#define MATRIXMATH

#include <mpi.h>
#include "matrix.c"
#include "../func2.c"
#include "../Arrays/doubleops.c"
#include "../Debug/procio.c"
#include <unistd.h>

void printArr_int(int* arr, int n) {
  int a;
  for(a = 0; a < n && a < 15; a++) {
    printf("%d", arr[a]);
    if(a+1 != n)
      printf(", ");
  }
  if(a < n)
    puts("...");
  else
    puts("");
}
// Copies the values of column colIndex in matrix A to arr
void copyColumn(struct Matrix* A, int colIndex, double* arr) {
	const int rows = ROWS(A);
	const int cols = COLS(A);
	for(int a = 0; a < rows; a++) {
		//printf("%d", A->arr[a*cols + colIndex]);
		//arr[a] = A->arr[a*cols + colIndex];
		arr[a] = ACCESS(A, a, colIndex);
	}
}

//-----------------------
// Operation Validation
//-----------------------

bool diffRows(struct Matrix* A, struct Matrix* B) {
	return ROWS(A) != ROWS(B);
}
bool diffCols(struct Matrix* A, struct Matrix* B) {
	return COLS(A) != COLS(B);
}
// Checks if two matrices have the same dimensions (Ex. A: 3x3, B: 3x3)
bool differingDimensions(struct Matrix* A, struct Matrix* B) {
	return diffRows(A, B) || diffCols(A, B);
}
// Checks if two matrices have inverse dimensions (Ex. A: 2x4, B: 4x2)
bool multipliableDimensions(struct Matrix* A, struct Matrix* B) {
	return COLS(A) == ROWS(B);
}
// Gets the transpose of A and returns it in At
void getTranspose(struct Matrix* A, struct Matrix* At) {
	const int rows = ROWS(A);
	const int cols = COLS(A);
	const int total = rows*cols;
	//destroyMatrix(At);
	//initMatrix(At, cols, rows);
	//printf("%d\n", total);
	for(int a = 0; a < total; a++) {
		//printf("%d %d, ", (rows*a)%(total)+(rows*a/total), a);
		At->arr[(rows*a)%(total)+(rows*a/total)] = A->arr[a];
	}
}
bool addMatrices(struct Matrix* A, struct Matrix* B, struct Matrix* result) {
	if(differingDimensions(A, B))
		return false;
	const int rows = A->rows;
	const int cols = A->cols;
	initMatrix(result, rows, cols);
	result->arr = addArrs_double(A->arr, B->arr, rows*cols);
	return true;
}
bool subMatrices(struct Matrix*A, struct Matrix* B, struct Matrix* result) {
	if(differingDimensions(A, B))
		return false;
	const int rows = A->rows;
	const int cols = A->cols;
	initMatrix(result, rows, cols);
	result->arr = subArrs_double(A->arr, B->arr, rows*cols);
	return true;
}
bool multMatrices(struct Matrix* A, struct Matrix* B, struct Matrix* result) {
	if(!multipliableDimensions(A, B)) {
		return false;
	}
	const int rows = A->rows;
	const int cols = A->cols;
	const int shared = B->rows;
	const int diff = B->cols;

	initMatrix(result, rows, diff);
	for(int a = 0; a < rows; a++) {
		int rowlen = A->cols;
		double* subA = A->arr + a*rowlen;
		for(int b = 0; b < diff; b++) {
			double* subB = malloc(shared*sizeof(double));
			copyColumn(B, b, subB);
			//printArr_double(subA, rowlen);
			//printArr_double(subB, rowlen);
			double prod = dotProduct_double(subA, subB, cols);
			//printf("%0.4f\n", prod);
			//printf("!!!%d at %d\n", prod, a*diff+b);
			result->arr[a*diff+b] = prod;
			free(subB);
		}
	}
	if(COLS(result) == 1)
		result->is_vect = true;
	return true;
}
bool MPI_multMatrices(struct Matrix* A, struct Matrix* B, struct Matrix* result) {
	int worldsize;
	MPI_Comm world = MPI_COMM_WORLD;
	MPI_Comm_size(world, &worldsize);

	int me;
	MPI_Comm_rank(world, &me);
	if(worldsize < 2) {
		return multMatrices(A, B, result);
	} else if(me == 0 && !multipliableDimensions(A, B)) {
		return false;
	}

	const int rows = A->rows;
	const int cols = A->cols;
	const int shared = B->rows;
	const int newCols = B->cols;
	const int newRows = rows;

	const int jobsize = rows;
	const int maxNodeload = getMaxNodeLoad(jobsize, worldsize);
	const int baseNodeload = getMinNodeLoad(jobsize, worldsize);
	const int overhead = jobsize%worldsize;

	int n = baseNodeload;
	if(me+1 <= overhead)
			n++;

	const int nodeload = n;

	if(me != 0)
		MPI_Send(&nodeload, 1, MPI_INT, 0, 999, world);

	double* m1Arr;
	if(me == 0)
		m1Arr = A->arr;
	else
		m1Arr = malloc(rows*cols*sizeof(double));
	MPI_Bcast(m1Arr, rows*cols, MPI_DOUBLE, 0, world);

	double* subB[nodeload];
	for(int a = 0; a < nodeload; a++)
	 	subB[a] = malloc(shared*sizeof(double));

	if(me == 0) {
		int processed = 0;
		int nodeloads[worldsize];
		nodeloads[0] = nodeload;
		for(int a = 0; a < nodeload; a++) {
			copyColumn(B, processed, subB[a]);
			processed++;
		}
		for(int a = 1; a < worldsize; a++) {
			int currsize = -1;
			MPI_Recv(&currsize, 1, MPI_INT, a, 999, world, MPI_STATUS_IGNORE);
			nodeloads[a] = currsize;
			for(int b = 0; b < nodeloads[a]; b++) {
				double* subArr = malloc(shared*sizeof(double));
				copyColumn(B, processed, subArr);
				MPI_Send(subArr, shared, MPI_DOUBLE, a, 4000+a*10+b, world);
				//free(subArr);
				processed++;
			}
		}
		MPI_Send(nodeloads, worldsize, MPI_INT, 0, 42, world);
	} else {
		for(int a = 0; a < nodeload; a++) {
			MPI_Recv(subB[a], shared, MPI_DOUBLE, 0, 4000+me*10+a, world, MPI_STATUS_IGNORE);
		}
	}
	double* multArr[nodeload];
	for(int a = 0; a < nodeload; a++)
		multArr[a] = malloc(newRows*sizeof(double));

	for(int a = 0; a < nodeload; a++) {
		for(int b = 0; b < rows; b++) {
			double* targetArr = m1Arr + shared*b;
			multArr[a][b] = dotProduct(targetArr, subB[a], shared);
		}
	}

	MPI_Barrier(world);
	//for(int a = 0; a < nodeload; a++)
	//	free(subB[a]);
	//if(me != 0) {
	//	free(m1Arr);
	//}

	//initMatrix(result, newRows, newCols);


	if(me != 0) {
		for(int a = 0; a < nodeload; a++) {
			MPI_Send(multArr[a], newRows, MPI_DOUBLE, 0, 4100+me*10+a, world);
			//free(multArr[a]);
		}
	}	else {
		int* nodeloads = malloc(worldsize*sizeof(int));
		MPI_Recv(nodeloads, worldsize, MPI_INT, 0, 42, world, MPI_STATUS_IGNORE);

		int colIndex = 0;
		for(int a = 0; a < worldsize; a++) {
			for(int b = 0; b < nodeloads[a]; b++) {
				// double* current;
				// if(a != 0) {
				// 	current = malloc(newRows/*shared*/*sizeof(double));
				// 	MPI_Recv(current, newRows, MPI_DOUBLE, a, 4100+a*10+b, world, MPI_STATUS_IGNORE);
				// } else
				// 	current = multArr[b];
				//
				//
				// for(int c = 0; c < newRows; c++) {
				// 	result->arr[colIndex+c*newRows] = current[c];
				// }

				if(a != 0) {
					double* current = malloc(newRows/*shared*/*sizeof(double));
					MPI_Recv(current, newRows, MPI_DOUBLE, a, 4100+a*10+b, world, MPI_STATUS_IGNORE);
					for(int c = 0; c < newRows; c++) {
						result->arr[colIndex+c*newRows] = current[c];
					}
				} else {
					for(int c = 0; c < newRows; c++) {
						result->arr[colIndex+c*newRows] = multArr[b][c];
					}
				}


				//for(int c = 0; c < newRows; c++) {
				//	result->arr[colIndex+c*newRows] = current[c];
				//}
				// if(me == 0) {
				// 	puts("TEST");
				// 	printf("%d\n", ROWS(result));
				// 	printMatrixFull(result);
				// }
				//if(a != 0)
				//	free(current);
				colIndex++;
			}
		}
	}
	// if(me == 1) {
	//  	puts("TEST2");
	//  	printf("%d\n", ROWS(result));
	//  	printMatrixFull(result);
	// }
	// printf("(%d) %d\n", me, newRows*newCols);

	//MPI_Barrier(world);
	//MPI_Bcast(result->arr, newRows*newCols, MPI_DOUBLE, 0, world);
	/*if(me != 0) {
	 	puts("TEST3");
	 	printf("%d\n", ROWS(result));
	 	printMatrixFull(result);
	}*/
//	MPI_Barrier(world);
	result->is_vect = B->is_vect;
	return true;
}
bool MPI_multVector(struct Matrix* A, struct Matrix* B, struct Matrix* result) {
  int worldsize;
	MPI_Comm world = MPI_COMM_WORLD;
	MPI_Comm_size(world, &worldsize);

	int rank;
	MPI_Comm_rank(world, &rank);
	if(worldsize < 2) {
		return multMatrices(A, B, result);
	} else if(rank == 0 && !multipliableDimensions(A, B)) {
		return false;
	}

  const int rows = A->rows;
	const int cols = A->cols;
	const int shared = B->rows;
	const int newCols = B->cols;
	const int newRows = rows;

  const int jobsize = rows;
	const int maxNodeload = getMaxNodeLoad(jobsize, worldsize);
	const int baseNodeload = getMinNodeLoad(jobsize, worldsize);
	const int overhead = jobsize%worldsize;

	int n = baseNodeload;
	if(rank+1 <= overhead)
			n++;

	const int nodeload = n;

  int nodeloads[worldsize];
  nodeloads[rank] = nodeload;
	if(rank != 0)
		MPI_Send(&nodeload, 1, MPI_INT, 0, 999, world);
  else {
    for(int a = 1; a < worldsize; a++) {
      MPI_Recv(&(nodeloads[a]), 1, MPI_INT, a, 999, world, MPI_STATUS_IGNORE);
    }
  }

  MPI_Bcast(nodeloads, worldsize, MPI_INT, 0, world);

  int startindex = 0;
  for(int a = 0; a < rank; a++) {
    startindex += nodeloads[a];
  }
  double* products[nodeload];
  double* column = malloc(shared*sizeof(double));
  copyColumn(B, 0, column);
  for(int a = 0; a < nodeload; a++) {
    if(rank != 0) {
      products[a] = malloc(newRows*sizeof(double));
      int b = startindex+a;
      double p = dotProduct(A->arr+shared*b, column, shared);
      MPI_Send(&b, 1, MPI_INT, 0, rank, world);
      MPI_Send(&p, 1, MPI_DOUBLE, 0, 410000+rank*1000+a, world);
      int num = 0;
      MPI_Recv(&num, 1, MPI_INT, 0, 0, world, MPI_STATUS_IGNORE);//Probe(0, 0, world, MPI_STATUS_IGNORE);
    } else {
      int b = startindex+a;
      double prod = dotProduct(A->arr+shared*b, column, shared);
      ACCESS(result,b,0) = prod;
      for(int c = 1; c < worldsize; c++) {
        if(a < nodeloads[c]) {
          int* colind = malloc(1*sizeof(int));
          MPI_Recv(colind, 1, MPI_INT, c, c, world, MPI_STATUS_IGNORE);
          double* buf = malloc(1*sizeof(double));

          MPI_Recv(buf, 1, MPI_DOUBLE, c, 410000+c*1000+a, world, MPI_STATUS_IGNORE);
          ACCESS(result,*colind,0) = *buf;
          int num = 0;
          MPI_Send(&num, 1, MPI_INT, c, 0, world);
        }
      }
    }
  }

  MPI_Barrier(world);
  MPI_Bcast(result->arr, ROWS(result)*COLS(result), MPI_DOUBLE, 0, world);
  result->is_vect = true;
  return true;
}
void first_pass(struct Matrix* A, struct Matrix* eigenvector) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Barrier(MPI_COMM_WORLD);
	struct Matrix x_vect, A_cross_x;
	struct Matrix* x = &x_vect;
	struct Matrix* Ax = &A_cross_x;
	MPI_Barrier(MPI_COMM_WORLD);
	initVector(Ax, ROWS(A));
	MPI_Barrier(MPI_COMM_WORLD);
	initVector(x, ROWS(A));
	MPI_Barrier(MPI_COMM_WORLD);
	set_vector(x->arr, ROWS(x), 1);
	MPI_Barrier(MPI_COMM_WORLD);
	bool loop = true;
	int cnt = 0;
	struct Matrix xr;
	struct Matrix* xresult = &xr;
	MPI_Barrier(MPI_COMM_WORLD);
	initVector(xresult, ROWS(x));
	MPI_Barrier(MPI_COMM_WORLD);
	copyMatrix(xresult,x);
	MPI_Barrier(MPI_COMM_WORLD);
	do {
	//printf("(%d) Hello. 5\n", rank);
		MPI_Barrier(MPI_COMM_WORLD);
		if(debug) {
			flogf("%d\n", cnt);
			flogs("xresult:");
			log_matrix(xresult);
			if(rank == 0) {
				printf("%d\n", cnt);
				puts("xresult:");
				printMatrixFull(xresult);
			}
		}
		MPI_multVector(A, xresult, Ax);
		if(debug) {
			flogs("Ax:");
			log_matrix(Ax);
			if(rank == 0) {
				puts("Ax:");
				printMatrixFull(Ax);
			}
		}
		copyMatrix(xresult, Ax);
		if(debug) {
			flogs("xresult:");
			log_matrix(xresult);
			if(rank == 0) {
				puts("xresult:");
				printMatrixFull(xresult);
			}
		}
		double xnorm = normalize_vector(xresult->arr, ROWS(xresult));
		scale_vector(xresult->arr, ROWS(xresult), 1/xnorm);
		if(debug) {
			flogs("xresult:");
			log_matrix(xresult);
			flogs("x:");
			log_matrix(x);
			flogs("\nComparing...");
			if(rank == 0) {
				puts("xresult:");
				printMatrixFull(xresult);
				puts("x:");
				printMatrixFull(x);
				puts("\nComparing...");
			}
		}
		if(vector_cmp(x, xresult)) {
			loop = false;
			if(debug) {
				flogs("Vectors match");
				if(rank == 0)
					puts("Vectors match");
				}
		} else if(debug) {
			flogs("Vectors Dont match");
			if(rank == 0) {
				puts("Vectors Dont match");
			}
		}
		if(debug) {
			flogs("Exit Comparison");
			if(rank == 0) {
				puts("Exit Comparison");
			}
		}
		copyMatrix(x,xresult);
		cnt++;
	} while(loop);
	if(rank == 0)
		copyMatrix(eigenvector,x);
	MPI_Bcast(eigenvector->arr, ROWS(eigenvector)*COLS(eigenvector), MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

void choleskyLU(struct Matrix* A, struct Matrix* l, struct Matrix* u) {
	struct Matrix copy;
	struct Matrix* copyptr = &copy;
	copyMatrix(copyptr,A);
	initMatrix(l, ROWS(copyptr), COLS(copyptr));
	initMatrix(u, ROWS(copyptr), COLS(copyptr));

	for(int k = 0; k < ROWS(copyptr); k++) {
		for(int i = 0; i < COLS(copyptr)-(COLS(copyptr)-1-k); i++) {
			//printf("k: %d\ti: %d\n", k, i);
			if(k == i) {
				double Akk, dotProd;
				Akk = ACCESS(copyptr,k,k);
				dotProd = dotProduct_double((l->arr)+k*COLS(copyptr), (l->arr)+k*COLS(copyptr), k);
				//printf("Akk:\t%0.4f\n", Akk);
				//printf("dotProd:\t%0.4f\n", dotProd);
				double v = sqrt(Akk - dotProd);
				ACCESS(l,k,i) = v;
				ACCESS(u,i,k) = v;
			} else {
				double Aki, dotProd, Aii;
				Aki = ACCESS(copyptr,k,i);
				dotProd = dotProduct_double((l->arr)+k*COLS(copyptr), (l->arr)+i*COLS(copyptr), k);
				Aii = ACCESS(l,i,i);
				//printf("Aki:\t%0.4f\n", Aki);
				//printf("dotProd:\t%0.4f\n", dotProd);
				//printf("Aii:\t%0.4f\n", Aii);
				double v = (Aki - dotProd)/Aii;
				ACCESS(l,k,i) = v;
				ACCESS(u,i,k) = v;
			}
			//printf("Aki:\t%0.4f\n", ACCESS(l,k,i));
			//puts("");
			MPI_Barrier(MPI_COMM_WORLD);
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	destroyMatrix(copyptr);
}
// Non-Parallel Gauss Jordan Elimination
bool gaussjordan(struct Matrix* A, struct Matrix* b) {
	if(!multipliableDimensions(A, b))
		return false;
	const int rows = ROWS(A);
	const int cols = COLS(A);
	for(int k = 0; k < rows; k++) {
		double* l = calloc(rows, sizeof(double));
		for(int i = 0; i < rows; i++) {
			l[i] = ACCESS(A, i, k)/(double) ACCESS(A, k, k);
		}
		//printf("l %d: ", k); printArr_double(l, COLS(A));
		for(int r = 0; r < rows; r++) {
			if(r != k) {
				for(int c = 0; c < cols; c++) {
					ACCESS(A, r, c) = ACCESS(A, r, c) - l[r]*ACCESS(A, k, c);
				}
				for(int c = 0; c < COLS(b); c++) {
					//printf("b: %0.2f\n", ACCESS(b, r,c));
					ACCESS(b, r, c) = ACCESS(b, r, c) - l[r]*ACCESS(b, k, c);
					//printf("a: %0.2f\n", ACCESS(b, r,c));
				}
			}
		}
	}
	for(int r = 0; r < rows; r++) {
		double value = ACCESS(A, r, r);
		ACCESS(A, r, r) = 1;
		for(int c = 0; c < COLS(b); c++) {
			ACCESS(b, r, c) = ACCESS(b,r,c)/value;
		}
	}
	return true;
}
bool MPI_gaussjordan(struct Matrix* A, struct Matrix* b) {
	//------------------------
	// MPI Boiler-Plate Code
	//------------------------
	int worldsize;
	MPI_Comm world = MPI_COMM_WORLD;
	MPI_Comm_size(world, &worldsize);
	//------------------------

	// Check that code is actually being called in parallel
	int me;
	MPI_Comm_rank(world, &me);
	if(worldsize < 2) {	// If worldsize: is 0, then the prog was not run with mpiexec; is 1, there's no disadvantage to just calling the non-parallel version
		return gaussjordan(A, b);
	} else if(/*me == 0 && */(diffRows(A, b) || !multipliableDimensions(A, b))) {	// If matrices are not multipliable, return false;	// Matrix Dimensions
		if(debug)
			printf("(%d) Incompatible Matrices Found. Exiting.\n", me);
		return false;
	}
	//printf("(%d) BEEINGO\n", me);

	// Matrix Dimensions
	const int rows = ROWS(A);
	const int cols = COLS(A);

	MPI_Bcast(A->arr, rows*cols, MPI_DOUBLE, 0, world);
	MPI_Bcast(b->arr, ROWS(b)*COLS(b), MPI_DOUBLE, 0, world);

	// Processing Info
	const int jobsize = rows;	// Note: jobsize and nodeload differ here from addition and subtraction because it is broken up by rows of A/columns of B
	const int baseNodeload = ROWS(A)/worldsize;//getMinNodeLoad(jobsize, worldsize);
	const int overhead = jobsize%worldsize;
	int maxnl = baseNodeload;
	if(overhead > 0) {
		maxnl++;
	}
	const int maxNodeload = maxnl;
	// If the jobsize is not evenly divisable by the number of nodes, add extra to a processors node if required
	int n = baseNodeload;
	if(me+1 <= overhead) {
			n++;
	}
	const int nodeload = n;
	int* nodeloads = malloc(worldsize*sizeof(int));
	MPI_Gather(&nodeload, 1, MPI_INT, nodeloads, 1, MPI_INT, 0, world);
	MPI_Bcast(nodeloads, worldsize, MPI_INT, 0, world);

	int recvdisp[worldsize];
	recvdisp[0] = 0;
	for(int a = 1; a < worldsize; a++) {
		recvdisp[a] = recvdisp[a-1]+nodeloads[a-1];//a*(nodeloads[0]+1);
	}
	const int rSI = sumArr_int(nodeloads, me);
	const int rEI = rSI+nodeload;

	MPI_Bcast(A->arr, rows*cols, MPI_DOUBLE, 0, world);
	MPI_Bcast(b->arr, ROWS(b)*COLS(b), MPI_DOUBLE, 0, world);
	for(int k = 0; k < rows; k++) {
		double* l = calloc(rows, sizeof(double)+1);
		for(int i = rSI; i < rEI; i++) {
			//printf("%0.2f\n", ACCESS(A,i,k)/ACCESS(A,k,k));
			l[i] = ACCESS(A,i,k)/ACCESS(A,k,k);
		}
		double* recvbuf = malloc(rows*sizeof(double));
		MPI_Gatherv(l+rSI, nodeload, MPI_DOUBLE, recvbuf, nodeloads, recvdisp, MPI_DOUBLE, 0, world);
		free(l);
		l = recvbuf;
		MPI_Bcast(l, rows, MPI_DOUBLE, 0, world);
		for(int r = 0; r < rows; r++) {
			if(r != k) {
				for(int c = rSI; c < rEI; c++)
					ACCESS(A,r,c) = ACCESS(A,r,c) - l[r]*ACCESS(A,k,c);
				for(int c = 0; c < 1; c++)
					ACCESS(b, r, c) = ACCESS(b, r, c) - l[r]*ACCESS(b, k, c);
				recvbuf = malloc(cols*rows*sizeof(double));
				MPI_Gatherv((A->arr+r*COLS(A)+rSI), nodeload, MPI_DOUBLE, recvbuf, nodeloads, recvdisp, MPI_DOUBLE, 0, world);
				MPI_Barrier(world);
				if(me == 0) {
					for(int c = 0; c < COLS(A); c++)
						ACCESS(A,r,c) = recvbuf[c];
				}
				MPI_Bcast(A->arr, ROWS(A)*COLS(A), MPI_DOUBLE, 0, world);
				free(recvbuf);
			}
		}
		MPI_Bcast(b->arr, ROWS(b)*COLS(b), MPI_DOUBLE, 0, world);
	}
	for(int r = 0; r < rows; r++) {
		ACCESS(b,r,0) = ACCESS(b,r,0)/ACCESS(A,r,r);
		(ACCESS(A,r,r)) = ((ACCESS(A,r,r))/(ACCESS(A,r,r)));
	}
	return true;
}
#endif

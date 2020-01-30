/* Alex English
 * 9/10/19
 * Dr. Anderson
 * func2.c
 * A small set of functions to read program operating parameters, specified by the user in the command line. Used exclusively in prog2.
 */
#ifndef MMATH_SUPPORT
#define MMATH_SUPPORT

#include <mpi.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "Debug/debug.c"
#include "Matrix/matrix.c"

const static int defaultMaxNumSize = 10;
const static int defaultRowNum = 3;
const static int defaultColNum = 3;

int randnum(int min, int max) {
	return rand() % (max-min+1) + min;
}
int defaultJobSize() {
	return defaultRowNum*defaultColNum;
}
//---------------------------------------------
// Currently Unused. May use in the future
//---------------------------------------------
bool argvContainsInt(int argc, char** argv, int query) {
	for(int a = 1; a < argc; a++) {
		if(query == atoi(argv[a]))
			return true;
	}
	return false;
}
bool argvContainsString(int argc, char** argv, char* query) {
	for(int a = 1; a < argc; a++) {
		if(strcmp(query, argv[a]) == 0)
			return true;
	}
	return false;
}
//---------------------------------------------
// Reading in matrix dimension fetching
//---------------------------------------------
int getRowNum(int argc, char** argv) {
	int n;
	if(argc > 2)			// If at least 3 arguments are specified
		n = atoi(argv[1]);	// Read the first as the row value
	else
		n = defaultRowNum;	// Else, use default row value
	return n;
}
int getColNum(int argc, char** argv) {
	int n;
	if(argc > 2)			// If at least 3 arguments are specified
		n = atoi(argv[2]);	// Read the second as the column value
	else
		n = defaultColNum;	// Else, use default column value
	return n;
}
void getDimensions(int* r, int* c, int argc, char** argv) {
	*r = getRowNum(argc, argv);
	*c = getColNum(argc, argv);
}
//---------------------------------------------
// Processing parameters specifed by the user
//---------------------------------------------
bool debugMode(int argc, char** argv) {
	char* str = "-d";
	if(argvContainsString(argc, argv, str))
		return true;
	return false;
}
// A max bound is specifed only under certain conditions. See readme for more detail
int getMaxBound(int argc, char** argv) {
	int n;
	if(argc > 1 && argc != 3) {	// If the user has specifed more than 0 arguments, but not exactly 2
		if(argc > 3)		// If the user has specified matrix dimensions, use the 3 argument
			n = atoi(argv[3]);
		else			// Else, use the first
			n = atoi(argv[1]);
	} else				// Else (no arguments), use default max
		n = defaultMaxNumSize;
	return n;
}
int getJobSize(struct Matrix* A) {
	return (A->rows)*(A->cols);
}
// Gets the size of the arrays that each processor will handle, rounded up.
int getMaxNodeLoad(int jobsize, int worldsize) {
	double n = jobsize/(double)worldsize;
	int nI = (int) n;
	if(n == nI)
		return nI;
	int padded = (int) ceil(n);
	return padded;
}
// Gets the size of the arrays that each processor will handle, rounded down.
int getMinNodeLoad(int jobsize, int worldsize) {
	return jobsize/worldsize;
}
//---------------------------------------------

//---------------------------------------------------------
// Currently Unused and Unfinished. May use in the future
//---------------------------------------------------------
int getChunkedNodeLoad(int jobsize, int worldsize, int blocksize) {
	return jobsize/(worldsize*blocksize);
}
int getPaddedJobSize(int nodeload, int worldsize) {
	return nodeload*worldsize;
}
int getLastNodeOverhead(int nodeload, int jobsize, int worldsize) {
	return nodeload*worldsize-jobsize;
}
//---------------------------------------------------------

#endif

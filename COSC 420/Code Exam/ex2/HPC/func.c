/* Alex English
 * 9/10/19
 * Dr. Anderson
 * func.c
 * A small set of functions to read program operating parameters, specified by the user in the command line. Used exclusively in prog1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h> 
#include <math.h>

const int defaultJobSize = 15;
const int maxNumSize = 100;

// Get the size of the vectors specified by the user, if applicable
int getJobSize(int argc, char** argv) {
  int n;
  if(argc > 1)		// If there is at least one parameter given py the user
    n = atoi(argv[1]);	// Set jobsize equal to that value
  else
    n = defaultJobSize;	// Else, use default size
  return n;
}
// Gets the maximum value of numbers that should be present in the elements of the vectors
int getMaxBound(int argc, char** argv) {
  int n;
  if(argc > 2)		// If there is at least two elements
    n = atoi(argv[2]);	// Set max bound equal to that value
  else
    n = maxNumSize;	// Else, use default max value
  return n;
}
// Gets the size of the sub vectors that each processor will handle, rounded up.
int getMaxNodeLoad(int jobsize, int worldsize) {
  double n = jobsize/(double)worldsize;	// Divide (as a floating point variable) the size of the vectors by the number of processors
  int nI = (int) n;			// Cast that value to an int
  if(n == nI)				// Compare the values: If they are the same, return that int value
    return nI;
  int padded = (int) ceil(n);		// Else, round it up, and return it.
  return padded;
}
// Returns the jobsize, but padded to represent the rounded up nodeload of each processor
// Ex.
//	jobsize = 15
//	worldsize = 4
//	realNodeload = 3.75 	// Theoretical evenly divided load for each processor. However, in reality, a processor can't handle "3/4" of an array element
//	maxNodeload = 4;

//	paddedJobsize = 16
int getPaddedJobSize(int nodeload, int worldsize) {
  return nodeload*worldsize;
}

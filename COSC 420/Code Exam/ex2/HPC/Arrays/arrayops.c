#ifndef UNIVERSALARRAYOPS
#define UNIVERSALARRAYOPS

#include <math.h>

int* cast_dtoi_trunc(double* arr, int n) {
  int* result = malloc(n*sizeof(int));
  for(int a = 0; a < n; a++) {
    result[a] = (int) arr[a];
  }
  return result;
}
int* cast_dtoi_round(double* arr, int n) {
  int* result = malloc(n*sizeof(int));
  for(int a = 0; a < n; a++) {
    result[a] = (int) round(arr[a]);
  }
  return result;
}
double* cast_itod(int* arr, int n) {
  double* result = malloc(n*sizeof(double));
  for(int a = 0; a < n; a++) {
    result[a] = (double) arr[a];
  }
  return result;
}

// Returns the sum of two indicies, i, of two arrays
double addArrIndex_int(int* arr1, int* arr2, int i) {
  return arr1[i]+arr2[i];
}
double addArrIndex_double(double* arr1, double* arr2, int i) {
  return arr1[i]+arr2[i];
}
double addArrIndex(double* arr1, double* arr2, int i) {
  return addArrIndex_double(arr1, arr2, i);
}
// Returns the product of two indicies, i, of two arrays
double multArrIndex_int(int* arr1, int* arr2, int i) {
  return arr1[i]*arr2[i];
}
double multArrIndex_double(double* arr1, double* arr2, int i) {
  return arr1[i]*arr2[i];
}
double multArrIndex(double* arr1, double* arr2, int n) {
  return multArrIndex_double(arr1, arr2, n);
}
// Returns the summation of the elements of an array
double sumArr_int(int* arr, int n) {
  double sum = 0;
  for(int a = 0; a < n; a++) {
    sum += arr[a];
  }
  return sum;
}
double sumArr_double(double* arr, int n) {
  double sum = 0;
  for(int a = 0; a < n; a++) {
    sum += arr[a];
  }
  return sum;
}
double sumArrs(double* arr, int n) {
  return sumArr_double(arr, n);
}

void scale_vector(double* arr, int n, double scalar) {
	for(int a = 0; a < n; a++) {
		arr[a] *= scalar;
	}
}
void set_vector(double* arr, int n, double value) {
	for(int a = 0; a < n; a++) {
		arr[a] = value;
	}
}

// Returns the dot product of two vectors
double dotProduct_int(int* arr1, int* arr2, int n) {
  double sum = 0;
  for(int a = 0; a < n; a++) {
    sum += multArrIndex_int(arr1, arr2, a);
  }
  return sum;
}
double dotProduct_double(double* arr1, double* arr2, int n) {
  double sum = 0;
  for(int a = 0; a < n; a++) {
    sum += multArrIndex_double(arr1, arr2, a);
  }
  return sum;
}

double dotProduct(double* arr1, double* arr2, int n) {
  return dotProduct_double(arr1, arr2, n);
}
double normalize_vector(double* arr, int n) {
	return sqrt(dotProduct(arr, arr, n));
}
// Returns a new array of size n, the elements of which are the sum of the matching indicies in each of the provided arrays
double* addArrs_int(int* arr1, int* arr2, int n) {
	double* sumArr = malloc(n*sizeof(double));
	for(int a = 0; a < n; a++)
		sumArr[a] = arr1[a] + arr2[a];
	return sumArr;
}
double* addArrs_double(double* arr1, double* arr2, int n) {
	double* sumArr = malloc(n*sizeof(double));
	for(int a = 0; a < n; a++)
		sumArr[a] = arr1[a] + arr2[a];
	return sumArr;
}

double* addArrs(double* arr1, double* arr2, int n) {
  return addArrs_double(arr1, arr2, n);
}

// Returns a new array of size n, the elements of which are the negative sum of the matching indicies in each of the provided arrays
double* subArrs_int(int* arr1, int* arr2, int n) {
	double* negSumArr = malloc(n*sizeof(double));
	for(int a = 0; a < n; a++)
		negSumArr[a] = arr1[a] - arr2[a];
	return negSumArr;
}
double* subArrs_double(double* arr1, double* arr2, int n) {
	double* negSumArr = malloc(n*sizeof(double));
	for(int a = 0; a < n; a++)
		negSumArr[a] = arr1[a] - arr2[a];
	return negSumArr;
}
double* subArrs(double* arr1, double* arr2, int n) {
  return subArrs_double(arr1, arr2, n);
}
#endif

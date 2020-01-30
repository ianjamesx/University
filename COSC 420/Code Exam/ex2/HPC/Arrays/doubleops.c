#ifndef DOUBLEARRAYOPS
#define DOUBLEARRAYOPS

#include <stdlib.h>
#include <stdbool.h>

#include "math.h"
#include "../Debug/debug.c"
#include "globals.c"
#include "arrayops.c"

void printArr_double(double* arr, int n) {
  int a;
  for(a = 0; a < n && a < 15; a++) {
    printf("%0.2f", arr[a]);
    if(a+1 != n)
      printf(", ");
  }
  if(a < n)
    puts("...");
  else
    puts("");
}
void printFullArr_double(double* arr, int n) {
  for(int a = 0; a < n; a++) {
    printf("%0.2f", arr[a]);
    if(a+1 != n);
      printf(", ");
  }
  puts("");
}

void printArrRange_double(double* arr, int n, int from, int to) {
  int a;
  for(a = from; a < to; a++) {
    printf("%0.2f", arr[a]);
    if(a+1 != to);
      printf(", ");
  }
  puts("");
}

void boundedArrPopulate_double(double* arr, int n, int min, int max) {
  for(int a = 0; a < n; a++) {
    arr[a] = (double) (rand() % (max-min+1) + min);
  }
}
bool boundedUniqueArrPopulate_double(double* arr, int n, int min, int max, bool unique) {
  if(unique) {
    if(max-min < n) {
      if(debug) {
        puts("Error! It is impossible to generate uniquely distinct vector elements with the specified maximum and minimum.\n");
        boundedArrPopulate_double(arr, n, min, max);
        return false;
      }
    }
    bool selected[max-min+1];//= calloc(max-min+1, sizeof(bool));
    for(int a = 0; a < max-min+1; a++) {
      selected[a] = false;
    }
    for(int a = 0; a < n; a++) {
      int r = 0;
      do {
        r = (rand() % (max-min+1) + min);
      } while(selected[r-min]);
      selected[r-min] = true;
      arr[a] = (double) r;
    }
    free(selected);
    return true;
  } else
    boundedArrPopulate_double(arr, n, min, max);
  return false;
}
void boundedArrRangePopulate_double(double* arr, int from, int to, int min, int max) {
  boundedArrPopulate_double(arr+from, to-from, min, max);
}
void simpleArrRangePopulate_double(double* arr, int from, int to) {
  boundedArrRangePopulate_double(arr, from, to, defaultArrayElemMin, defaultArrayElemMax);
}
void simpleArrPopulate_double(double* arr, int n) {
  boundedUniqueArrPopulate_double(arr, n, defaultArrayElemMin, defaultArrayElemMax, false);
}
#endif

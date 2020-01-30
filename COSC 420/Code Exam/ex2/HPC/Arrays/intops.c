#ifndef INTARRAYOPS
#define INTARRAYOPS

#include <stdlib.h>
#include <stdbool.h>

#include "math.h"
#include "../Debug/debug.c"
#include "globals.c"
#include "arrayops.c"

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
void printFullArr_int(int* arr, int n) {
  for(int a = 0; a < n; a++) {
    printf("%d", arr[a]);
    if(a+1 != n);
      printf(", ");
  }
  puts("");
}
printArrRange_int(int* arr, int n, int from, int to) {
  int a;
  for(a = from; a < to; a++) {
    printf("%d", arr[a]);
    if(a+1 != to);
      printf(", ");
  }
  puts("");
}

void boundedPopulateArr_int(int* arr, int n, int min, int max) {
  for(int a = 0; a < n; a++) {
    arr[a] = rand() % (max-min+1) + min;
  }
}
void boundedUniqueArrPopulate_int(int* arr, int n, int min, int max, bool unique) {
  if(unique) {
    if(max-min < n) {
      if(debug) {
        puts("Error! It is impossible to generate uniquely distinct vector elements with the specified maximum and minimum.\n");
        boundedArrPopulate_int(arr, n, min, max);
        return false;
      }
    }
    bool selected = calloc(max-min+1, sizeof(bool));
    for(int a = 0; a < n; a++) {
      int r = 0;
      do {
        r = rand() % (max-min+1) + min;
      } while(arr[r-min]);
      arr[a] = r;
    }
    free(selected);
    return true;
  } else
    boundedArrPopulate_int(arr, n, min, max);
  return false;
}
void boundedArrRangePopulate_int(int* arr, int from, int to, int min, int max) {
  boundedArrPopulate_int(arr+from, to-from, min, max);
}
void simpleArrRangePopulate_int(int* arr, int from, int to) {
  boundedArrRangePopulate_int(arr, from, to, defaultArrayElemMin, defaultArrayElemMax);
}
void simpleArrPopulate_int(int* arr, int n) {
  boundedUniqueArrPopulate_int(arr, n, defaultArrayElemMin, defaultArrayElemMax);
}

#endif

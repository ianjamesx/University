#include "binsearch.h"
#include <iostream>
using namespace std;

int Binsearch::binarySearch(int arr[], int size, int val, int &fail){

  int first = 0;
  int last = size - 1;
  int middle;
  
  int comparisons = 0;

  while(last >= first){

    middle = last + (first - last)/2;

    if(arr[middle] == val){

      return middle;

    } else if(arr[middle] > val){

      last = middle - 1;

    } else {

      first = middle + 1;

    }
    
    comparisons++;

  }
  
  fail += comparisons;

  return -1;

}

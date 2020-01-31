#include <iostream>
#include "delSelsort.h"
using namespace std;

void selectionSort(int[], int);

int main(){

  int arr[8] = {13, 5, 2, 25, 47, 17, 8, 21};
  
  delSelsort sort;
  
  sort.doubleSelectSort(arr, 8);

  return 0;

}

//traditional selection sort

void selectionSort(int arr[], int size){

  int temp, min;

  for( int i = 0; i < size; i++){

    min = i;

    for(int j = i; j < size; j++){

      if(arr[j] < arr[min]){

        min = j;

      }

    }

    temp = arr[i];
    arr[i] = arr[min];
    arr[min] = temp;

  }

}


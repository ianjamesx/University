#include <iostream>
#include "delSelsort.h"
using namespace std;

void selectionSort(int[], int);
void delSelectionSort(int[], int);
void printArr(int[], int);

int main(){

  int arr[8] = {13, 5, 2, 25, 47, 17, 8, 21};

  delSelectionSort(arr, 8);
  printArr(arr, 8);

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

//double ended selection sort

void delSelectionSort(int arr[], int size){
  
  int min, max; //minimum and maximum values we find
  int minCount, maxCount; //indexes of minimum and maximum values
  int end = size-1; //furthest element we can observe
  int i, j, l; //control vars

  for(i = 0; i < end; i++){
    
      minCount = i;
      min = arr[i];
      
      maxCount = end;
      max = arr[end];
      
      j = end;

      for(l = i + 1; l < size; l++){
	
	//if we find smallest value, store in min
	
	  if(arr[l] < min){
	    
	      min = arr[l];
	      minCount = l;
	      
	    }
	    
	  //if we find the biggest value store in max

	  else if(arr[j] > max){
	    
	      max = arr[j];
	      maxCount = j;
	      
	    }
	    
	  //incrementer j will be moving from end to start of array
	    
	  j--;
	  
	  printArr(arr, size);
	  
	}
	
      //move min and max values to appropriate positions (start - smallest, end - biggest)

      arr[minCount] = arr[i];
      arr[i] = min;
      arr[maxCount] = arr[end];
      arr[end] = max;

      end--;
      
  }

} 

void printArr(int arr[], int size){
  
  int i;
  for(i = 0; i < size; i++){

    cout << arr[i] << " ";

  }

  cout << "\n\n";

}

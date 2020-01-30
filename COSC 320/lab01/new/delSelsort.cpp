#include <iostream>
#include "delSelsort.h"
using namespace std;

void delSelsort::doubleSelectSort(int arr[], int size){
  
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
	  
	  cout << "iteration " << i << ", seeking elements " << l << " and " << j << ": ";
	  
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

void delSelsort::printArr(int arr[], int size){
  
  int i;
  for(i = 0; i < size; i++){

    cout << arr[i] << " ";

  }

  cout << "\n\n";
  
}
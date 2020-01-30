#include <iostream>
#include "binsearch.h"
#include "delSelsort.h"

//some libraries for random number generation
#include <cstdlib>
#include <ctime>
using namespace std;

const int ARRSIZE = 10000;
const int RANDOMLIMIT = 99999;
const int RANDOMVALUES = 10000;

int main(){

  int arr[ARRSIZE];
  
  //fill arr with random values
  int i;
  for(i = 0; i < ARRSIZE; i++){
    
    arr[i] = rand()%(RANDOMLIMIT-0 + 1) + 0;
    
  }
  
  //sort array
  
  delSelsort sort;
  
  sort.doubleSelectSort(arr, ARRSIZE);
  
  //search for random value RANDOMVALUE times
  
  int sumFailCom = 0, successTotal = 0;
  
  for(i = 0; i < RANDOMVALUES; i++){
  
    int randomVal = rand()%(RANDOMLIMIT-0 + 1) + 0;
    
    Binsearch bin;
    
    int index = bin.binarySearch(arr, ARRSIZE, randomVal, sumFailCom);
    
    if(index != -1) successTotal++;
    
  }
  
  cout << "total iterations in unsuccessful binary searches: " << sumFailCom << "\n";
  cout << "total successful binary searches " << successTotal << "\n";
  cout << "worst case comparison results: " << sumFailCom/(RANDOMVALUES - successTotal) << "\n\n";

  return 0;
  
}

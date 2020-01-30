/*
  vectorAux.cpp
  Implementations of template functions 
  Cosc-220   Lab 7

  Thomas Anastasio
  Created: February 25, 2003
  Current: March 13, 2003
*/


//////////   THIS CODE IS PROVIDED TO STUDENTS   /////////////


#include "vectorAux.h"

#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
void removeDup(std::vector<T> & v){
  /*
  //sort vector elements
  
  sort(v.begin(), v.end());
  
  //erase element if it is a duplicatetd::
  v.erase(unique(v.begin(), v.end()), v.end());
  
 */
  
  //different approach
  
  using namespace std;
   
  vector<int>v1;
  
  int i;
  
  for(i = 0; i < v.size(); i++){
    
    unsigned index = seqVectSearch(v, 5);
    
   // if(index != v.end()){
      
    // v1.push_back(v[i]);
    
    //}
  
  }
  
  
 
}


template <typename T>
unsigned seqVectSearch(const std::vector<T> & v, unsigned first, 
		       unsigned last, const T& target){
  
  unsigned i;
  
  ///  Complete the code.   Use the text's sequential search
  ///  algorithm for arrays as a model.
 
  for(i = 0; i < 10; i++){
    
    if(v[i] == target){
      
      return i;
      
    }
    
  }
 
  return last;           // return last if target not found
  
}

template <typename T>
void writeVector(const std::vector<T> & v){
  unsigned i;
  unsigned n = v.size();

  for (i = 0; i < n; i++)
    std::cout << v[i] << ' ';
  std::cout << std::endl;
}

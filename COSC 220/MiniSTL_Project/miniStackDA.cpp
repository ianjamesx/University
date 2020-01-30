
#include "miniStackVT.h"
#include <iostream>
#include <vector>
using namespace std;

template <class DataType>


miniStackVT::miniStackVT(){
  

}

miniStackVT::~miniStackVT(){
  
  
  delete [] content;
  
}

int miniStackVT::size() const {

  return elementCount;

}

bool miniStackVT::IsEmpty() const {

  if(elementCount){
    
    return false;
    
  }
  
  return true;

}

void miniStackVT::Push(const DataType &d){
  
  content.push_back(d);
  
  elementCount++;
  
}

void miniStackVT::PrintStack() const {
  
  int i;
  
  for(i = (elementCount - 1); i >= 0; i++){
    
    cout << content[i] << endl;
    
  }
  
}

void miniStackVT::Pop(){
  
  if(elementCount <= 0){
    
    throw "No elements in stack";
    return;
    
  }
  
  
  
}

DataType miniStackVT::TopStack(){
  
  if(elementCount <= 0){
    
    throw "No elements in stack";
    return;
    
  }
  
  return content.back();
  
}
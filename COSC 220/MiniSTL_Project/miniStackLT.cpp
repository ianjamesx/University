
#include "miniStackVT.h"
#include <iostream>
#include <vector>
using namespace std;

template <class DataType>


miniStackVT::miniStackVT(){
  

}

miniStackVT::~miniStackVT(){
  
  
  
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
  
  //iterate through all elements of list
  //keep in mind, going back to front (as this is a stack)
  
  list<DataType>::iterator iter;
  
  iter = content.end();
  while(iter != content.begin()){
    
    cout << *iter << endl;
    iter--;
    
  }
  
}

void miniStackVT::Pop(){
  
  if(elementCount <= 0){
    
    throw "No elements in stack";
    return;
    
  }
  
  content.pop_back();
  
}

DataType miniStackVT::TopStack(){
  
  if(elementCount <= 0){
    
    throw "No elements in stack";
    return;
    
  }
  
  return content.back();
  
}
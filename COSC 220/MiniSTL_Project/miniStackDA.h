#ifndef MINISTACKDA_H
#define MINISTACKDA_H

template <class DataType>

class miniStackDA {
  
private:
  
/* 
ONE of the following depending on XX 
vector<DataType> content;
list<DataType> content;
DataType *content;
*/

DataType *content;

int elementCount;// number of elements in the stack

public:
  
  miniStackDA();		// constructor create a stack with size zero
  ~miniStackDA();		// destructor 
  int size() const;		// return the number of elements in the stack
  bool IsEmpty() const;		// check empty stack
  void Push (const DataType & );// push a node in the stack
  void PrintStack() const;	// print all stack content (TOP to BOTTOM)
  void Pop();			// Pop an element from the top of stack. 
  
  // Issue exception if the stack is empty
  
  DataType& TopStack(); // Return Data from the top of the stack.
    
  // Issue exception if the stack is empty

};

#include "miniStackDA.cpp"
#endif
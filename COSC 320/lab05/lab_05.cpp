#include <iostream>
#include "int.h"

#include <cstdlib>
#include <ctime>

#include "d_stree.h"
//#include "d_stiter.h"
#include "d_except.h"

#include <utility>

using namespace std;

int main(){
 
  int i;
  
  //testing the integer object
  
  //integer test1(12);
  
  //cout << test1;
  
  stree<integer> intTree;
  
  for(i = 0; i < 10000; i++){
    
    int randomValue = rand() % 7;
    
    stnode<integer> *foundNode = intTree.findNode(randomValue);
    
    if(foundNode == NULL){
      
      //the value we are looking for is not in the tree
      //insert it
      
      intTree.insert(randomValue);
      
    } else {
      
      //already in tree, increment its count
      
      foundNode->nodeValue.incCount();
      
    }
   
  }
  
  intTree.displayTree(5);

  return 0;
  
}
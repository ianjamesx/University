
#ifndef LINK_H
#define LINK_H

template <typename T>

class node{
  
  public:

    T nodeValue;

    node<T>* next;

    node():nodeValue(0), next(NULL){}
      
      //nodeValue = 0;
      //next = NULL;
      
     // default constructor to set nodeValue to be zero and next to be NULL

    node(const T& item, node *nextNode=NULL): nodeValue(item), next(nextNode) {}
      
      //nodeValue = item;
      //next = nextNode;
      
     // constructor to set nodeValue to be newValue and next to nextNode
    
};

#include "linkFun.cpp"

#endif

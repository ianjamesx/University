#include "link.h"
//template <typename T>
/*
Node<T>* CreateNode(const T &value){
  
  //create temporary node
  
  Node<T> *tempNode;
  
  tempNode = new Node(value);
  
  return tempNode;
  
}

void InsertNode(node<T> * &front, const T &value){
  
  //first, create node with passed value
  
  Node<T>* newNode = CreateNode(value);
  
  //if the front does not point anywhere (list does not exist)
  
  //OR if fronts value is greater than the value of the the new node (with value passed)
  //since we are going in ascending order, we put this node in front (if newNode < firstNode)
  
  if(front->next == NULL || front->nodeValue >= newNode->nodeValue){
    
    newNode->next= front;
    front = newNode;
  
  } else {
    
    //make a temporary node called curr
    
    node<T> *curr = front;
    
    //if we are not at end of array, and the newNode value is still greater than the current
    //node we are comparing (again, we are going in ascending order, so smallest -> greatest)
    
    while(curr->next != NULL && curr->next->nodeValue < newNode->nodeValue){
      
      //move to next node
      
      curr = curr->next;
    
    }
    
    //once we are out we are either at end of loop, or have found an adequet spot for our newNode
    
    nodeNew->next = curr->next;
    curr->next = newNode;
    
  }
  
}

Node<T>* SearchNode(Node<T> *front, const T &value){
  
  Node<T> *curr = front;
  
  //loop through all nodes in the list
  
  while(curr->next != NULL){
    
    //if we find a match, return current node
    
    if(curr->nodeValue == value){
      
      return curr;
      
    //if not, keep moving
      
    } else {
    
      curr = curr->next;
    
    }
  
  }
  
  //we need to return something of type Node* with value NULL,
  //curr will have NULL by this point
  
  return curr;
  
}

void DeleteNode(node<T>* &front, const T &value){
  
  Node* prev, curr;
  
  prev = NULL;
  curr = prev;
  
  bool found = false;
  
  //while the current Node exitst and we haven't found our target yet
  
  while(curr != NULL && !found){
    
    //if we find our target
    
    if(curr->nodeValue == target){
      
      //if the node before our target is null (we found target at front of list)
      
      if(prev == NULL){
	
	front->next = curr->next;
      
      } else {
	
	//target node is not in front, lets redirect the previous node to route to
	//the node in front of this node
	
	prev->next = curr->next;
	
      }
      
      //delete the current node (one of which we delete)
      //set found to be true to stop loop
      
      delete curr;
      found = true;
      
    }
    
    //move to next node
    
    prev = curr;
    curr = curr->next;
    
  }
  
}

void PrintList(node<T>* front, const string &separator = " "){
  
  Node<T> *curr = front;
  
  while(curr->next != NULL){
    
    cout << curr->nodeValue << separator;
    
    curr = curr->next;
    
  }
  
}

*/
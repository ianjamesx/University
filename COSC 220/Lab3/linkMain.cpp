#include <iostream>
#include "link.h"
using namespace std;

int main(){

  node<int> *front = NULL;
  
  cout << "hi" << endl;
  
  char input;
  
  cout << "Hello, user, Welcome to Ian's Linked List software\n" <<
	  "here are your options: " << endl;
  
  while(input != 'X' || input != 'x'){
    
    cout << "Enter 'I' to insert a node" << endl;
    cout << "Enter 'D' to delete a node" << endl;
    cout << "Enter 'P' to print the list" << endl;
    cout << "Enter 'S' to search the list for a specific node" << endl;
    cout << "Enter 'X' to quit the program" << endl;
    
    cin >> input;
    
    if(input == 'I' || input == 'i'){
      
      int nodeVal;
      
      cout << "Please input a value for the new node (as an integer value)" << endl;
      
      cin >> nodeVal;
      
     // InsertNode(front, &nodeVal);
      
    } else if(input == 'D' || input == 'd'){
      
      int targetVal;
      
      cout << "Please input a value of the node you want to delete (as an integer value)" << endl;
      
      cin >> targetVal;
      
     // DeleteNode(front, &targetVal);
      
    } else if(input == 'P' || input == 'p'){
      
     // PrintList(front);
      
    } else if(input == 'S' || input == 's'){
      
      int searchVal;
      
      cout << "Input value of the node of which you want to search for (as an integer value)" << endl;
      
      cin >> searchVal;
      
     // SearchNode(front, &searchVal);
      
    } else if(input == 'X' || input == 'x'){
      
      cout << "Thanks for using Ian's Linked List software" << endl;
      
    } else {
      
      cout << "Invalid command, please refer to your options list and try again" << endl;
      
    }
    
  }

  return 0;

}
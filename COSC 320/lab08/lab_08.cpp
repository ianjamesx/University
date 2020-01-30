#include <iostream>
#include "d_pqueue.h"
#include "preqrec.h"
#include <cstdlib> //for random numbers
#include <string>
using namespace std;

//apologies for my absence on monday, I have the flu

int main(){

  miniPQ<procReqRec> mqp;

  //push random process request records into the priority queue
  //until we have 10 (a - j) records in queue

  //for simplicity, lets make an array of process request records

  procReqRec arr[10];

  arr[0].setName("Priority A");
  arr[0].setPriority((rand() % 40));

  arr[1].setName("Priority B");
  arr[1].setPriority((rand() % 40));

  arr[2].setName("Priority C");
  arr[2].setPriority((rand() % 40));

  arr[3].setName("Priority D");
  arr[3].setPriority((rand() % 40));

  arr[4].setName("Priority E");
  arr[4].setPriority((rand() % 40));

  arr[5].setName("Priority F");
  arr[5].setPriority((rand() % 40));

  arr[6].setName("Priority G");
  arr[6].setPriority((rand() % 40));

  arr[7].setName("Priority H");
  arr[7].setPriority((rand() % 40));

  arr[8].setName("Priority I");
  arr[8].setPriority((rand() % 40));

  arr[9].setName("Priority J");
  arr[9].setPriority((rand() % 40));

  //put all process request records into priority queue

  int i;
  for(i = 0; i < 10; i++){

    mqp.push(arr[i]);

  }

  //get the top element (highest priority), then pop it off

  for(i = 0; i < 10; i++){

    cout << mqp.top();
    mqp.pop();

  }

  return 0;

}

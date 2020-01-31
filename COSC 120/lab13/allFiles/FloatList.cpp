//we will need all of these for input, printing, and file reading

#include "FloatList.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

FloatList::FloatList(){

  length = 0;

}

void FloatList::getList(ifstream &infile){

  //we'll need locals to store the input, and the incrementer

  float inputData;
  int i = 0;

  while(infile >> inputData){

    values[i] = inputData;

    i++;

  }

  //update the length member to match the amount of values put into the array

  length = i;

}

void FloatList::printList() const{

  int i;

  for(i = 0; i < length; i++){

    cout << values[i] << endl;

  }

}

void FloatList::printAvg(){

  int i;
  float total = 0;

  for(i = 0; i < length; i++){

    total += values[i];

  }

  cout << "Average temperature is " << (total / length) << endl;

}

FloatList::~FloatList(){

}

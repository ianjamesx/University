#include <iostream>
#include <fstream>
#include "Inventory.h"
using namespace std;

//declares class called inventory that has itemNumber (id of product)
//and numOfItem (contains quantity on hand of corresponding product)

//both members private

//read values form file and store them in an array of objects
//it will then print values to the screen

//Ian Thomas

const int NUMOFPROD = 10;

int main(){

  ifstream infile;
  infile.open("Inventory.dat");

  Inventory products[NUMOFPROD];

  int pos = 0;
  int id;
  int total;

  while(infile >> id >> total){

    products[pos].getId(id);
    products[pos].getAmount(total);

    pos++;

  }

  //display each item

  int i;

  for(i = 0; i < pos; i++){

    products[i].display();

  }

  return 0;

}

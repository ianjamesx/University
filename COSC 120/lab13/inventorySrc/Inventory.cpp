
#include "Inventory.h"
#include <iostream>

using namespace std;

void Inventory::getId(int item){

  itemNumber = item;

}

void Inventory::getAmount(int num){

  numOfItem = num;

}

void Inventory::display(){

  cout << "Item number " << itemNumber << " Has " << numOfItem << " Items in stock" << endl;

}

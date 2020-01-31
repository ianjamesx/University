//program reads floating point data from file
//places values in a private data member called Values (float arr)
//of FloatList class, values printed to screen

//input done by member function called GetList

//output done by PrintList

//quantity of data read in is stored in private data member caleld Length

//member function GetList is called first so length can be initialized to zero

#include <iostream>
#include <fstream>
#include <iomanip>
#include "FloatList.h"

using namespace std;

int main(){

  ifstream tempData;
  FloatList list;

  cout << fixed << showpoint;
  cout << setprecision(2);

  tempData.open("temperatures.txt");

  list.getList(tempData);
  list.printList();
  list.printAvg();

  return 0;

}

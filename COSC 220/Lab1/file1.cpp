  // file1.cpp
  // Contains the main function
  // Demo file for Cosc-220 Lab 1
  //
  // ian thomas
  // Created: 09/17/18

  #include <iostream>
  #include "file2.h"

  int main()
  {
    using namespace std;
    int i = 3;
    int sq;

    sq = SquareIt(i);
    cout << "Square of " << i << " is " << sq << endl;
    return 0;
  } 

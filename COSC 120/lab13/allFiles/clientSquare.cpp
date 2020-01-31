//program declares square class and uses member functions
//to find perimeter and area of square

#include <iostream>
#include "Square.h"
using namespace std;

//Ian Thomas

int main(){

  //user defined

  Square box;
  float size;

  //defined with value 9

  Square box1(9);

  cout << "Enter length of side of square" << endl;
  cin >> size;

  box.setSide(size);

  cout << "Area of box: " << box.findArea() << endl;

  cout << "perimeter of box: " << box.findPerimeter() << endl;

  cout << "Area of box1: " << box1.findArea() << endl;

  cout << "perimeter of box1: " << box1.findPerimeter() << endl;

  return 0;

}

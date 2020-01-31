#include <iostream>
#include <iomanip>
using namespace std;

//uses structure to hold data about a rectangle
//calcs area and perimeter

//Ian Thomas

struct Dimensions {

  float length;
  float width;

};

//need to define results before rectangle

struct Results {

  float area;
  float perimeter;

};

struct Rectangle {

  Results attributes;
  Dimensions sizes;

};

float computeArea(float, float);
float computePerim(float, float);

int main(){

  Rectangle box;

  cout << "Enter length of Rectangle: ";

  cin >> box.sizes.length;

  cout << "Enter width of Rectangle: ";

  cin >> box.sizes.width;

  cout << endl << endl;

  box.attributes.area = computeArea(box.sizes.length, box.sizes.width);
  box.attributes.perimeter = computePerim(box.sizes.length, box.sizes.width);

  cout << fixed << showpoint << setprecision(2);
  cout << "Area of the rectangle is " << box.attributes.area << endl;
  cout << "Perimeter of the rectangle is " << box.attributes.perimeter << endl;
  
  return 0;

}

float computeArea(float length, float width){

  return length * width;

}

float computePerim(float length, float width){

  return (length * 2) + (width* 2);

}

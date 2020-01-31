#include <iostream>
#include "Circles.h"
using namespace std;

const double PI = 3.14;

//construct

Circles::Circles(){

  radius = 1;
  centerX = 0;
  centerY = 0;

}

Circles::Circles(float rad){

  radius = rad;
  centerX = 0;
  centerY = 0;

}

Circles::Circles(int x, int y){

  radius = 1;
  centerX = x;
  centerY = y;

}

Circles::Circles(float rad, int x, int y){

  radius = rad;
  centerX = x;
  centerY = y;

}

Circles::~Circles(){

  cout << "This concludes the Circles class" << endl;

}

double Circles::findArea(){

  return PI * (radius * radius);

}

double Circles::findCircumference(){

  return (2 * PI * radius);

}

void Circles::printCircleStats(){

  cout << "Radius of circle is " << radius << endl;
  cout << "Center of circle is (" << centerX << ", " << centerY << ")" << endl;

}

#include <iostream>
using namespace std;

class Point {

  float x, y;

  public:

    Point();
    Point(float, float);

    void setX(float);
    void setY(float);

    float getX() const;
    float getY() const;

}

Point:: Point(){

  x = 0;
  y = 0;

}

Point:: Point(float xc, float yc){

  x = xc;
  y = yc;

}

void Point:: setX(float xc){

  x = xc;

}

void Point:: setY(float yc){

  y = yc;

}

float Point: getX(){

  return x;

}

float Point: getY(){

  return y;

}

float operator+(Point p1, Point p2){

  return sqrt((pow(p1.getX() - p2.getX()), 2) + (pow(p1.getY() - p2.getY())), 2);

}

int main(){

  Point p1;

  Point p2(2, 5);

  cout << p1 + p1;

  return 0;

}

#include <iostream>
#include "Circles.h"
using namespace std;

int main(){

  Circles sphere1(2);

  Circles sphere2;

  Circles sphere3(15, 16);

  sphere1.printCircleStats();

  cout << "Area of circle is " << sphere1.findArea() << endl;
  cout << "The circumference of the circle is " << sphere1.findCircumference() << endl;

  cout << "\n";

  sphere2.printCircleStats();

  cout << "Area of circle is " << sphere2.findArea() << endl;
  cout << "The circumference of the circle is " << sphere2.findCircumference() << endl;

  cout << "\n";

  sphere3.printCircleStats();

  cout << "Area of circle is " << sphere3.findArea() << endl;
  cout << "The circumference of the circle is " << sphere3.findCircumference() << endl;

  return 0;

}

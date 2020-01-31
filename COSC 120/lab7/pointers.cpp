//program uses pointers
//Ian Thomas

#include <iostream>
using namespace std;

int main(){

  int length;
  int width;
  int area;

  int *lengthPtr = nullptr;
  int *widthPtr = nullptr;

  cout << "Please input the length of the rectangle" << endl;
  cin >> length;

  cout << "Please input the width of the rectangle" << endl;
  cin >> width;

  lengthPtr = &length;
  widthPtr = &width;

  area = *lengthPtr * *widthPtr;

  cout << "The area is " << area << endl;

  if(*lengthPtr > *widthPtr){

    cout << "Length is greater than width" << endl;


  } else if(*widthPtr > *lengthPtr){

    cout << "Width is greater than length" << endl;


  } else {

    cout << "Width and length are the same" << endl;

  }

  return 0;

}

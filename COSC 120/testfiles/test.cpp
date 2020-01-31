#include <iostream>

using namespace std;

void recurse(int n);

class Vector {

  int size;
  int *data;

public:

  Vector(); //default size to 0, data to NULL
  Vector(int length);
  Vector(int *arr, int length); //put a copy of an array in data

  void addElement(int element);
  int getLastElement();

  friend int operator[](int index); //get element in data at index

};


int main(){

  recurse(5);

  return 0;

}

void recurse(int n){

  cout << n << endl;
  n--;
  if(n > 0){
    recurse(n);
  }

}

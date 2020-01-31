//program demonstrates a binary search

//Ian Thomas

#include <iostream>
using namespace std;

int binarySearch(int [], int, int);

const int SIZE = 16;

int main(){

  int found, value;

  //array now in ascending order

  int array[] = {0, 2, 2, 3, 4, 6, 7, 8, 9, 10, 11, 13, 13, 14, 15, 17};

  cout << "Enter an integer to search for:" << endl;

  cin >> value;

  found = binarySearch(array, SIZE, value);

  if(found == -1){

    cout << "The value " << value << " was not found" << endl;

  } else {

    cout << "The value " << value << " is in position " << found + 1 << " of the list" << endl;

  }

  return 0;

}

struct Node {

  Node *next;
  int val;

};

int binarySearch(int array[], int numElems, int value){

  //array was rearranged to be search through arrays in ascending order

  int first = 0;
  int last = numElems - 1;
  int middle;

  while(last >= first){

    middle = last + (first - last)/2;
    cout << first << ", " << middle << ", " << last << endl;

    if(array[middle] == value){

      return middle;

    } else if(array[middle] > value){

      last = middle - 1;

    } else {

      first = middle + 1;

    }

  }

  return -1;

}

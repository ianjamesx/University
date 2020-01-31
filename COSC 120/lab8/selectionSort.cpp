//program uses a selection sort
//to put integers in ascending order

//Ian Thomas

/* Note

for the lab 8.3 excercises,
all changes were applied to THIS algorithm
rather than bubble sort

*/

#include <iostream>
using namespace std;

void selectionSortArray(int[], int);
void displayArray(int[], int);

const int SIZE = 8;

int main(){

  int values[SIZE] = {23, 0, 45, -3, -78, 1, -1, 9};

  cout << "The values before the selection sort is performed are:" << endl;
  displayArray(values, SIZE);

  selectionSortArray (values, SIZE);

  cout << "The values after the selection sort is performed are:" << endl;

  displayArray(values, SIZE);

  return 0;

}

void displayArray(int array[], int elems){

  for(int count = 0; count < elems; count++){

    cout << array[count] << " ";

  }

  cout << endl;

}

void selectionSortArray(int array[], int elems){

  int seek;
  int minCount;
  int minValue;

  for(seek = 0; seek < (elems - 1); seek++){

    //temporary values for current index in array

    minCount = seek;
    minValue = array[seek];

    for(int index = seek + 1; index < elems; index++){

      //switch sign to sort in descending order
      //rather than ascending

      if(array[index] > minValue){

        //switch values if its bigger

        minValue = array[index];
        minCount = index;

      }

    }

    //exchange smallest value in pass with smallest value found

    array[minCount] = array[seek];
    array[seek] = minValue;

    //print array throughout each step of sorting

    cout << "Iteration: " << seek << ", the current array is" << endl;
    displayArray(array, elems);

  }

}

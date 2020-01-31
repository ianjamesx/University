//student generated code assignment
//Ian Thomas

#include <iostream>
using namespace std;

int binarySearch(int [], int, int);
void selectionSortArray(int[], int);
float findAvg(int[], int);

int main(){

  int size, i;

  cout << "Please enter the size of the array (at most 50)" << endl;

  cin >> size;

  //limit to 50 elements in the array

  if(size > 50){

    size = 50;

  }

  //creating two arrays, since program requires output of array as originally entered by user
  //one array will be sorted and searched, one will not

  int arr[size], unsortedArr[size];

  //then, take values from user

  for(i = 0; i < size; i++){

    cout << "Enter element " << (i + 1) << endl;

    cin >> arr[i];

    unsortedArr[i] = arr[i];

  }

  //sort the array

  selectionSortArray(arr, size);

  //take value to look for

  int value;

  cout << "Which value would you like to search for?" << endl;

  cin >> value;

  //search for value with binarySearch

  int result = binarySearch(arr, size, value);

  //find mean of array

  float mean = findAvg(arr, size);

  //alert user of results

  if(result == -1){

    cout << "The value " << value << " was not found in array" << endl;

  } else {

    cout << "The value " << value << " was found at spot " << (result + 1) << " in sorted array" << endl;

  }

  //space

  cout << "\n";

  cout << "The average of all values in array was " << mean << endl;

  //space

  cout << "\n";

  cout << "The array of " << size << " elements as originally entered" << endl;

  for(i = 0; i < size; i++){

    //add line after each element

    cout << unsortedArr[i] << " | ";

  }

  cout << "\n\n";

  cout << "The array of " << size << " elements sorted numerically" << endl;

  for(i = 0; i < size; i++){

    //add line after each element

    cout << arr[i] << " | ";

  }

  cout << "\n\n";

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

      if(array[index] < minValue){

        //switch values if its bigger

        minValue = array[index];
        minCount = index;

      }

    }

    //exchange smallest value in pass with smallest value found

    array[minCount] = array[seek];
    array[seek] = minValue;

  }

}


int binarySearch(int array[], int numElems, int value){

  //array was rearranged to be search through arrays in ascending order

  int first = 0;
  int last = numElems - 1;
  int middle;

  while(last >= first){

    middle = last + (first - last)/2;

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

float findAvg(int array[], int size){

  int total = 0, i;

  for(i = 0; i < size; i++){

    total += array[i];

  }

  float avg = static_cast<float>(total) / size;

  return avg;

}

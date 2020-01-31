//program performs a linear search on a character array

//Ian Thomas

#include <iostream>
using namespace std;

int searchList(int[], int, int); // prototype
const int SIZE = 8;

int main(){

  int nums[SIZE] = {3, 6, -19, 5, 5, 0, -2, 99};
  int found;
  int num;

  //use a do while loop to continue to take in user input
  //will break after user enters a -1

  do {

    cout << "Enter a number to search for, or enter -1 to end" << endl;
    cin >> num;

    //test again inside loop so we do not search for value which ends loop

    if(num != -1){

      found = searchList(nums, SIZE, num);

      if(found == -1){

        cout << "The number " << num << " was not found in the list" << endl;

      } else {

        cout << "The number " << num << " is in the " << found + 1 << " position of the list" << endl;

      }

    }

  } while(num != -1);

  return 0;

}

int searchList(int List[], int numElems, int value){

  for(int count = 0; count <  numElems; count++){

    if(List[count] == value){

      return count;

    }

  }

  return -1;

}

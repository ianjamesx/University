
//take scores, find average, and print the scores in numberic order

//Ian Thomas

#include <iostream>
using namespace std;

float average(int*, int);
void ascend(int*, int);

int main(){

  int size, i;

  cout << "Input the number of scores" << endl;
  cin >> size;

  int *scores = new int[size];

  for(i = 0; i < size; i++){

    cout << "Enter score " << (i + 1) << endl;
    cin >> scores[i];

  }

  cout << "The average score is " << average(scores, size) << endl;

  cout << "Sorted numerically: " << endl;

  //sort in ascending order

  ascend(scores, size);

  //we can now delete our dynamic array

  delete [] scores;

  return 0;

}

float average(int *scores, int size){

  int total = 0, i;

  for(i = 0; i < size; i++){

    total += scores[i];

  }

  float average = static_cast<float>(total) / size;

  return average;

}

/*

using the 'bubble sort' algorithm to rearrange array in numeric order

*/

void ascend(int *scores, int size){

  int i, j;

  //swapped indicates that a swap has occured (we need to continue through loop if it has)
  //temp will be a temporary hold variable for swapping elements

  int swapped = 1, temp;

  for(i = 0; (i < size) && swapped; i++){

    swapped = 0;

    for (j = 0; j < (size - 1); j++){

      //if the next element is bigger, then we swap

       if (scores[j + 1] < scores[j]){

         //switch the two scores

        temp = scores[j];

        scores[j] = scores[j + 1];

        scores[j + 1] = temp;

        //a swap occured, so we set our swap 'flag' to 1, continuing loop

        swapped = 1;

      }

    }

  }

  //finally, print elements in reassorted array

  for(i = 0; i < size; i++){

    cout << scores[i] << endl;

  }

}

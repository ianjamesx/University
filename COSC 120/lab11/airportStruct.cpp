#include <iostream>

using namespace std;

//airport calculator
//Ian Thomas

struct Airport {

  int landed;
  int departed;
  int mostLanded;
  int leastLanded;

};

//define a constant since i used fewer months to test the code

const int MONTHS = 3;

//returns totals for the year
//averages will be calculated in main()

int totalLanded(Airport[]);
int totalDeparted(Airport[]);

//for the following functions, we need to return the day with most planes landed/departed
//since we cannot return two values (we need the number for that day, and the month of which it occured in) without using a pointer
//we return the index of the month in the array

int highestLanded(Airport[]);
int lowestLanded(Airport[]);

int main(){

  Airport year[MONTHS];

  int i;

  //input loop

  for(i = 0; i < MONTHS; i++){

    //take data for each property from user

    cout << "Enter total number of planes landed for month " << (i + 1) << endl;
    cin >> year[i].landed;

    cout << "Enter total number of planes departed for month " << (i + 1) << endl;
    cin >> year[i].departed;

    cout << "Enter greatest number of planes landed on a given day for month " << (i + 1) << endl;
    cin >> year[i].mostLanded;

    cout << "Enter least number of planes landed on a given day for month " << (i + 1) << endl;
    cin >> year[i].leastLanded;

    cout << "\n";

  }

  //output

  //first, get the averages, totals, and most and least landings

  int totalLand = totalLanded(year);
  int totalDepart = totalDeparted(year);

  int mostIndex = highestLanded(year);
  int leastIndex = lowestLanded(year);

  cout << "The total number of planes landed for the year was " << totalLand << endl;
  cout << "The total number of planes departed for the year was " << totalDepart << endl;

  cout << "\n";

  cout << "The average number of planes landed was " << (static_cast<float>(totalLand) / MONTHS) << endl;
  cout << "The average number of planes departed was " << (static_cast<float>(totalDepart) / MONTHS) << endl;

  cout << "\n";

  cout << "The most planes landed on one day was " << year[mostIndex].mostLanded << " during month " << (mostIndex + 1) << endl;
  cout << "The least planes landed on one day was " << year[leastIndex].leastLanded << " during month " << (leastIndex + 1) << endl;

  return 0;

}

//average functions (same logically)

int totalLanded(Airport arr[MONTHS]){

  int i;
  float total = 0;

  for(i = 0; i < MONTHS; i++){

    total += arr[i].landed;

  }

  return total;

}

int totalDeparted(Airport arr[MONTHS]){

  int i;
  float total = 0;

  for(i = 0; i < MONTHS; i++){

    total += arr[i].departed;

  }

  return total;

}

int highestLanded(Airport arr[MONTHS]){

  int i, mostIndex = 0;

  for(i = 0; i < MONTHS; i++){

    if(arr[i].mostLanded > arr[mostIndex].mostLanded){

      mostIndex = i;

    }

  }

  return mostIndex;

}

int lowestLanded(Airport arr[MONTHS]){

  int i, leastIndex = 0;

  for(i = 0; i < MONTHS; i++){

    if(arr[i].mostLanded < arr[leastIndex].mostLanded){

      leastIndex = i;

    }

  }

  return leastIndex;

}

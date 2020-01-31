#include <iostream>
using namespace std;

//convert miles to km
//or km to miles

//Ian Thomas

float milesToKM(float miles);
float kmToMiles(float km);

int main(){

  int input, distance;

  cout << "Enter 1 to convert miles to kilometers" << endl;
  cout << "Enter 2 to convert kilometers to miles" << endl;
  cout << "Enter 3 to exit" << endl;
  cin >> input;

  //the rest of the program will be handled within the switch
  //by calling the user preferred function

  switch(input){

    case 1:

      cout << "Please enter the number of miles" << endl;

      cin >> distance;

      cout << distance << " miles is = " << milesToKM(distance) << " kilometers" << endl;

    break;

    case 2:

      cout << "Please enter the number of kilometers" << endl;

      cin >> distance;

      cout << distance << " kilometers is = " << kmToMiles(distance) << " miles" << endl;

    break;

  }

  return 0;

}

float milesToKM(float miles){

  return (miles * 1.61);

}

float kmToMiles(float kilometers){

  return (kilometers * .621);

}

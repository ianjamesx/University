
// Name: Ian Thomas
// User Name:
// hw#: Project 1

#include <fstream>
#include <iostream>

using namespace std;

enum Choice {LETTER, NUMBER, QUIT};

const int NAME_LEN = 20;

typedef char Name[NAME_LEN + 1];

struct Entry {

  Name name;
  int  PN;

};

//Pre: file "phonenum.txt" must be in directory
//Post: opens file, reads all name/phone-number pairs, and returns how many there were.

int ReadPNs(Entry[]);


//Post: prints out the names of the people with that phone number.
//      prints nothing if that number isn't in the list.

void NumList(const Entry[], int size, int num);


//Post: prints all the name/phone number pairs of everyone whose
//      name starts with that letter.

void LetterList(const Entry[], int size, char ch);


//Pre: int must be at most 7 digits
//Post: prints out as 7-digit phone number (no \n at end.)

void ShowPN(int);


//Post: prints the menu

void Menu();


int main(){

  //define an array of Entry structs

  Entry L[50];

  //size for actual number of defined elements in L array
  //numChoice for choice of user

  int size, numChoice;
  char ch;
  int num;

  //ReadPN method will populate structure array

  size = ReadPNs(L);

  //handle user input

  numChoice = 0;

  while (numChoice != QUIT + 1){

    Menu();

    cin >> numChoice;

    switch(numChoice){

      //take in a character, find their phone numbers

      case  LETTER + 1:

        cout << "Enter initial:";
        cin >> ch;

        LetterList(L, size, ch);

      break;

      //take in a phone number, find a match for their name

      case  NUMBER + 1:

        cout << "Enter number as 7 digits:";
        cin >> num;

        NumList(L, size, num);

      break;

      //stop program

      case QUIT + 1:

        cout << "Thank you!" << endl;

      break;

      //invalid input

      default:

        cerr << "Not an Option!" << endl;
        break;

    }

  }

  return 0;

}

void NumList(const Entry L[], int size, int num){

  //looking for a phone number match

  int i;

  for(i = 0; i < size; i++){

    if(L[i].PN == num){

      //we have a phone number match

      cout << L[i].name << " has this phone number" << endl;

    }

  }

}

void LetterList(const Entry L[], int size, char ch){

  //take in the first initial
  //match it with the first index of user's name array

  int i;

  for(i = 0; i < size; i++){

    ///compare to first index

    if(L[i].name[0] == ch){

      //we found a match to this character

      cout << L[i].name << " has the number: ";

      //the ShowPN method will handle the print out for
      //the requested users phone number, this method is in place
      //so we can append X's to the users phone number if they are less
      //than seven digits

      ShowPN(L[i].PN);

      //add another line break after the phone number print

      cout << "\n";

    }

  }

}

void ShowPN(int n){

  //we need a temporary version of n
  //so we don't overwrite the real n parameter

  int tempNumber = n, digits = 0, i;

  while(tempNumber > 0){

    //take off ten digits on each iteration to find
    //amount of digits in the 'n' parameter

    tempNumber /= 10;

    digits++;

  }

  //first, print out the number

  cout << n;

  //then append the character 'X'
  //for each digit in their phone number they're missing

  for(i = 7; i > digits; i--){

    cout << 'X';

  }

}

int ReadPNs(Entry L[]){

  //count all the name/number pairs in file
  //put them in L array of Entry structs

  ifstream infile;

  string name;
  int num;

  //we need an incrememter to keep track of which index to
  //put data in L array

  int i = 0;

  infile.open("phonenum.txt");

  //take the name and number

  while(infile >> name >> num){

    L[i].PN = num;

    //the .name property is actually a character array, so we need to do a loop
    //in order to assign characters properly

    int j;

    for(j = 0; j < NAME_LEN; j++){

      L[i].name[j] = name[j];

    }

    //increment the index of the structure array

    i++;

  }

  //return value of i as the number of defined elements in array

  return i;

}

void Menu(){

  cout << endl;

  cout << "Enter "<< LETTER + 1 << " to look up names starting"
       << " with a certain letter\n";

  cout << "      " << NUMBER + 1 << " to look up a number\n";

  cout << "      " << QUIT + 1 << " to quit\n";

  cout << "    " ;

}

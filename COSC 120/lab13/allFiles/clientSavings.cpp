#include "SavingsAccount.h"
#include <iostream>

using namespace std;

int main(){

  /*

  first object instance
  bank1

  initialized to user values

  */
  int initDollars, initCents;

  cout << "Enter inital dollars for bank1 account" << endl;
  cin >> initDollars;

  cout << "Enter inital cents for bank1 account" << endl;
  cin >> initCents;

  SavingsAccount bank1(initDollars, initCents);

  //use while loops to allow user to deposit or withdraw amounts

  char deposit, withdraw;

  do {

    cout << "Would you like to make a deposit for bank1 account? (Enter y for yes or n for no)" << endl;
    cin >> deposit;

    //if they want to make a deposit

    if(deposit == 'y' || deposit == 'Y'){

      int depDollars, depCents;

      cout << "Input the dollars to be deposited" << endl;
      cin >> depDollars;

      cout << "Input the cents to be deposited" << endl;
      cin >> depCents;

      bank1.deposit(depDollars, depCents);

    }

  } while(deposit == 'y' || deposit == 'Y');

  do {

    cout << "Would you like to make a withdraw for bank1 account? (Enter y for yes or n for no)" << endl;
    cin >> withdraw;

    //if they want to make a deposit

    if(withdraw == 'y' || withdraw == 'Y'){

      int wdDollars, wdCents;

      cout << "Input the dollars to be withdrawn" << endl;
      cin >> wdDollars;

      cout << "Input the cents to be withdrawn" << endl;
      cin >> wdCents;

      bank1.withdraw(wdDollars, wdCents);

    }

  } while(withdraw == 'y' || withdraw == 'Y');

  cout << "bank1 account:" << endl;

  bank1.print();

  /*

  second object instance
  bank2

  initialized to default values (zero dollars and cents)

  */

  SavingsAccount bank2;

  //deposit and withdraw already defined

  do {

    cout << "Would you like to make a deposit for bank2 account? (Enter y for yes or n for no)" << endl;
    cin >> deposit;

    //if they want to make a deposit

    if(deposit == 'y' || deposit == 'Y'){

      int depDollars, depCents;

      cout << "Input the dollars to be deposited" << endl;
      cin >> depDollars;

      cout << "Input the cents to be deposited" << endl;
      cin >> depCents;

      bank2.deposit(depDollars, depCents);

    }

  } while(deposit == 'y' || deposit == 'Y');

  do {

    cout << "Would you like to make a withdraw for bank2 account? (Enter y for yes or n for no)" << endl;
    cin >> withdraw;

    //if they want to make a deposit

    if(withdraw == 'y' || withdraw == 'Y'){

      int wdDollars, wdCents;

      cout << "Input the dollars to be withdrawn" << endl;
      cin >> wdDollars;

      cout << "Input the cents to be withdrawn" << endl;
      cin >> wdCents;

      bank2.withdraw(wdDollars, wdCents);

    }

  } while(withdraw == 'y' || withdraw == 'Y');

  cout << "bank2 account:" << endl;

  bank2.print();

  return 0;

}

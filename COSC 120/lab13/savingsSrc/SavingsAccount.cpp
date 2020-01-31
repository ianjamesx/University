#include "SavingsAccount.h"
#include <iostream>
using namespace std;

SavingsAccount::SavingsAccount(){

  //default constructor

  dollars = 0;
  cents = 0;

}

SavingsAccount::SavingsAccount(int d, int c){

  //normalize cents to dollars
  //while cents are more than 100, add one to the dollar amount
  //and decrement cents by 100

  while(c >= 100){

    d++;
    c -= 100;

  }

  //then, store local variables in instance variables

  dollars = d;
  cents = c;

}

void SavingsAccount::deposit(int d, int c){

  while(c >= 100){

    d++;
    c -= 100;

  }

  //increment instance variables

  cents += c;
  dollars += d;

}

void SavingsAccount::withdraw(int d, int c){

  while(c > 100){

    d++;
    c -= 100;

  }

  //decrement

  cents -= c;
  dollars -= d;

}

void SavingsAccount::print(){

  cout << "Dollars: " << dollars << endl;
  cout << "Cents: " << cents << endl;

}

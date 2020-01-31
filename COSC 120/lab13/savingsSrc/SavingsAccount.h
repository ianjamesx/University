#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

class SavingsAccount {

public:

  //make parameters d and c so we dont get mixed up with member variables

  void deposit(int d, int c);
  void withdraw(int d, int c);
  void print();

  SavingsAccount();
  SavingsAccount(int d, int c);

private:

  int dollars;
  int cents;

};

#endif

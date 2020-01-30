#include <iostream>
#include <string>
#include "Executive.h"
using namespace std;

Executive::Executive(string fn, string ln, string title, int base, int bonus, int stock){

  firstname = fn;
  lastname = ln;
  jobTitle = title;
  baseSalary = base;
  bonusPayment = bonus;
  stockOption = stock;

}

int Executive::calcSalary(){

  return baseSalary + bonusPayment + stockOption;

}

void Executive::displayStockOption(){

  cout << stockOption << endl;

}

void Executive::displayInfo(){

  displayName();
  displaySalary();
  displayTitle();
  displayBonusPayment();
  displayStockOption();

}

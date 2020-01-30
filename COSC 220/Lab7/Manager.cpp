#include <iostream>
#include <string>
#include "Manager.h"
using namespace std;

Manager::Manager(string fn, string ln, string title, int base, int bonus){

  firstname = fn;
  lastname = ln;
  jobTitle = title;
  baseSalary = base;
  bonusPay = bonus;

}

int Manager::calcSalary(){

  return baseSalary + bonusPay;

}

void Manager::displayBonusPayment(){
  
  cout << bonusPayment << endl;
  
}

void Manager::displayInfo(){
  
  displayName();
  displaySalary();
  displayTitle();
  displayBonusPayment();
  
}
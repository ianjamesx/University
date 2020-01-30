#include <iostream>
#include <string>
#include "TechnicalStaff.h"
using namespace std;

TechnicalStaff::TechnicalStaff(string fn, string ln, string title, int base, int profit){

  firstname = fn;
  lastname = ln;
  jobTitle = title;
  baseSalary = base;
  profitSharing = profit;

}

int TechnicalStaff::calcSalary(){

  return baseSalary + profitSharing;

}

void TechnicalStaff::displayProfitSharing(){
  
  cout << bonusPayment << endl;
  
}

void TechnicalStaff::displayInfo(){
  
  displayName();
  displaySalary();
  displayTitle();
  displayProfitSharing();
  
}
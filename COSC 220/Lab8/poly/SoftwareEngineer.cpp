#include <iostream>
#include <string>
#include "SoftwareEngineer.h"
using namespace std;

SoftwareEngineer::SoftwareEngineer(string fn, string ln, string title, int base, int profit, int over){

  firstname = fn;
  lastname = ln;
  jobTitle = title;
  baseSalary = base;
  profitSharing = profit;
  overtimePay = over;

}

int SoftwareEngineer::calcSalary(){

  return baseSalary + profitSharing;

}

void SoftwareEngineer::displayOvertimePay(){
  
  cout << overtimePay << endl;
  
}

void SoftwareEngineer::displayInfo(){
  
  displayName();
  displaySalary();
  displayTitle();
  displayProfitSharing();
  displayOvertimePay();
  
}
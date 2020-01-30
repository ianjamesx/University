#include <iostream>
#include <string>
#include "Employee.h"
using namespace std;

Employee::Employee(){

}

Employee::Employee(string fn, string ln, string title, int base){

  firstname = fn;
  lastname = ln;
  jobTitle = title;
  baseSalary = base;

}

int Employee::calcSalary(){

  return baseSalary;

}

void Employee::displayName(){

  cout << firstname << " " << lastname << endl;

}

void Employee::displaySalary(){

  cout << baseSalary << endl;

}

void Employee::displayTitle(){

  cout << jobTitle << endl;

}

void Employee::displayInfo(){

  displayName();
  displaySalary();
  displayTitle();

}

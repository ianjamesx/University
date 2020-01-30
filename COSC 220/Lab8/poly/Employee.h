#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
using namespace std;

class Employee {

public:

  Employee();
  Employee(string, string, string, int);
  int calcSalary();
  void displayName();
  void displaySalary();
  void displayTitle();
  virtual void displayInfo();

protected:
  string firstname;
  string lastname;
  string jobTitle;
  int baseSalary;

};

#endif

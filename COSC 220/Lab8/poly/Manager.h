#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <string>
#include "Employee.h"
using namespace std;

class Manager:public Employee {

public:

  Manager();
  Manager(string, string, string, int, int);
  int calcSalary();
  void displayBonusPayment();
  void displayInfo();

protected:

  int bonusPayment;

};

#endif

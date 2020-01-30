#ifndef TECHNICALSTAFF_H
#define TECHNICALSTAFF_H

#include <iostream>
#include <string>
#include "Employee.h"
using namespace std;

class TechnicalStaff: public Employee {

public:

  TechnicalStaff();
  TechnicalStaff(string, string, string, int, int);
  int calcSalary();
  void displayProfitSharing();
  void displayInfo();


protected:

  int profitSharing;

};

#endif

#ifndef SOFWAREENGINEER_H
#define SOFWAREENGINEER_H

#include <iostream>
#include <string>
#include "TechnicalStaff.h"
using namespace std;

class SoftwareEngineer: public TechnicalStaff {

  int overtimePay;

public:

  SoftwareEngineer(string, string, string, int, int, int);
  int calcSalary();
  void displayOvertimePay();
  void displayInfo();

};

#endif

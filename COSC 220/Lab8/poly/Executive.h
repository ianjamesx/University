#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <string>
#include "Manager.h"
using namespace std;

class Executive: public Manager {

  int stockOption;

public:

  Executive(string, string, string, int, int, int);
  int calcSalary();
  void displayInfo();
  void displayStockOption();

};

#endif

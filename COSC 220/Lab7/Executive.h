#include <iostream>
#include <string>
using namespace std;

class Executive {
  
  int stockOption;
  
public:
  
  Executive(string, string, string, int, int, int);
  int calcSalary();
  void displayInfo();
  void displayStockOption();
  
};
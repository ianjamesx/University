#include <iostream>
#include <string>
using namespace std;

class SoftwareEngineer: public TechnicalStaff {
  
  int overtimePay;
  
public:
  
  SoftwareEngineer(string, string, string, int, int);
  int calcSalary();
  void displayOvertimePay();
  void displayInfo();
  
};
#include <iostream>
#include <string>
using namespace std;

class TechnicalStaff: public Employee {
  
public:
  
  TechnicalStaff(string, string, string, int, int);
  int calcSalary();
  void displayProfitSharing();
  void displayInfo();
 
  
protected:
  
  int profitSharing;
  
};
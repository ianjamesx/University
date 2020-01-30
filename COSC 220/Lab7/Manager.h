#include <iostream>
#include <string>
using namespace std;

class Manager:public Employee {
  
public:
  
  Manager(string, string, string, int, int);
  int calcSalary();
  void displayBonusPayment();
  void displayInfo();
  
protected:
  
  int bonusPayment;
  
};
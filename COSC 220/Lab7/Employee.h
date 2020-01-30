#include <iostream>
#include <string>
using namespace std;

class Employee {
  
public:
  
  Employee(string, string, string, int);
  int calcSalary();
  void displayName();
  void displaySalary();
  void displayTitle();
  void displayInfo();
  
protected:
  
  string firstname;
  string lastname;
  string jobTitle;
  int baseSalary;
  
};
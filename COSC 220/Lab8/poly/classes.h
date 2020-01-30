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
  void displayInfo();

protected:

  string firstname;
  string lastname;
  string jobTitle;
  int baseSalary;

};

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

class Executive: public Manager {

  int stockOption;

public:

  Executive(string, string, string, int, int, int);
  int calcSalary();
  void displayInfo();
  void displayStockOption();

};

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

class SoftwareEngineer: public TechnicalStaff {

  int overtimePay;

public:

  SoftwareEngineer(string, string, string, int, int, int);
  int calcSalary();
  void displayOvertimePay();
  void displayInfo();

};


class TestEngineer: public TechnicalStaff{

public:

  TestEngineer(string, string, string, int, int);

};

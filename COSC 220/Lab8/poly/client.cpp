#include <iostream>
#include "Employee.h"
#include "Manager.h"
#include "Executive.h"
#include "TechnicalStaff.h"
#include "SoftwareEngineer.h"
#include "TestEngineer.h"
using namespace std;

int main(){

  Employee empArr[3];

  Executive emp0("James", "Jameson", "Exec", 18000, 4000, 7000);
  SoftwareEngineer emp1("John", "Johnson", "Engineer", 12000, 4000, 7000);
  TestEngineer emp2("Tom", "Tomson", "Tester", 8000, 4000);

  empArr[0] = emp0;
  empArr[1] = emp1;
  empArr[2] = emp2;

  int i;

  for(i = 0; i < 3; i++){

    empArr[i].displayInfo();

  }

  cout << "\n\n\n";

  emp0.displayInfo();
  emp1.displayInfo();
  emp2.displayInfo();
  
  
  //using dynamic binding implementation
  
  Employee *empptr;
  
  cout << "\n";
  
  empptr = new Employee("Ron", "Ronson", "Emp", 18000);
  empptr->displayInfo();
  
  cout << "\n";
  
  empptr = new Executive("Jon", "Jonson", "Exec", 18000, 4000, 7000);
  empptr->displayInfo();
  
  cout << "\n";
  
  empptr = new TestEngineer("Tom", "Tomson", "Tester", 8000, 4000);
  empptr->displayInfo();

  return 0;

}

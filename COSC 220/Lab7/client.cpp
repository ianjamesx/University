#include <iostream>
#include "Employee.h"
#include "Manager.h"
#include "Executive.h"
#include "TechnicalStaff.h"
#include "SoftwareEngineer.h"
#include "TestEngineer.h"
using namespace std;

int main(){
  
  Employee emp1("Ian", "thomas", "engineer", 12);
  Manager m1("Ian", "thomas", "engineer", 12, 12);
  Executive ex1("Ian", "thomas", "engineer", 12, 12, 12);
  TechnicalStaff t1("Ian", "thomas", "engineer", 12, 12);
  SoftwareEngineer se1("Ian", "thomas", "engineer", 12, 12);
  TestEngineer te1("Ian", "thomas", "engineer", 12, 12);
  
  return 0;

}
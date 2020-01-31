#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//program demonstrates partially initialized structure variables
//Ian Thomas

struct taxPayer {

  string name;
  long socialSecNum;
  float taxRate;
  float income;
  float taxes;

};

int main(){

  taxPayer citizen1;
  citizen1.name = "Tim McGuiness";
  citizen1.socialSecNum = 255871234;
  citizen1.taxRate = .35;

  taxPayer citizen2;
  citizen2.name = "John Kane";
  citizen2.socialSecNum = 278990582;
  citizen2.taxRate = .29;

  cout << fixed << showpoint << setprecision(2);

  cout << "Enter this years income for " << citizen1.name << endl;
  cin >> citizen1.income;

  citizen1.taxes = citizen1.income * citizen1.taxRate;

  cout << "Name: " << citizen1.name << endl;
  cout << "Social Security Number: " << citizen1.socialSecNum << endl;
  cout << "Taxes due: " << citizen1.taxes << endl;

  cout << "Enter this years income for " << citizen2.name << endl;
  cin >> citizen2.income;

  citizen2.taxes = citizen2.income * citizen2.taxRate;

  cout << "Name: " << citizen2.name << endl;
  cout << "Social Security Number: " << citizen2.socialSecNum << endl;
  cout << "Taxes due: " << citizen2.taxes << endl;

  return 0;

}

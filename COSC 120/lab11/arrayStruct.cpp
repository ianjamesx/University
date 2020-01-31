#include <iostream>
#include <iomanip>
using namespace std;

//program demonstrates how to use array of structures
//Ian Thomas

struct taxPayer {

  float taxRate;
  float income;
  float taxes;

};

int main(){

  taxPayer citizen[5];

  cout << fixed << showpoint << setprecision(2);

  cout << "Please enter annual income and tax rate for 5 tax payers" << endl;
  cout << endl << endl << endl;

  for(int count = 0; count < 5; count++){

    cout << "Enter this years income for tax payer " << (count + 1) << endl;

    cout << ": ";

    cin >> citizen[count].income;

    cout << "Enter tax rate for tax payer " << (count + 1) << endl;

    cout << ": ";

    cin >> citizen[count].taxRate;

    citizen[count].taxes = citizen[count].income * citizen[count].taxRate;

    cout << endl;

  }

  cout << "Taxes due for this year: " << endl << endl;

  for(int index = 0; index < 5; index++){

    cout << "Tax payer " << (index + 1) << ": " << "$ "
    << citizen[index].taxes << endl;

  }

  return 0;

}

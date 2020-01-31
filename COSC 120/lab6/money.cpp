#include <iostream>
#include <iomanip>
using namespace std;

//Ian Thomas

void normalizeMoney(float& dollars, int cents = 150);

int main(){

  int cents;
  float dollars;

  cout << setprecision(2) << fixed << showpoint;

  cents = 95;

  cout << "\nWe will now add 95 cents to our dollar total \n";

  normalizeMoney(dollars, cents);

  cout << "Converting cents to dollars resulted in $" << dollars << " dollars\n";


  cout << "\nWe will now add 193 cents to our dollar total\n";

  cents = 193;

  normalizeMoney(dollars, cents);

  cout << "Converting cents to dollars resulted in $" << dollars << " dollars\n";


  cout << "\nWe will now add the default value of cents to our dollar total \n";

  //call using default value
  //by this, we mean call without including the cents paremeter

  normalizeMoney(dollars);

  cout << "Converting cents to dollars resulted in $" << dollars << " dollars\n";

  return 0;

}

void normalizeMoney(float& dollars, int cents){

  float total = 0;

  //we need to define sum staticly

  static float sum = 0.0;

  //convert cents to dollars
  //we need to static cast the cents in order to convert properly
  //store it in variable dollars

  dollars = static_cast<float>(cents) / 100;

  total = total + dollars;
  sum = sum + dollars;

  cout << "We have added another $" << dollars << " to our total" << endl;

  cout << "Our total so far is $" << sum << endl;

  cout << "The value of our local variable total is $" << total << endl;

}

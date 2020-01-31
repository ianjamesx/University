//dynamic arrays

//Ian Thomas

#include <iostream>
#include <iomanip>
using namespace std;

int main(){

  float *monthSales = nullptr;

  float total = 0;
  float average;
  int numOfSales;
  int count;

  cout << fixed << showpoint << setprecision(2);

  cout << "How many monthly sales will be processed? ";
  cin >> numOfSales;

  monthSales = new float[numOfSales];

  if(!monthSales){

    cout << "Error allocating memory" << endl;

    return 1;

  }

  cout << "Enter the sales below" << endl;

  for(count = 0; count < numOfSales; count++){

    cout << "sales for Month number "
        << count << " : ";

    cin >> monthSales[count];

  }

  for(count = 0; count < numOfSales; count++){

    total = total + monthSales[count];

  }

  average = total / numOfSales;

  cout << "The average monthly sale is $" << average << endl;

  delete [] monthSales;

  return 0;

}

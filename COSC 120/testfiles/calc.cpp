#include <iostream>
#include <cmath>

using namespace std;

int main(){

  int i;

  double init;

  for(i = 1; i < 11; i++){

    double x = 12.0 / pow(-5, i);

    if(i == 1){

      init = x;

    } else {

      init += x;

    }

    cout << "Sequence " << i << " : " << x;

    cout << "\t Series : " <<  init << endl;

  }

  return 0;

}

#include <iostream>
using namespace std;

//Ian Thomas

void findAverage(float dollars, float& euros, float& pesos);

int main(){

  return 0;

}

void convertMulti(float dollars, float& euros, float& pesos){

  cout << "The function convertMulti was called with dollars, euros, and pesos "
    << endl << " was called with " << dollars << " dollars " << endl << endl;

    euros = dollars * 1.06;
    pesos = dollars * 9.73;

}

#include <iostream>
#include <fstream>
using namespace std;

int main(){
  ofstream out;
  out.open("numbs");
  int i;
  for(i = 0; i <= 100; i++){
    out << i << "\n";
  }
  return 0; 
}
#include <iostream>
#include <set>
#include <map>
#include <string>
#include "d_state.h"

using namespace std;

int main(){
  
  map<string, string> s;
  
  s["MD"] = "Salisbury";
  s["NY"] = "Rochester";
  s["NJ"] = "Princeton";
  s["DE"] = "Dover";
  s["CA"] = "San Diego";
  
  map<string, string>::iterator iter;
  
  string state;
  cout << "Enter a state: ";
  cin >> state;
  
  iter = s.find(state);
  
  if(iter != s.end()){ 
    
    cout << iter->second << endl;
  
  } else {
    
    cout << "Not found in map\n";
    
  }

  return 0;
  
}
#include <iostream>
#include <string>
#include <set>
#include <map>
#include "d_state.h"

using namespace std;

int main(){
  
  set<stateCity> s;
  
  //insert five stateCity objects to s
  
  stateCity sby("MD", "Salisbury");
  stateCity rch("NY", "Rochester");
  stateCity pri("NJ", "Princeton");
  stateCity dvr("DE", "Dover");
  stateCity san("CA", "San Diego");
  
  s.insert(sby);
  s.insert(rch);
  s.insert(pri);
  s.insert(dvr);
  s.insert(san);
  
  //search for a city/state
  
  string state;
  
  cout << "Enter name of state: ";
  cin >> state;
  
  /*
  set<stateCity>:: iterator iter;
  iter = s.find(stateCity(state));
  stateCity found = *iter;
  cout << found;
  */
  
  bool f = false;
  
  set<stateCity>::iterator it;
  for (it = s.begin(); it != s.end(); ++it)
  {
      stateCity found = *it;
      
      if(found.getState() == state){
	cout << found; 
	f = true;
      } 
      
  }
  
  if(!f) cout << "No city was found\n";
  
  return 0;
  
}
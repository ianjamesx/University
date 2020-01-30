#ifndef STATECITY_CLASS
#define STATECITY_CLASS

#include <iostream>
#include <string>

using namespace std;

// object stores the state name and city in the state
class stateCity
{
	public:
		stateCity (const string& name = "", const string& city = ""){
		  
		  stateName = name;
		  cityName = city;
		  
		};
		
		string getState() { return stateName; }

		// output the state and city name in the format
		//    cityName, stateName
		friend ostream& operator<< (ostream& ostr, const stateCity& state){
		  
		  ostr << state.cityName << ", " << state.stateName << endl;
		  
		};
		
		// operators < and == must be defined to use with set object.
		// operators use only the stateName as the key
		friend bool operator< (const stateCity& a, const stateCity& b){
		  
		  if(a.stateName < b.stateName) return true;
		  
		  return false;
		  
		};
		
		friend bool operator== (const stateCity& a, const stateCity& b){
		  
		  if(a.stateName == b.stateName) return true;
		  
		  return false;
		  
		};
	
	private:
		string stateName, cityName;
};

#endif	// STATECITY_CLASS

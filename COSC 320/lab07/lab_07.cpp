#include <iostream>
#include <fstream>
#include "d_hashf.h"
#include "d_hash.h"
#include "d_except.h"
using namespace std;

void getWord(ifstream& fin, string& w);

int main(){
  
  //define the hash table
  
  myhash<string, hFstring>hash(1373);
  
  //just testing out some methods in the hash
  //to see if they work properly
  
  //cout << hash.empty() << endl;
  //cout << hash.size() << endl;
  
  //read every word in file
  
  ifstream infile;
  infile.open("dict.dat");
  
  string word;
  while (infile >> word){
     
    hash.insert(word);
    
  }
  
  //prompt user for a file name
  
  bool fileExists = false;
  
  while(!fileExists){
  
    string fileName;
    cout << "Enter a filename to open (include extension: e.g. .txt, .db): ";
    getline(cin, fileName);
  
    ifstream userfile;
      
    userfile.open(fileName.c_str());
    
    //try-catch block not required, the good() method of an ifstream object works
    //for determining if file exists
    
    if(userfile.good()){
      
      fileExists = true;
      
      //file exists
      
      string wd;
      
      cout << "Words in your file that appear to be misspelled:\n";
      
      while(!userfile.eof()){
	
	getWord(userfile, wd);
	
	//hash.end() will be returned if wd is not
	//in list, then hash.end() will be returned
	
	//print the word
	
	if(hash.end() == hash.find(wd)){
	  
	  cout << wd << endl;
	  
	}
	
      }
      
    } else {
      
      cout << "That file does not exist, please try again\n";
      
    }
   
  }

  return 0;
  
}

//extract a word from fin
void getWord(ifstream& fin, string& w){
	char c;

	w = "";	// clear the string of characters

	while (fin.get(c) && !isalpha(c))
		;	// do nothing. just ignore c

	// return on end-of-file
	if (fin.eof())
		return;

	// record first letter of the word
	w += tolower(c);

	// collect letters and digits
	while (fin.get(c) && (isalpha(c) || isdigit(c)))
		w += tolower(c);

}


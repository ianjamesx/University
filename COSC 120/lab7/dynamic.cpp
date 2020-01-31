//program uses dynamic variables
//Ian Thomas

#include <iostream>
using namespace std;

const int MAXNAME = 10;

int main(){

  int pos;
  char *name = nullptr;
  int *one = nullptr;
  int *two = nullptr;
  int *three = nullptr;
  int result;

  one = new int;
  two = new int;
  three = new int;

  name = new char[MAXNAME];

  cout << "Enter your last name with exactly 10 characters" << endl;
  cout << "If your name has < 10 characters, repeat last letter" << endl
      << "Blanks at the end do not count" << endl;

  for(pos = 0; pos < MAXNAME; pos++){

    cin >> *(name + pos);

  }

  cout << "Hi ";

  for(pos = 0; pos < MAXNAME; pos++){

    cout << *(name + pos);

  }

  cout << endl << "Enter three integer numbers seperated by blanks" << endl;

  cin >> *one;
  cin >> *two;
  cin >> *three;

  cout << "Your numbers were:" << endl;

  cout << *one << endl;
  cout << *two << endl;
  cout << *three << endl;

  result = *one + *two + *three;

  cout << "The sum of these three values is " << result << endl;

  //deallocate

  delete one;
  delete two;
  delete three;
  delete name;

  return 0;

}

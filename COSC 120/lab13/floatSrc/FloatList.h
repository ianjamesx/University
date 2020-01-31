#ifndef FLOATLIST_H
#define FLOATLIST_H

#include <fstream>
using namespace std;

const int MAX_LENGTH = 50;

class FloatList {

public:
  void getList(ifstream&);
  void printList() const;
  void printAvg();

  FloatList();
  ~FloatList();

private:
  int length;
  float values[MAX_LENGTH];

};

#endif

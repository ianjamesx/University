#ifndef TESTENGINEER_H
#define TESTENGINEER_H

#include <iostream>
#include <string>
#include "TechnicalStaff.h"
using namespace std;

class TestEngineer: public TechnicalStaff{

public:

  TestEngineer(string, string, string, int, int);

};

#endif

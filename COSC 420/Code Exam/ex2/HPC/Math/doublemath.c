#ifndef DOUBLEMATH
#define DOUBLEMATH

#include <math.h>
double round_double(double d, unsigned places) {
  const int n = pow(10, places);
  return round(d*n)/n;
}
#endif

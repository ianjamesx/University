#ifndef vectoraux_h
#define vectoraux_h

#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
void removeDup(std::vector<T> & v);
//Precondition: v is nonempty
//Postcondition: duplicates are removed from v

template <typename T>
unsigned seqVectSearch(const std::vector<T> & v, const T& target);
//Purpose: search for target in specified range of elements of v

template <typename T>
void writeVector(const std::vector<T> & v);
//Purpose: displays vector v

#include "vectorAux.cpp"
#endif
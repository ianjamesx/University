
//member functions

#include "Square.h"

Square::Square(){

  side = 1;

}

Square::Square(float size){

  side = size;

}

Square::~Square(){


}

void Square::setSide(float length){

  side = length;

}

float Square::findArea(){

  return side * side;

}

float Square::findPerimeter(){

  return 4 * side;

}

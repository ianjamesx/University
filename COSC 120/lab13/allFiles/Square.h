#ifndef SQUARE_H
#define SQUARE_H

//class declaration

class Square {

    float side;

  public:

    Square();
    Square(float);
    ~Square();
    void setSide(float);
    float findArea();
    float findPerimeter();

};

#endif

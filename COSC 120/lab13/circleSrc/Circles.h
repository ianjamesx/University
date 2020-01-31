#ifndef CIRCLES_H
#define CIRCLES_H

class Circles {

  public:

    double findArea();
    double findCircumference();
    void printCircleStats();
    Circles(float, int, int);
    Circles(int, int);
    Circles(float);
    Circles();
    ~Circles();

  private:

    float radius;
    int centerX;
    int centerY;

};

#endif

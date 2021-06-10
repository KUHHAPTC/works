#ifndef TISOSCELESTRIANGLE_H
#define TISOSCELESTRIANGLE_H

#include "triangle.h"

class TIsoscelesTriangle: public TTriangle
{
public:
    TIsoscelesTriangle(int, int);
    ~TIsoscelesTriangle();
    double CalculateAngle(int, int);
};

#endif // TISOSCELESTRIANGLE_H

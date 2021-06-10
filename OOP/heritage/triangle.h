#ifndef TTRIANGLE_H
#define TTRIANGLE_H

#include "geometricshape.h"

class TTriangle: public TGeometricShape
{
    int a, b;
    double angle;
public:
    TTriangle(int, int, double);
    ~TTriangle();
    double findArea();
    double findPerimeter();
};

#endif // TTRIANGLE_H

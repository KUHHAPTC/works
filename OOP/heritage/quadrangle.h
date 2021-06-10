#ifndef TQUADRANGLE_H
#define TQUADRANGLE_H

#include "geometricshape.h"

class TQuadrangle: public TGeometricShape
{
    int a, b, c;
    double d;
    int angleAB, angleDC;
public:
    TQuadrangle(int, int, int, int, int);
    ~TQuadrangle();
    double findArea();
    double findPerimeter();
};

#endif // TQUADRANGLE_H

#ifndef TELLIPSE_H
#define TELLIPSE_H

#include "geometricshape.h"

class TEllipse: public TGeometricShape
{
    int a;
    int b;
public:
    TEllipse(int, int);
    ~TEllipse();
    double findArea();
    double findPerimeter();
};

#endif // TELLIPSE_H

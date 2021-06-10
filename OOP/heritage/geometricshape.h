#ifndef TGEOMETRICSHAPE_H
#define TGEOMETRICSHAPE_H

#include <QDebug>


class TGeometricShape
{
public:
    TGeometricShape();
    ~TGeometricShape();
protected:
    virtual double findArea() = 0;
    virtual double findPerimeter() = 0;
};

#endif // TGEOMETRICSHAPE_H

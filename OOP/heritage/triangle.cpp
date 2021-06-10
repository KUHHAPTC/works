#include "triangle.h"
#include <math.h>

TTriangle::TTriangle(int z, int x, double v): TGeometricShape()
{
    a = z;
    b = x;
    angle = v;
}

TTriangle::~TTriangle()
{
    qDebug() << "Triangle was destroyed";
}

double TTriangle::findArea()
{
    return (0.5 * a * b * sin(angle));
}

double TTriangle::findPerimeter()
{
    return pow((pow(a, 2) + pow(b, 2) - 2 * a * b * cos(angle)), 0.5) + a + b;
}

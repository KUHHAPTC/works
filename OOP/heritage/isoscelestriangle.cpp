#include "isoscelestriangle.h"
#include <math.h>

TIsoscelesTriangle::TIsoscelesTriangle(int x, int y): TTriangle(x, y, CalculateAngle(x, y))
{
}

TIsoscelesTriangle::~TIsoscelesTriangle()
{
    qDebug() << "Isosceles Triangle was destroyed";
}

double TIsoscelesTriangle::CalculateAngle(int x, int y)
{
    return acos(y / (2.0 * x));
}

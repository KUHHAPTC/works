#include "equilateraltriangle.h"

TEquilateralTriangle::TEquilateralTriangle(int b): TIsoscelesTriangle(b, b)
{
}

TEquilateralTriangle::~TEquilateralTriangle()
{
    qDebug() << "Equilate Triangle was destroyed";
}

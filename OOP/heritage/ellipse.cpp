#include "ellipse.h"
#include <math.h>

TEllipse::TEllipse(int z, int x): TGeometricShape()
{
    a = z;
    b = x;
}

TEllipse::~TEllipse()
{
    qDebug() << "Ellipse was destroyed";
}

double TEllipse::findArea()
{
    return M_PI * a * b;
}

double TEllipse::findPerimeter()
{
    return M_PI * (3 * (a + b) - pow(((3 * a + b) * (a + 3 * b)), 0.5));
        //    (4 * (M_PI * a * b + pow(a - b, 2)) / (a + b));
}

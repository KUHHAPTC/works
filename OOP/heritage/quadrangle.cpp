#include "quadrangle.h"
#include <math.h>

TQuadrangle::TQuadrangle(int k, int z, int m, int v, int q): TGeometricShape()
{
    a = k;
    b = z;
    c = m;
    angleAB = v;
    angleDC = q;
    double x = pow((pow(a, 2) + pow(b, 2) - 2 * a * b * cos(angleAB * M_PI / 180)), 0.5);
    double temp = sin(angleDC * M_PI / 180);
    double angle = asin((c / x) * temp) * 180 / M_PI;
    double last_angle = 180 - angleDC - angle;

    d = pow((pow(x, 2) + pow(c, 2) - 2 * x * c * cos(last_angle * M_PI / 180)), 0.5);
}

TQuadrangle::~TQuadrangle()
{
    qDebug() << "Quadrangle was destroyed";
}

double TQuadrangle::findArea()
{
    double p = findPerimeter() / 2;
    double area = pow(((p - a) * (p - b) * (p - c) * (p - d) - a * b * c * d * pow(cos(((angleAB + angleDC) * (M_PI / 180) / 2)), 2)), 0.5);
    return area;
}


double TQuadrangle::findPerimeter()
{
    return a + b + c + d;
}

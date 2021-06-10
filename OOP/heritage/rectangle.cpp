#include "rectangle.h"

TRectangle::TRectangle(int x, int y): TParallelogram(x, y, 90)
{

}

TRectangle::~TRectangle()
{
    qDebug() << "Rectangle was destroyed";
}

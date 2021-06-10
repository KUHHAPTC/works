#include "square.h"

TSquare::TSquare(int a): TParallelogram(a, a, 90), TRectangle(a, a), TRhombus(a, 90)
{

}


TSquare::~TSquare()
{
    qDebug() << "Square was destroyed";
}

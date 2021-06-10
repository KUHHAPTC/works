#include "rhombus.h"

TRhombus::TRhombus(int x, int angle): TParallelogram(x, x, angle)
{

}


TRhombus::~TRhombus()
{
    qDebug() << "Rhombus was destroyed";
}

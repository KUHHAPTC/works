#include "parallelogram.h"

TParallelogram::TParallelogram(int x, int y, int angle): TQuadrangle(x, y, x, angle, angle)
{

}

TParallelogram::~TParallelogram()
{
    qDebug() << "Parallelogram was destroyed";
}

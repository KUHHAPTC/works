#ifndef TRECTANGLE_H
#define TRECTANGLE_H

#include "parallelogram.h"

class TRectangle: virtual public TParallelogram
{
public:
    TRectangle(int, int);
    ~TRectangle();
};

#endif // TRECTANGLE_H

#ifndef TRHOMBUS_H
#define TRHOMBUS_H

#include "parallelogram.h"

class TRhombus: virtual public TParallelogram
{
public:
    TRhombus(int, int);
    ~TRhombus();
};

#endif // TRHOMBUS_H

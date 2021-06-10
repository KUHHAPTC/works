#ifndef TSQUARE_H
#define TSQUARE_H

#include "rectangle.h"
#include "rhombus.h"

class TSquare: public TRectangle, public TRhombus
{
public:
    TSquare(int);
    ~TSquare();
};

#endif // TSQUARE_H

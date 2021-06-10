#ifndef DERIVESAMPLE_H
#define DERIVESAMPLE_H

#include "sample.h"

class TDeriveSample : public TSample
{
    int active;
public:
    TDeriveSample(int);
    TDeriveSample();
    void draw(QPainter*, QRect, QColor, int);
    void newEvent(bool);
};

#endif // DERIVESAMPLE_H

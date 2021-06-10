#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPainter>

class TSample
{
    int count;
public:
    TSample();
    TSample(int);
    void draw(QPainter*, QRect, QColor, int);
    int getcount();
};

#endif // SAMPLE_H

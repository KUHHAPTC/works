#include "derivesample.h"
#include <math.h>

TDeriveSample::TDeriveSample(int n) : TSample(n)
{
    active = 0;
}

void TDeriveSample::draw(QPainter* p, QRect r, QColor c, int n)
{
    TSample::draw(p, r, c, n);
    qreal cw = 0.5 * r.width();
    qreal ch = 0.5 * r.height();
    qreal cr = 0.9 * (cw > ch ? ch : cw);
    qreal a = 2.0 * acos(-1.0) / n;
    QPointF t(cw + cr * sin(active * a), ch - cr * cos(active*a));
    p->setPen(QPen(Qt::black));
    p->setBrush(QBrush(Qt::yellow));
    p->drawEllipse(t, 0.09 * cr, 0.09 * cr);
}

void TDeriveSample::newEvent(bool direction)
{
    if (direction) active++;
    else active = --active + getcount();
    active = active % getcount();
}

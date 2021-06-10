#include "sample.h"
#include <math.h>

TSample::TSample()
{

}

TSample::TSample(int n)
{
    count = n;
}

int TSample::getcount(){
    return count;
}

void TSample::draw(QPainter* p, QRect r, QColor c, int amount)
{
    count = amount;
    if(count > 2){
        qreal cw = 0.5 * r.width();
        qreal ch = 0.5 * (r.height() + 100);
        qreal cr = 0.9 * (cw > ch ? ch : cw);
        qreal a = 2.0 * acos(-1.0) / count;
        QPointF *t = new QPointF[count];
        for (int i = 0; i < count; i++)
        {
            t[i] = QPointF(cw +cr * sin(i * a), ch - cr * cos(i * a));
        }
        p->setPen(QPen(Qt::black));
        p->setBrush(QBrush(c));
   //     p->drawPolygon(t, count);
        for(int i = 0; i < count; i++){
            for(int j = i; j < count; j++){
                p->drawLine(t[i], t[j]);
            }
        }
        qreal cf = 0.25 * cr;
        QFont font;
        font.setPointSize(cf);
        font.setBold(true);

        p->setFont(QFont("Arial", 12));
        for(int i = 0; i < count; i++){
            QString s = (QString)(i + 49);
            p->drawEllipse(t[i], 0.09 * cr, 0.09 * cr);
            p->drawText(t[i], s);
        }
  //      p->setFont(font);
  //      p->drawText(QRectF(cw - cf, ch - cf, 2.0 * cf, 2.0 * cf),
  //                  QString().setNum(count),
  //                  QTextOption(Qt::AlignCenter));
        delete [] t;
    }
    else{
        p->setFont(QFont("Arial", 18));
        p->drawText(QRectF(75, 250, 350, 150), Qt::AlignCenter, "Вершин должно быть > 2");
    }
}

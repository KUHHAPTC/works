#include "circle.h"

TCircle::TCircle(int r): TEllipse(r, r)
{

}

TCircle::~TCircle()
{
    qDebug() << "Circle was destroyed";
}

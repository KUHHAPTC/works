#include "rational.h"
#include "common.h"
#include <cstdlib>
#include <cmath>

QChar Trational::SEPARATOR = separator;

Trational::Trational()
{
}

Trational::Trational(const int& r, const int& k)
{
    a = r;
    b = k;
}

Trational::Trational(const int& r)
{
    a = r;
    b = 1;
}

Trational Trational::operator*(Trational R)
{
    Trational t;
    t.a = a * R.a;
    t.b = b * R.b;
    return t;
}

Trational Trational::operator/(Trational R)
{
    Trational t;
    t.a = a * R.b;
    t.b = b * R.a;
    if((t.a < 0) && (t.b < 0)) {
        t.a = -t.a;
        t.b = -t.b;
    }
    return t;
}

Trational Trational::operator-(Trational R)
{
    Trational t;
    if(b == R.b)
    {
        t.a = a - R.a;
        t.b = b;
    }
    else {
        t.b = b * R.b;
        t.a = a * R.b - R.a * b;
    }
    return t;
}

Trational Trational::operator-()
{
    Trational t;
    t.a = -a;
    t.b = b;
    return t;
}

Trational Trational::operator+(Trational R)
{
    Trational t;
    if(b == R.b)
    {
        t.a = a + R.a;
        t.b = b;
    }
    else {
        t.b = b * R.b;
        t.a = a * R.b + R.a * b;
    }
    return t;
}

bool Trational::operator<(Trational R)
{
    Trational t;
    if(b == R.b)
    {
        t.a = a - R.a;
        t.b = b;
    }
    else {
        t.b = b * R.b;
        t.a = a * R.b - R.a * b;
    }

    if(t.a < 0)
        return true;
    else {
        return false;
    }
}

bool Trational::operator<=(Trational R)
{
    Trational t;
    if(b == R.b)
    {
        t.a = a - R.a;
        t.b = b;
    }
    else {
        t.b = b * R.b;
        t.a = a * R.b - R.a * b;
    }

    if(t.a <= 0)
        return true;
    else {
        return false;
    }
}

bool Trational::operator==(Trational R)
{
   if((a == 0) && (R.a == 0))

       return true;

   if((a == R.a) && (b == R.b))
       return true;
   else {
       return false;
   }
}

Trational sqrt(Trational r)
{
    Trational t;
    double x, e = 0.001;
    x = sqrt(r.a);
    t.a = x;
    if(abs(x - t.a) > e)
        return 1;
    x = sqrt(r.b);
    t.b = x;
    if(abs(x - t.b) > e)
        return 2;
    return t;
}

int Trational::nod(int n, int m)
{
    int a = n, b = m;
    while (a != b)
        if (a > b)
            a = a - b;
        else
            b = b - a;
    return a;
}

Trational Trational::reduction()
{
    int max = 1;
    Trational t;
    int temp;
    if(a > 0)
    {
        max = nod(a, b);
        t.a = a / max;
        t.b = b / max;
    }
    else if(a == 0){
        t.a = 0;
        t.b = 1;
    }
    else {
        temp = -a;
        max = nod(temp, b);
        t.a = -temp / max;
        t.b = b / max;

    }
    return t;
}

ostream& operator<<(ostream& os, Trational c)
{
    Trational t;

    t = c.reduction();
    if(t.b == 1)
        os << t.a;
    else {
        os << "(" << t.a << "/" << t.b << ")";
    }
    return os;
}

istream& operator>>(istream& is, Trational& c)
{
    is >> c.a >> c.b;
    return is;
}

QString& operator<<(QString& s, Trational& c) {

    Trational t;

    t = c.reduction();
    if(t.b == 1)
        s += QString().setNum(t.a);
    else {
        s += "(";
        s += QString().setNum(t.a);
        s += "/";
        s += QString().setNum(t.b);
        s += ")";
    }
    return s;
}

Trational::Trational(const QByteArray& arr)
{
    int p = arr.indexOf(SEPARATOR);
    a = arr.left(p).toDouble();
    b = arr.right(arr.length() - p - 1).toDouble();
}

Trational::operator QString ()
{
    QString s = "(";
    s += QString().setNum(a);
    s += "/";
    s += QString().setNum(b);
    s += ")";
    return s;
}

QByteArray& operator>>(QByteArray& arr, Trational& c)
{
    int p = arr.indexOf(Trational::SEPARATOR);
    p = arr.indexOf(Trational::SEPARATOR, p + 1);
    if (p > 0)
    {
        c = Trational(arr.left(p));
        arr = arr.right(arr.length() - p - 1);
    }
    return arr;
}

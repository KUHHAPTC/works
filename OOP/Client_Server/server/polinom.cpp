#include "polinom.h"

TPolinom::TPolinom(number x, number y, number z)
{
    printMode = EPrintModeClassic;
    a = x;
    b = y;
    c = z;
}


ostream& operator<< (ostream& os, TPolinom p)
{
    if(p.printMode == EPrintModeClassic)
    {
        number b, c;
        b = p.b;
        c = p.c;
        char sign1 = '+', sign2 = '+';
        if (p.b <= 0)
        {
            b = p.b * (-1);
            sign1 = '-';
        }
        if(p.c <= 0)
        {
            c = p.c * (-1);
            sign2 = '-';

        }
        os << p.a << "x^2 " << sign1 << " " << b << "x " << sign2 << " " << c;
    }
    else
    {
        number val[2] = {0};
        char sign1 = '-', sign2 = '-';
        p.findValue(val);
        if (val[0] <= 0)
        {
            val[0] = val[0] * (-1);
            sign1 = '+';
        }
        if (val[1] <= 0)
        {
            val[1] = val[1] * (-1);
            sign2 = '+';
        }

        os << p.a << " * " <<  "(x " << sign1 << " " << val[0] << ") * (x " << sign2 << " " << val[1] << ")";
    }
    return os;
}

number TPolinom::value(number x)
{
    return a * x * x + b * x + c;
}



void TPolinom::setPrintMode(EPrintMode m)
{
    printMode = m;
}


int TPolinom::findValue(number *val)
{
    number d;
    d = b * b -  a * 4 * c;
    if(d == 0) {
        val[0] = - (b) / (a * 2);
        val[1] = val[0];
        return 2;
    }
    else if(d < 0) {
        val[0] = 0;
        val[1] = 0;
        return 0;
    }
    else {
        val[0] = (- (b) + sqrt(d)) / (a * 2);
        val[1] = (- (b) - sqrt(d)) / (a * 2);
        return 2;
    }

}

QString TPolinom::printValue(number *val)
{
    QString s;
    s += "x1 = ";
    s << val[0];
    s += "  x2 = ";
    s << val[1];
    return s;
}

QString& operator << (QString& s, TPolinom p)
{
    if(p.printMode == EPrintModeClassic)
    {
        number b, c;
        b = p.b;
        c = p.c;
        char sign1 = '+', sign2 = '+';
        if (p.b <= 0)
        {
            b = p.b * (-1);
            sign1 = '-';
        }
        if(p.c <= 0)
        {
            c = p.c * (-1);
            sign2 = '-';

        }
        s << p.a;
        s += "x^2 ";
        s += sign1;
        s += " ";
        s << b;
        s += "x ";
        s += sign2;
        s += " ";
        s << c;
    }
    else
    {
        number val[2] = {0};
        char sign1 = '-', sign2 = '-';
        p.findValue(val);
        if (val[0] <= 0)
        {
            val[0] = val[0] * (-1);
            sign1 = '+';
        }
        if (val[1] <= 0)
        {
            val[1] = val[1] * (-1);
            sign2 = '+';
        }

        s << p.a;
        s += " * (x ";
        s += sign1;
        s += " ";
        s << val[0];
        s += ") * (x ";
        s += sign2;
        s += " ";
        s << val[1];
        s += ")";
    }
    return s;
}

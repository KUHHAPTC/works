#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <QString>

using namespace std;

class Trational
{
    int a, b;
    int nod(int, int);
    Trational reduction();
    static QChar SEPARATOR;

public:
    Trational();
    Trational(const int&);
    Trational(const int&, const int&);
    Trational(const QByteArray&);


    Trational operator* (Trational);
    Trational operator/ (Trational);
    Trational operator+ (Trational);
    Trational operator- (Trational);
    Trational operator- ();
    bool operator< (Trational);
    bool operator<= (Trational);
    bool operator== (Trational);
    friend Trational sqrt(Trational);
    friend ostream& operator<<(ostream&, Trational);
    friend istream& operator>>(istream&, Trational&);
    friend QString& operator<<(QString&, Trational&);
    friend QByteArray& operator>>(QByteArray&, Trational&);
    operator QString ();
};

#endif // RATIONAL_H

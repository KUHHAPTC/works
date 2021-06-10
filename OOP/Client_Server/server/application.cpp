#include "application.h"
#include "polinom.h"
#include "rational.h"
#include "common.h"

QByteArray& operator>>(QByteArray& arr, int& c)
{
    int p = arr.indexOf(separator);
    if (p > 0)
    {
        c = atoi(arr.left(p));
        arr = arr.right(arr.length() - p - 1);
    }
    return arr;
}

QString& operator<<(QString& s, int c)
{
    s += QString().setNum(c);
    return s;
}

TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
}

void TApplication::recieve(QByteArray msg)
{
    QString answer, s;
    int pos = msg.indexOf(separator);
    int t, mode = msg.left(pos).toInt();
    msg = msg.right(msg.length() - pos - 1);
    if (mode == R_MODE)
    {
        Trational a, b, c, x, v;
        msg >> a >> b >> c;
        TPolinom<Trational> p(a, b, c);
        Trational val[2];
        Trational v1, v2;
        int n = 0;
        pos = msg.indexOf(separator);
        t = msg.left(pos).toInt();
        switch (t)
        {
            case VALUE_REQUEST:
                msg = msg.right(msg.length() - pos - 1);
                msg >> x;
                v = p.value(x);
                s << (QString)x << (QString)v;
                answer << QString().setNum(VALUE_ANSWER);
                answer += s;
                break;
            case PRINT_CLASSIC_REQUEST:
                p.setPrintMode(EPrintModeClassic);
                s << p;
                answer << QString().setNum(PRINT_ANSWER) << s;
                break;
            case ROOTS_REQUEST:
                n = p.findValue(val);

                v1 = p.value(val[0]);
                v2 = p.value(val[1]);

                if((n == 2) && (v1 == 0) && (v2 == 0))
                {
                    s << (QString)p.printValue(val);
                    answer << QString().setNum(ROOTS_ANSWER);
                    answer += s;
                }
                else {
                    answer << QString().setNum(ROOTS_ANSWER);
                    answer << "These coefficients cannot be decomposed over a given field, enter another! " << "z";
                }
                break;
            case PRINT_CANONIC_REQUEST:

                p.setPrintMode(EPrintModeCanonic);
                n = p.findValue(val);
                v1 = p.value(val[0]);
                v2 = p.value(val[1]);
                if((n == 2) && (v1 == 0) && (v2 == 0))
                {
                    s << p;
                    answer << QString().setNum(PRINT_ANSWER) << s;
                }
                else {
                    answer << QString().setNum(PRINT_ANSWER);
                    answer << "These coefficients cannot be decomposed over a given field, enter another! " << "z";
                }
                break;

            default: return;
        }
    }
    if (mode == I_MODE)
    {
        int a, b, c, x, v;
        msg >> a >> b >> c;
        TPolinom<int> p(a, b, c);
        int val[2];
        int v1, v2;
        int n = 0;
        pos = msg.indexOf(separator);
        t = msg.left(pos).toInt();
        switch (t)
        {
            case VALUE_REQUEST:
                msg = msg.right(msg.length() - pos - 1);
                msg >> x;
                v = p.value(x);
                s << ("(" + QString().setNum(x) + ")") << QString().setNum(v);
                answer << QString().setNum(VALUE_ANSWER);
                answer += s;
                break;
            case PRINT_CLASSIC_REQUEST:
                p.setPrintMode(EPrintModeClassic);
                s << p;
                answer << QString().setNum(PRINT_ANSWER) << s;
                break;
            case ROOTS_REQUEST:
                n = p.findValue(val);

                v1 = p.value(val[0]);
                v2 = p.value(val[1]);

                if((n == 2) && (v1 == 0) && (v2 == 0))
                {
                    s << (QString)p.printValue(val);
                    answer << QString().setNum(ROOTS_ANSWER);
                    answer += s;
                }
                else {
                    answer << QString().setNum(ROOTS_ANSWER);
                    answer << "These coefficients cannot be decomposed over a given field, enter another! " << "z";
                }
                break;
            case PRINT_CANONIC_REQUEST:

                p.setPrintMode(EPrintModeCanonic);
                n = p.findValue(val);
                v1 = p.value(val[0]);
                v2 = p.value(val[1]);
                if((n == 2) && (v1 == 0) && (v2 == 0))
                {
                    s << p;
                    answer << QString().setNum(PRINT_ANSWER) << s;
                }
                else {
                    answer << QString().setNum(PRINT_ANSWER);
                    answer << "These coefficients cannot be decomposed over a given field, enter another! " << "z";
                }
                break;

            default: return;
        }
    }
    comm->send(QByteArray().append(answer));
}

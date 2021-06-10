#include <QApplication>
#include "canvas.h"
#include "sample.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TSample s;
    TCanvas w(&s);
    w.show();

    return a.exec();
}

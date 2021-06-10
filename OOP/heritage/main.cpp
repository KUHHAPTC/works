#include <QApplication>
#include "application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TApplication w;
    w.show();

    return a.exec();
}

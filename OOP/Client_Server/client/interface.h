#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

class TInterface : public QWidget
{
    Q_OBJECT

    QLabel *name_a, *delimeter_a;
    QLineEdit *a_top, *a_bot;
    QLabel *name_b, *delimeter_b;
    QLineEdit *b_top, *b_bot;
    QLabel *name_c, *delimeter_c;
    QLineEdit *c_top, *c_bot;
    QLabel *name_x, *delimeter_x;
    QLineEdit *x_top, *x_bot;

    QPushButton *value_btn;
    QPushButton *root_btn;
    QPushButton *print_classic_btn;
    QPushButton *print_canonic_btn;

    QRadioButton *i_mode;
    QRadioButton *r_mode;

    QLabel *output;
    QLabel *outputmess;

//    friend QString& operator<< (QString&,const QString&);

public:
    TInterface(QWidget *parent = 0);
    ~TInterface();

public slots:
    void answer(QString);

private slots:
    void formRequest();

signals:
    void request(QString);

};


#endif // INTERFACE_H

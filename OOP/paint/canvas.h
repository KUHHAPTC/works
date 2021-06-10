#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include "derivesample.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>

class TCanvas : public QWidget
{
    Q_OBJECT

    QLabel *amount;
    QLineEdit *number;

    QPushButton *number_btn;

    TDeriveSample* s;
public:
    TCanvas(TDeriveSample*, QWidget *parent = 0);
    ~TCanvas();

public slots:
    void nodes();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
};

#endif // VIEWER_H

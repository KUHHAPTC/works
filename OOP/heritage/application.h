#ifndef TAPPLICATION_H
#define TAPPLICATION_H

#include <QWidget>
#include <QLabel>
#include <qcombobox.h>
#include <QPushButton>
#include <QLineEdit>
#include "geometricshape.h"

enum type {Triangle = 1, Isoscele, Equilate, Ellipse, Circle, Quadrangle, Parallelogram, Rectangle, Rhombus, Square};

class TApplication : public QWidget
{
    Q_OBJECT
    type figure;
    QLabel *amount;
    QComboBox *combo;
    QPushButton *choice_btn;
    QLabel *area_inf, *per_inf, *area_txt, *per_txt;
    QLabel *side1, *side2, *side3, *side4, *side5;
    QLineEdit *side1_btn, *side2_btn, *side3_btn, *side4_btn, *side5_btn;
    QPushButton *clear_btn;
    QPushButton *get_btn;
public:
    TApplication(QWidget *parent = 0);
    ~TApplication();

public slots:
    void choice();
    void clear();
    void get();

};

#endif // TAPPLICATION_H

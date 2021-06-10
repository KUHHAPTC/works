#include "canvas.h"

TCanvas::TCanvas(TDeriveSample* f, QWidget *parent)
    : QWidget(parent)
{
    s = f;
    setFixedSize(500, 600);

    amount = new QLabel("Количество вершин: ", this);
    amount->setGeometry(120, 40, 130, 25);
    number = new QLineEdit("4", this);
    number->setGeometry(250, 40, 40, 25);

    number_btn = new QPushButton("Ввести", this);
    number_btn->setGeometry(300, 40, 60, 25);

    connect(number_btn, SIGNAL(pressed()), this, SLOT(nodes()));
}

TCanvas::~TCanvas()
{
    delete amount;
    delete number;
    delete number_btn;
}

void TCanvas::paintEvent(QPaintEvent*)
{
    QPainter p;
    int k = number->text().toInt();
    p.begin(this);
    s->draw(&p, rect(), Qt::gray, k);
    p.end();
}

void TCanvas::nodes(){
    repaint();
}

void TCanvas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)  s->newEvent(false);
    if (event->button() == Qt::RightButton) s->newEvent(true);
    update();
}

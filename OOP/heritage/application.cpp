#include "application.h"
#include "equilateraltriangle.h"
#include "circle.h"
#include "square.h"
#include <math.h>

#define PI (M_PI / 180)

TApplication::TApplication(QWidget *parent) : QWidget(parent)
{
    setFixedSize(380, 200);

    side1 = new QLabel("a = ", this);
    side2 = new QLabel("b = ", this);
    side3 = new QLabel("c = ", this);
    side4 = new QLabel("angle(ab) = ", this);
    side5 = new QLabel("angle(dc) = ", this);
    side1_btn = new QLineEdit("3", this);
    side2_btn = new QLineEdit("4", this);
    side3_btn = new QLineEdit("5", this);
    side4_btn = new QLineEdit("60", this);
    side5_btn = new QLineEdit("30", this);

    area_inf = new QLabel("", this);
    per_inf = new QLabel("", this);
    area_txt = new QLabel("Площадь: ", this);
    per_txt = new QLabel("Периметр: ", this);

    side1->setGeometry(10, 10, 0, 0);
    side2->setGeometry(10, 10, 0, 0);
    side3->setGeometry(10, 10, 0, 0);
    side4->setGeometry(10, 10, 0, 0);
    side5->setGeometry(10, 10, 0, 0);
    side1_btn->setGeometry(10, 10, 0, 0);
    side2_btn->setGeometry(10, 10, 0, 0);
    side3_btn->setGeometry(10, 10, 0, 0);
    side4_btn->setGeometry(10, 10, 0, 0);
    side5_btn->setGeometry(10, 10, 0, 0);
    area_inf->setGeometry(10, 10, 0, 0);
    area_txt->setGeometry(10, 10, 0, 0);
    per_inf->setGeometry(10, 10, 0, 0);
    per_txt->setGeometry(10, 10, 0, 0);

    clear_btn = new QPushButton("Очистить", this);
    clear_btn->setGeometry(10, 10, 0, 0);

    get_btn = new QPushButton("Вычислить", this);
    get_btn->setGeometry(10, 10, 0, 0);

    amount = new QLabel("Выберите фигуру: ", this);
    amount->setGeometry(30, 130, 120, 25);

    combo = new QComboBox(this);
    combo->setGeometry(150, 130, 210, 25);
    QStringList items = {"Треугольник", "Равнобедренный треугольник", "Равносторонний треугольник", "Окружность", "Эллипс",
                         "Четырёхугольник", "Параллелограмм", "Ромб", "Прямоугольник", "Квадрат"};
    combo->addItems(items);

    choice_btn = new QPushButton("Выбрать", this);
    choice_btn->setGeometry(45, 160, 75, 25);


    connect(choice_btn, SIGNAL(pressed()), this, SLOT(choice()));
    connect(clear_btn, SIGNAL(pressed()), this, SLOT(clear()));
    connect(get_btn, SIGNAL(pressed()), this, SLOT(get()));
}

TApplication::~TApplication()
{
    delete amount;
    delete combo;
    delete choice_btn;
    delete side1;
    delete side2;
    delete side3;
    delete side4;
    delete side5;
    delete side1_btn;
    delete side2_btn;
    delete side3_btn;
    delete side4_btn;
    delete side5_btn;
    delete clear_btn;
    delete get_btn;
    delete area_inf;
    delete per_inf;
    delete per_txt;
    delete area_txt;
}

void TApplication::choice()
{
    side1->setText("a = ");
    side2->setText("b = ");
    side3->setText("c = ");
    side5->setText("angle(ab) = ");
    side1->setGeometry(20, 20, 0, 0);
    side2->setGeometry(20, 50, 0, 0);
    side3->setGeometry(20, 80, 0, 0);
    side4->setGeometry(20, 80, 0, 0);
    side5->setGeometry(20, 80, 0, 0);
    side1_btn->setGeometry(50, 20, 0, 0);
    side2_btn->setGeometry(50, 50, 0, 0);
    side3_btn->setGeometry(50, 80, 0, 0);
    side4_btn->setGeometry(50, 110, 0, 0);
    side5_btn->setGeometry(20, 80, 0, 0);
    area_inf->setGeometry(10, 10, 0, 0);
    per_inf->setGeometry(10, 10, 0, 0);
    area_txt->setGeometry(10, 10, 0, 0);
    per_txt->setGeometry(10, 10, 0, 0);
    clear_btn->setGeometry(150, 15, 210, 20);
    get_btn->setGeometry(150, 45, 210, 20);
    QString now = combo->currentText();
    if(now == "Треугольник"){
        figure = Triangle;
        side5->setText("angle = ");
        side1->setGeometry(40, 20, 20, 20);
        side2->setGeometry(40, 50, 20, 20);
        side5->setGeometry(15, 80, 50, 20);
        side1_btn->setGeometry(65, 20, 40, 20);
        side2_btn->setGeometry(65, 50, 40, 20);
        side5_btn->setGeometry(65, 80, 40, 20);
    }
    else if(now == "Равнобедренный треугольник"){
        figure = Isoscele;
        side2->setText("c = ");
        side1->setGeometry(20, 20, 20, 20);
        side2->setGeometry(20, 50, 20, 20);
        side1_btn->setGeometry(50, 20, 40, 20);
        side2_btn->setGeometry(50, 50, 40, 20);
    }
    else if(now == "Равносторонний треугольник"){
        figure = Equilate;
        side1->setGeometry(20, 20, 20, 20);
        side1_btn->setGeometry(50, 20, 40, 20);
    }
    else if(now == "Квадрат"){
        figure = Square;
        side1->setGeometry(20, 20, 20, 20);
        side1_btn->setGeometry(50, 20, 40, 20);
    }
    else if(now == "Ромб"){
        figure = Rhombus;
        side5->setText("angle = ");
        side1->setGeometry(40, 20, 20, 20);
        side5->setGeometry(15, 50, 50, 20);
        side1_btn->setGeometry(65, 20, 40, 20);
        side5_btn->setGeometry(65, 50, 40, 20);
    }
    else if(now == "Прямоугольник"){
        figure = Rectangle;
        side2->setGeometry(20, 50, 20, 20);
        side2_btn->setGeometry(50, 50, 40, 20);
        side1->setGeometry(20, 20, 20, 20);
        side1_btn->setGeometry(50, 20, 40, 20);
    }
    else if(now == "Параллелограмм"){
        figure = Parallelogram;
        side5->setText("angle = ");
        side1->setGeometry(40, 20, 20, 20);
        side2->setGeometry(40, 50, 20, 20);
        side5->setGeometry(15, 80, 50, 20);
        side1_btn->setGeometry(65, 20, 40, 20);
        side2_btn->setGeometry(65, 50, 40, 20);
        side5_btn->setGeometry(65, 80, 40, 20);
    }
    else if(now == "Четырёхугольник"){
        figure = Quadrangle;
        side5->setText("angle(dc) = ");
        side1->setGeometry(55, 10, 20, 20);
        side1_btn->setGeometry(80, 10, 40, 20);
        side2->setGeometry(55, 35, 20, 20);
        side2_btn->setGeometry(80, 35, 40, 20);
        side3->setGeometry(55, 60, 20, 20);
        side3_btn->setGeometry(80, 60, 40, 20);
        side4->setGeometry(7, 85, 70, 20);
        side4_btn->setGeometry(80, 85, 40, 20);
        side5->setGeometry(7, 110, 70, 20);
        side5_btn->setGeometry(80, 110, 40, 20);
    }
    else if(now == "Эллипс"){
        figure = Ellipse;
        side1->setGeometry(20, 15, 20, 20);
        side1_btn->setGeometry(50, 15, 40, 20);
        side2->setGeometry(20, 45, 20, 20);
        side2_btn->setGeometry(50, 45, 40, 20);
    }
    else if(now == "Окружность"){
        figure = Circle;
        side1->setText("r = ");
        side1->setGeometry(20, 15, 20, 20);
        side1_btn->setGeometry(50, 15, 40, 20);
    }
    else{
        clear();
    }
}

void TApplication::clear()
{
    side1->setGeometry(10, 10, 0, 0);
    side2->setGeometry(10, 10, 0, 0);
    side3->setGeometry(10, 10, 0, 0);
    side4->setGeometry(10, 10, 0, 0);
    side5->setGeometry(10, 10, 0, 0);
    side1_btn->setGeometry(10, 10, 0, 0);
    side2_btn->setGeometry(10, 10, 0, 0);
    side3_btn->setGeometry(10, 10, 0, 0);
    side4_btn->setGeometry(10, 10, 0, 0);
    side5_btn->setGeometry(10, 10, 0, 0);
    clear_btn->setGeometry(10, 10, 0, 0);
    get_btn->setGeometry(10, 10, 0, 0);
    area_inf->setGeometry(10, 10, 0, 0);
    per_inf->setGeometry(10, 10, 0, 0);
    area_txt->setGeometry(10, 10, 0, 0);
    per_txt->setGeometry(10, 10, 0, 0);
}

void TApplication::get()
{
    double area = 0;
    double perimeter = 0;
    switch(figure){

    case Triangle:
    {
        TTriangle q(side1_btn->text().toInt(), side2_btn->text().toInt(), side5_btn->text().toInt() * PI);
        area = q.findArea();
        perimeter = q.findPerimeter();
        break;
    }

    case Isoscele:
    {
        TIsoscelesTriangle q(side1_btn->text().toInt(), side2_btn->text().toInt());
        area = q.findArea();
        perimeter = q.findPerimeter();
        break;
    }

    case Equilate:
    {
        TEquilateralTriangle q(side1_btn->text().toInt());
        area = q.findArea();
        perimeter = q.findPerimeter();
        break;
    }

    case Ellipse:
    {
        TEllipse q(side1_btn->text().toInt(), side2_btn->text().toInt());
        area = q.findArea();
        perimeter = q.findPerimeter();
        break;
    }

    case Circle:
    {
        TCircle q(side1_btn->text().toInt());
        area = q.findArea();
        perimeter = q.findPerimeter();
        break;
    }

    case Square:
    {
        TSquare q(side1_btn->text().toInt());
        area = q.findArea();
        perimeter = q.findPerimeter();
        break;
    }

    case Rhombus:
    {
        TRhombus q(side1_btn->text().toInt(), side5_btn->text().toInt());
        area = q.findArea();
        perimeter = q.findPerimeter();
        break;
    }

    case Rectangle:
    {
        TRectangle q(side1_btn->text().toInt(), side2_btn->text().toInt());
        area = q.findArea();
        perimeter = q.findPerimeter();
        break;
    }

    case Parallelogram:
    {
        TParallelogram q(side1_btn->text().toInt(), side2_btn->text().toInt(), side5_btn->text().toInt());
        area = q.findArea();
        perimeter = q.findPerimeter();
        break;
    }

    case Quadrangle:
    {
        TQuadrangle q(side1_btn->text().toInt(), side2_btn->text().toInt(), side3_btn->text().toInt(), side4_btn->text().toInt(), side5_btn->text().toInt());
        area = q.findArea();
        perimeter = q.findPerimeter();
        break;
    }
    }

    QString a = QString::number(area, 'f', 4);
    QString p = QString::number(perimeter, 'f', 4);
    area_inf->setText(a);
    per_inf->setText(p);
    area_txt->setGeometry(150, 75, 60, 20);
    per_txt->setGeometry(150, 100, 60, 20);
    area_inf->setGeometry(215, 75, 60, 20);
    per_inf->setGeometry(215, 100, 60, 20);
    qDebug() << "";
}



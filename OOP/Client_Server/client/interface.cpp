#include "interface.h"
#include "common.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{

    setWindowTitle("Работа №5");
    setFixedSize(500, 290);

    name_a = new QLabel("a = ", this);
    name_a->setGeometry(165, 20, 30, 25);
    a_top = new QLineEdit("1", this);
    a_top->setGeometry(205, 20, 50, 25);
    delimeter_a = new QLabel("/", this);
    delimeter_a->setGeometry(265, 20, 30, 25);
    a_bot = new QLineEdit("1", this);
    a_bot->setGeometry(280, 20, 50, 25);

    name_b = new QLabel("b = ", this);
    name_b->setGeometry(165, 50, 30, 25);
    b_top = new QLineEdit("2", this);
    b_top->setGeometry(205, 50, 50, 25);
    delimeter_b = new QLabel("/", this);
    delimeter_b->setGeometry(275, 50, 30, 25);
    b_bot = new QLineEdit("1", this);
    b_bot->setGeometry(280, 50, 50, 25);

    name_c = new QLabel("c = ", this);
    name_c->setGeometry(165, 80, 30, 25);
    c_top = new QLineEdit("1", this);
    c_top->setGeometry(205, 80, 50, 25);
    delimeter_c = new QLabel("/", this);
    delimeter_c->setGeometry(265, 80, 30, 25);
    c_bot = new QLineEdit("1", this);
    c_bot->setGeometry(280, 80, 50, 25);

    name_x = new QLabel("x = ", this);
    name_x->setGeometry(165, 110, 30, 25);
    x_top = new QLineEdit("1", this);
    x_top->setGeometry(205, 110, 50, 25);
    delimeter_x = new QLabel("/", this);
    delimeter_x->setGeometry(265, 110, 30, 25);
    x_bot = new QLineEdit("1", this);
    x_bot->setGeometry(280, 110, 50, 25);


    value_btn = new QPushButton("value", this);
    value_btn->setGeometry(115, 150, 65, 30);
    root_btn = new QPushButton("root", this);
    root_btn->setGeometry(185, 150, 65, 30);
    print_classic_btn = new QPushButton("classic", this);
    print_classic_btn->setGeometry(270, 150, 65, 30);
    print_canonic_btn = new QPushButton("canonic", this);
    print_canonic_btn->setGeometry(340, 150, 65, 30);

    i_mode = new QRadioButton("integer", this);
    i_mode->setGeometry(130, 200, 480, 25);
    r_mode = new QRadioButton("rational", this);
    r_mode->setGeometry(300, 200, 480, 25);
    i_mode->setCheckable(true);

    outputmess = new QLabel(this);
    outputmess->setGeometry(30, 240, 480, 25);

    output = new QLabel(this);
    output->setGeometry(190, 240, 300, 25);


    connect(value_btn, SIGNAL(pressed()), this, SLOT(formRequest())); // SLOT(value1())
    connect(root_btn, SIGNAL(pressed()), this, SLOT(formRequest())); // SLOT(root())
    connect(print_classic_btn, SIGNAL(pressed()), this, SLOT(formRequest())); // SLOT(print_classic())
    connect(print_canonic_btn, SIGNAL(pressed()), this, SLOT(formRequest())); // SLOT(print_canonic())
}

TInterface::~TInterface()
{
    delete name_a;
    delete delimeter_a;
    delete a_top;
    delete a_bot;

    delete name_b;
    delete delimeter_b;
    delete b_top;
    delete b_bot;

    delete name_c;
    delete delimeter_c;
    delete c_top;
    delete c_bot;

    delete name_x;
    delete delimeter_x;
    delete x_top;
    delete x_bot;

    delete value_btn;
    delete root_btn;
    delete print_canonic_btn;
    delete print_classic_btn;

    delete i_mode;
    delete r_mode;

    delete outputmess;
    delete output;
}

void TInterface::formRequest()
{
    QString msg;
    if(i_mode->isChecked())
    {
        msg << QString().setNum(I_MODE);
        msg << a_top->text();
        msg << b_top->text();
        msg << c_top->text();
    }
    else
    {
        msg << QString().setNum(R_MODE);
        msg << a_top->text() << a_bot->text();
        msg << b_top->text() << b_bot->text();
        msg << c_top->text() << c_bot->text();
    }
    QPushButton *btn = (QPushButton*)sender();
    if (btn == value_btn)
    {
        msg << QString().setNum(VALUE_REQUEST);
        if(i_mode->isChecked())
            msg << x_top->text();
        else
            msg << x_top->text() << x_bot->text();
    }
    if (btn == print_classic_btn)
        msg << QString().setNum(PRINT_CLASSIC_REQUEST);
    if (btn == root_btn)
        msg << QString().setNum(ROOTS_REQUEST);
    if (btn == print_canonic_btn)
        msg << QString().setNum(PRINT_CANONIC_REQUEST);
    emit request(msg);
}

void TInterface::answer(QString msg)
{
    QString text;
    int p = msg.indexOf(separator);
    int t = msg.left(p).toInt();
    msg = msg.mid(p + 1, msg.length() - p - 2);
    switch (t)
    {
        case VALUE_ANSWER:
            text = "p";
            p = msg.indexOf(separator);
            text += msg.left(p);
            text += " = ";
            text += msg.right(msg.length() - p - 1);
            outputmess->setText("");
            output->setText(text);
            break;
        case PRINT_ANSWER:

            if (msg.right(p) == "z") {
                p = msg.indexOf(separator);
                text += msg.left(p);
                output->setText("");
                outputmess->setText(text);
            }
            else {
                text = "p(x) = ";
                text += msg;
                outputmess->setText("");
                output->setText(text);
            }
            break;
        case ROOTS_ANSWER:
            p = msg.indexOf(separator);
            text += msg.left(p);
            if (msg.right(msg.length() - p - 1) == "z") {
                output->setText("");
                outputmess->setText(text);
            }
            else {
                outputmess->setText("");
                output->setText(text);
            }
        default: break;
    }
}

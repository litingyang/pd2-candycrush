#include "c.h"

C::C(QWidget *parent, int Col, int Row) : A(parent,Col,Row)
{
    button->setIcon(QIcon(QPixmap(":/box2_1.png")));

}

C::~C()
{

}

void C::click(){

    button->setIcon(QIcon(QPixmap(":/box2_1.png")));
    emit Click(row,col,num);
}

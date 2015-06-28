#include "b.h"

B::B(QWidget *parent, int Col, int Row) : A(parent,Col,Row)
{
    button->setIcon(QIcon(QPixmap(":/box1_1.png")));

}

B::~B()
{

}

void B::click(){
    button->setIcon(QIcon(QPixmap(":/box1_1.png")));
    emit Click(row,col,num);


}

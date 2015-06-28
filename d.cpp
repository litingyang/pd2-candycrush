#include "d.h"

D::D(QWidget *parent, int Col, int Row) : A(parent,Col,Row)
{
    button->setIcon(QIcon(QPixmap(":/box3_1.png")));

}

D::~D()
{

}

void D::click(){

    button->setIcon(QIcon(QPixmap(":/box3_1.png")));
    emit Click(row,col,num);
}

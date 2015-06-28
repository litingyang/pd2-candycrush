#include "e.h"

E::E(QWidget *parent, int Col, int Row) : A(parent,Col,Row)
{
    button->setIcon(QIcon(QPixmap(":/box4_1.png")));

}

E::~E()
{

}

void E::click(){
    button->setIcon(QIcon(QPixmap(":/box4_1.png")));
    emit Click(row,col,num);


}

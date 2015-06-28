#include "f.h"

F::F(QWidget *parent, int Col, int Row) : A(parent,Col,Row)
{
    button->setIcon(QIcon(QPixmap(":/box5_1.png")));

}

F::~F()
{

}

void F::click(){
    button->setIcon(QIcon(QPixmap(":/box5_1.png")));
    emit Click(row,col,num);


}

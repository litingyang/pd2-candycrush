#include "a.h"

A::A(QWidget *parent, int Row, int Col,int Num) : QWidget(parent)
{
    row=Row;
    col=Col;
    num=Num;
    button=new QPushButton(parent);
    button->setGeometry(50*row+20,50*col+30,49,49);
    button->setIcon(QIcon(QPixmap(":/box1/box1_1.png")));
    button->setIconSize(QSize(49,49));
    button->setFlat(true);
    button->setStyleSheet("border:1px solid;");
    button->setIconSize(button->size());
    button->setText(QString::number(num));
    clicked=false;
    connect(button,SIGNAL(clicked()),this,SLOT(click()));
}

A::~A()
{

}





void A::click(){
    //button->setIcon(QIcon(QPixmap(":/box1_1.png")));
    emit Click(row,col,num);


}


















bool A::operator ==(A &a) const{

    if(a.num==this->num){
        return true;

    }



}




void A::operator =(int a) {

    this->num=a;


}

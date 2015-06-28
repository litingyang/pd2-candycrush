#ifndef A_H
#define A_H

#include <QWidget>
#include <QPushButton>
class A : public QWidget
{
    Q_OBJECT
public:
    friend class MainWindow;
    bool operator ==(A &)const;
    void operator =(int a);
    explicit A(QWidget *parent = 0, int Row=0, int Col=0 ,int Num=0);
    ~A();

signals:
    void Click(int row,int col,int num);

public slots:
    void click();

protected:
    int turn;
    QPushButton *button;
    int row,col,num;
    bool clicked;
};

#endif // A_H

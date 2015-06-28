#ifndef C_H
#define C_H

#include <QWidget>
#include<a.h>
class C : public A
{
    Q_OBJECT
public:
    explicit C(QWidget *parent = 0, int Col=0, int Row=0);
    ~C();

signals:

public slots:
    virtual void click();
};

#endif // C_H

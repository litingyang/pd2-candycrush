#ifndef B_H
#define B_H

#include <QWidget>
#include<a.h>
class B : public A
{
    Q_OBJECT
public:
    explicit B(QWidget *parent = 0, int Col=0, int Row=0);
    ~B();

signals:

public slots:
    virtual void click();
};

#endif // B_H

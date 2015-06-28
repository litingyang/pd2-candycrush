#ifndef E_H
#define E_H

#include <QWidget>
#include<a.h>
class E : public A
{
    Q_OBJECT
public:
    explicit E(QWidget *parent = 0, int Col=0, int Row=0);
    ~E();

signals:

public slots:
    virtual void click();
};

#endif // E_H

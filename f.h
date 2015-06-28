#ifndef F_H
#define F_H

#include <QWidget>
#include<a.h>
class F : public A
{
    Q_OBJECT
public:
    explicit F(QWidget *parent = 0, int Col=0, int Row=0);
    ~F();

signals:

public slots:
    virtual void click();
};

#endif // F_H

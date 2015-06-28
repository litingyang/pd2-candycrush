#ifndef D_H
#define D_H

#include <QWidget>
#include<a.h>
class D : public A
{
    Q_OBJECT
public:
    explicit D(QWidget *parent = 0, int Col=0, int Row=0);
    ~D();

signals:

public slots:
    virtual void click();
};

#endif // D_H

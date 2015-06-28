#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTextStream>
#include <QMainWindow>
#include<a.h>
#include<QVector>
#include<QTime>
#include<QTimer>
#include<QElapsedTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void quit(int star , int score);


private slots:
    void update_time();
    void BoxClick(int row, int col, int num );

    void on_pushButton_clicked();

private:
    bool check();
    void check2();
    Ui::MainWindow *ui;
    QPushButton *kj;
    QVector <int> data;
    QVector <int> data2;
    QVector <int>typ;
    QVector <int>typ2;
    bool rem[9][9];
    QVector<A *>box;
    A* rrrr;
    int turn;
    void move();
    void Create();
    void SetNum();
    void check_Fr();
    void check_Fv();
    void check_T();
    void SetPicture();
    void set_special();
    void set_five(int a,int b);
    void set_T();
    int tm;
    int Move;
    int star;
    int score;
    QElapsedTimer timer;
    QTimer *timer2;
    void step();
    void count_score();
    void clock();
    void create_clock();




};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int a;
    turn=1;
    Move=32;
    ui->label_4->setNum(Move);
    ui->result->hide();
    ui->pushButton_2->hide();
    star=0;
    score=0;
    //QTimer *timer2;
    tm=0;
    //QTimer::singleShot(1000, this, SLOT(update_time()));
    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(update_time()));
    timer2->start(1000);
    timer.start();
    QTextStream out(stdout);
    out << QString("It took");
    out << QString::number((timer.elapsed()/1000));
    out << QString("milliseconds");
    //timer = new QTimer(this);
    //timer->start(1000);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    box.resize(81);
    data.resize(81);
    data2.resize(81);
    typ.resize(81);
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            typ[9*i+j]=1;
            a=qrand()%6;
            //while(i>1)
            while(i>1&&data[9*(i-1)+j]==a&&data[9*(i-2)+j]==a)
            {a=qrand()%6;}
            //while(j>1)
            while(j>1&&data[9*i+j-1]==a&&data[9*i+j-2]==a)
            {a=qrand()%6;}
            data[9*i+j]=a;
            rem[i][j]=false;
            if(data[9*i+j]==0)box[9*i+j]=new A(this,i,j,data[9*i+j]);
            if(data[9*i+j]==1)box[9*i+j]=new A(this,i,j,data[9*i+j]);
            if(data[9*i+j]==2)box[9*i+j]=new A(this,i,j,data[9*i+j]);
            if(data[9*i+j]==3)box[9*i+j]=new A(this,i,j,data[9*i+j]);
            if(data[9*i+j]==4)box[9*i+j]=new A(this,i,j,data[9*i+j]);
            if(data[9*i+j]==5)box[9*i+j]=new A(this,i,j,data[9*i+j]);
            connect(box[9*i+j],SIGNAL(Click(int,int,int)),this,SLOT(BoxClick(int,int,int)));
            data2=data;

        }
    }
    //QTextStream out(stdout);
    out << QString("\nboll=\n");
    SetNum();
    out << QString::number((*box[0])==(*box[9]));
    SetPicture();

}

MainWindow::~MainWindow()
{
    delete ui;
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
        delete box[9*i+j];
        }
    }
    emit quit(star ,score);
}

void MainWindow::BoxClick(int row, int col, int num){
    if(Move>0){
    typ2=typ;
    int tmp;
    A *tmpa;
    turn=(turn+1)%2;
    rem[row][col]=true;
    if(turn==1){
        for(int i=0;i<9;++i){
            for(int j=0;j<9;++j){
            if(rem[i][j]==true&&(((abs(row-i)==1&&col==j))||(abs(col-j)==1&&row==i))){
               tmp=data.at(9*i+j);
               data[9*i+j]=data[9*row+col];
               data[9*row+col]=tmp;
               tmp=typ.at(9*i+j);
               typ[9*i+j]=typ[9*row+col];
               typ[9*row+col]=tmp;
               set_five(9*i+j,9*row+col);
               set_five(9*row+col,9*i+j);

               check2();
               Create();
               SetNum();
               SetPicture();
               QTextStream out(stdout);
//               out << QString::number(i);
               out << QString("\nSome check=\n");
               out << QString::number(check());
               if(check()==true){
                   box[9*row+col]->button->setText(QString::number(data[9*row+col]));
                   (*box[9*row+col])=data[9*row+col];
                   box[9*i+j]->button->setText(QString::number(data[9*i+j]));
                   (*box[9*i+j])=data[9*i+j];

                   while(check()==true){
                       check_Fv();
                       check_T();
                       check_Fr();
                       move();
                       set_T();
                       set_special();
                       clock();
                       check2();
                       Create();
                       SetNum();


                   }

                   //box[0]->button->setText(QString::number(10000));
        /*tmpa=box[9*row+col];
        box[9*row+col]=box[9*i+j];
        box[9*i+j]=tmpa;
        box[9*row+col]->button->setGeometry(50*row+20,50*col+30,49,49);
        box[9*row+col]->row=row;
        box[9*row+col]->col=col;
        box[9*i+j]->button->setGeometry(50*i+20,50*j+30,49,49);
        box[9*i+j]->row=i;
        box[9*i+j]->col=j;
*/
               }
               else{
                   for(int i=0;i<9;++i){
                       for(int j=0;j<9;++j){
                       data[9*i+j]=data2[9*i+j];
                       typ=typ2;
                       SetNum();
                       }
                   }

               }
            }
            }
            SetPicture();
        }

        for(int i=0;i<9;++i){
            for(int j=0;j<7;++j){
                if(data[9*i+j]==data[9*i+j+1]&&data[9*i+j]==data[i*9+j+2]){


                }
            }
        }

        for(int i=0;i<9;++i){
            for(int j=0;j<9;++j){
            rem[i][j]=false;
            }
        }

}
    if(data!=data2)
        step();

    data2=data;
    }

}


bool MainWindow::check(){

    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){

            if(data[9*(i)+j]==-5&&typ[9*(i)+j]==5){
  //              return true;

            }
        }
    }
    for(int i=0;i<9;++i){
        for(int j=0;j<7;++j){
            if(data[9*i+j]!=-1&&data[9*i+j]==data[9*i+j+1]&&data[9*i+j]==data[9*i+j+2]){

                QTextStream out(stdout);
                out << QString("\ntrue1 data\n");
                out << QString::number(9*i+j);
                out << QString("=");
                out << QString::number(data[9*i+j]);
                out << QString("\ntrue1 data\n");
                out << QString::number(9*i+j+1);
                out << QString("=");
                out << QString::number(data[9*i+j+1]);
                out << QString("\ntrue1 data\n");
                out << QString::number(9*i+j+2);
                out << QString("=");
                out << QString::number(data[9*i+j+2]);
                return true;
            }
        }
    }

    for(int j=0;j<9;++j){
        for(int i=0;i<7;++i){
            if((data[9*i+j]!=-1&&data[9*i+j]==data[9*(i+1)+j])&&(data[9*i+j]==data[9*(i+2)+j])){

                QTextStream out(stdout);
                out << QString("\ntrue2 data\n");
                out << QString::number(9*i+j);
                out << QString("=");
                out << QString::number(data[9*i+j]);
                out << QString("\ntrue2 data\n");
                out << QString::number(9*(i+1)+j);
                out << QString("=");
                out << QString::number(data[9*(i+1)+j]);
                out << QString("\ntrue2 data\n");
                out << QString::number(9*(i+2)+j);
                out << QString("=");
                out << QString::number(data[9*(i+2)+j]);
                return true;
            }
        }

    }
//    QTextStream out(stdout);
//    out << QString("\nfalse\n");

 return false;
}
void MainWindow::move(){
//    QTextStream out(stdout);
//    out << QString("\nmove\n");
    for(int i=0;i<9;++i){
        for(int j=0;j<7;++j){
            if(data[9*i+j]!=-1&&data[9*i+j]==data[9*i+j+1]&&data[9*i+j]==data[9*i+j+2]){
                QTextStream out(stdout);
                out << QString("\ndata!=\n");
                out << QString::number(data[9*i+j]);
                data[9*i+j]=-1;
                data[9*i+j+1]=-1;
                data[9*i+j+2]=-1;
                /*
                out << QString("\nmovelr data\t");
                out << QString::number(9*i+j);
                out << QString("=");
                out << QString::number(data[9*i+j]);
                out << QString("\nmove data\t");
                out << QString::number(9*i+j+1);
                out << QString("=");
                out << QString::number(data[9*i+j+1]);
                out << QString("\nmove data\t");
                out << QString::number(9*i+j+2);
                out << QString("=");
                out << QString::number(data[9*i+j+2]);

                */
            }
        }
    }
    for(int j=0;j<9;++j){
        for(int i=0;i<7;++i){
            if(data[9*i+j]!=-1&&data[9*i+j]==data[9*(i+1)+j]&&data[9*i+j]==data[9*(i+2)+j]){
                data[9*i+j]=-1;
                data[9*(i+1)+j]=-1;
                data[9*(i+2)+j]=-1;
                /*
                QTextStream out(stdout);
                out << QString("\nmove data\t");
                out << QString::number(9*i+j);
                out << QString("=");
                out << QString::number(data[9*i+j]);
                out << QString("\nmove data\t");
                out << QString::number(9*(i+1)+j);
                out << QString("=");
                out << QString::number(data[9*(i+1)+j]);
                out << QString("\nmove data\t");
                out << QString::number(9*(i+2)+j);
                out << QString("=");
                out << QString::number(data[9*(i+2)+j]);
                    */
}

        }

    }


}
void MainWindow::check2(){
    QTextStream out(stdout);
    out << QString("\ncheck2\n");
    int tmp;
    for(int i=0;i<9;++i){
        for(int j=7;j>=0;--j){
            if(data[9*(i)+j+1]==-1){
                data[9*(i)+j+1]=data[9*i+j];
                data[9*i+j]=-1;
                tmp=typ[9*i+j+1];
                typ[9*(i)+j+1]=typ[9*i+j];
                typ[9*i+j]=tmp;
                for(int k=j;k>=0;--k){
                    if((j-k+1)>=0){
                    if(data[9*(i)+j-k+1]==-1){
                        data[9*(i)+j-k+1]=data[9*(i)+j-k];
                        data[9*(i)+j-k]=-1;
                        tmp=typ[9*i+j-k+1];
                        typ[9*(i)+j-k+1]=typ[9*i+j-k];
                        typ[9*i+j-k]=tmp;

                    }


                    }


                }

            }


        }
    }


}
void MainWindow::Create(){
    QTextStream out(stdout);
    out << QString("\ncreate\n");
    int a,b;
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            if(data[9*i+j]==-1){
                count_score();
                a=qrand()%6;
                while(i>1&&data[9*(i-1)+j]==a&&data[9*(i-2)+j]==a)
                {a=qrand()%6;}
                while(j>1&&data[9*i+j-1]==a&&data[9*i+j-2]==a)
                {a=qrand()%6;}
                data[9*i+j]=a;
                typ[9*i+j]=1;
                b=qrand()%100;
                if(b==0)
                    typ[9*i+j]=6;

            }




        }
    }




}
void MainWindow::SetNum(){
    QTextStream out(stdout);
//    out << QString("\nsetnum\n");
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            box[9*i+j]->button->setText(QString::number(data[9*i+j]));
            (*box[9*i+j])=data[9*i+j];
            out << QString("\ndata=\n");
            out << QString::number(data[9*i+j]);
//            out << QString::number(box[9*i+j]->num);

        }
    }





}
void MainWindow::check_Fr(){
    for(int i=0;i<9;++i){
        for(int j=0;j<6;++j){
            if(data[9*i+j]!=-1&&data[9*i+j]==data[9*i+j+1]&&data[9*i+j]==data[9*i+j+2]&&data[9*i+j]==data[9*i+j+3]){
                QTextStream out(stdout);
                out << QString("\ndata!=\n");
                out << QString::number(data[9*i+j]);
                count_score();
                count_score();
                data[9*i+j]=-1;
                data[9*i+j+1]=-1;
                data[9*i+j+2]=-1;
//                data[9*i+j+3]=-3;
                typ[9*i+j+3]=3;

            }
        }
    }
    for(int j=0;j<9;++j){
        for(int i=0;i<6;++i){
            if(data[9*i+j]!=-1&&data[9*i+j]==data[9*(i+1)+j]&&data[9*i+j]==data[9*(i+2)+j]&&data[9*i+j]==data[9*(i+3)+j]){
                count_score();
                count_score();
                data[9*i+j]=-1;
                data[9*(i+1)+j]=-1;
//                data[9*(i+2)+j]=-2;
                data[9*(i+3)+j]=-1;
                typ[9*(i+2)+j]=2;
                QTextStream out(stdout);
                out << QString("\nsetfour data\n");
                out << QString::number(9*i+j);
                out << QString("=");
                out << QString::number(typ[9*(i+2)+j]);
            }
        }

    }






}
void MainWindow::SetPicture(){
//    QTextStream out(stdout);
//    out << QString("\nsetpicture\n");
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            if(data[9*i+j]==0){
                if(typ[9*i+j]==2)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box1_2.png")));
                else if(typ[9*i+j]==3)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box1_3.png")));
                else if(typ[9*i+j]==4)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box1_4.png")));
                else if(typ[9*i+j]==6)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box1_6.png")));
                else
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box1_1.png")));}
            if(data[9*i+j]==1){
                if(typ[9*i+j]==2)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box2_2.png")));
                else if(typ[9*i+j]==3)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box2_3.png")));
                else if(typ[9*i+j]==4)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box2_4.png")));
                else if(typ[9*i+j]==6)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box2_6.png")));
                else
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box2_1.png")));}
            if(data[9*i+j]==2){
                if(typ[9*i+j]==2)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box3_2.png")));
                else if(typ[9*i+j]==3)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box3_3.png")));
                else if(typ[9*i+j]==4)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box3_4.png")));
                else if(typ[9*i+j]==6)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box3_6.png")));
                else
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box3_1.png")));}
            if(data[9*i+j]==3){
                if(typ[9*i+j]==2)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box4_2.png")));
                else if(typ[9*i+j]==3)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box4_3.png")));
                else if(typ[9*i+j]==4)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box4_4.png")));
                else if(typ[9*i+j]==6)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box4_6.png")));
                else
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box4_1.png")));}
            if(data[9*i+j]==4){
                if(typ[9*i+j]==2)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box5_2.png")));
                else if(typ[9*i+j]==3)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box5_3.png")));
                else if(typ[9*i+j]==4)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box5_4.png")));
                else if(typ[9*i+j]==6)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box5_6.png")));
                else
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box5_1.png")));}
            if(data[9*i+j]==5){
                if(typ[9*i+j]==2)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box6_2.png")));
                else if(typ[9*i+j]==3)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box6_3.png")));
                else if(typ[9*i+j]==4)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box6_4.png")));
                else if(typ[9*i+j]==6)
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box6_6.png")));
                else
                    box[9*i+j]->button->setIcon(QIcon(QPixmap(":/box6_1.png")));}


        if(data[9*(i)+j]==-5&&typ[9*(i)+j]==5){
            box[9*i+j]->button->setIcon(QIcon(QPixmap(":/Box_a.png")));
    }


}



}
}

void MainWindow::check_Fv(){
    for(int i=0;i<9;++i){
        for(int j=0;j<5;++j){
            if(data[9*i+j]!=-1&&data[9*i+j]==data[9*i+j+1]&&data[9*i+j]==data[9*i+j+2]&&data[9*i+j]==data[9*i+j+3]&&data[9*i+j]==data[9*i+j+4]){
                QTextStream out(stdout);
                out << QString("\ndata5=\n");
                out << QString::number(data[9*i+j]);
                count_score();
                count_score();
                count_score();
                data[9*i+j]=-1;
                data[9*i+j+1]=-1;
                data[9*i+j+2]=-5;
                data[9*i+j+3]=-1;
                data[9*i+j+4]=-1;
                typ[9*i+j+2]=5;
                out << QString::number(9*i+j+2);
                out << QString("\t=\t");
                out << QString::number(data[9*i+j+2]);

            }
        }
    }
    for(int j=0;j<9;++j){
        for(int i=0;i<5;++i){
            if(data[9*i+j]!=-1&&data[9*i+j]==data[9*(i+1)+j]&&data[9*i+j]==data[9*(i+2)+j]&&data[9*i+j]==data[9*(i+3)+j]&&data[9*i+j]==data[9*(i+4)+j]){
                count_score();
                count_score();
                count_score();
                data[9*i+j]=-1;
                data[9*(i+1)+j]=-1;
                data[9*(i+2)+j]=-5;
                data[9*(i+3)+j]=-1;
                data[9*(i+5)+j]=-1;
                typ[9*(i+2)+j]=5;
                QTextStream out(stdout);
                out << QString("\nsetfive data\n");
                out << QString::number(9*i+j+2);
                out << QString("=");
                out << QString::number(data[9*(i+2)+j]);
                out << QString::number(typ[9*(i+2)+j]);
            }
        }

    }
}







void MainWindow::check_T(){
    for(int j=0;j<7;++j){
        for(int i=0;i<7;++i){
            if(data[9*i+j]!=-1&&data[9*i+j]==data[9*(i+1)+j]&&data[9*i+j]==data[9*(i+2)+j]){
                if(data[9*i+j]==data[9*i+j+1]&&data[9*i+j]==data[9*i+j+2]){
                    count_score();
                    count_score();
                    typ[9*i+j]=4;
                    data[9*(i+1)+j]=-1;
                    data[9*(i+2)+j]=-1;
                    data[9*(i)+j+1]=-1;
                    data[9*(i)+j+2]=-1;





                }
                else{
                    if(data[9*(i+1)+j]==data[9*(i+1)+j+1]&&data[9*(i+1)+j]==data[9*(i+1)+j+2]){
                        typ[9*(i+1)+j]=4;
                        data[9*(i)+j]=-1;
                        data[9*(i+2)+j]=-1;
                        data[9*(i+1)+j+1]=-1;
                        data[9*(i+1)+j+2]=-1;





                }


                else {if(data[9*(i+2)+j]==data[9*(i+2)+j+1]&&data[9*(i+1)+j]==data[9*(i+2)+j+2]){
                    typ[9*(i+2)+j]=4;
                    data[9*(i)+j]=-1;
                    data[9*(i+1)+j]=-1;
                    data[9*(i+2)+j+1]=-1;
                    data[9*(i+2)+j+2]=-1;
                    }
                }
                }



        }
    }
    }

    for(int j=2;j<9;++j){
        for(int i=0;i<7;++i){
            if(data[9*i+j]!=-1&&data[9*i+j]==data[9*(i+1)+j]&&data[9*i+j]==data[9*(i+2)+j]){
                if(data[9*i+j]==data[9*i+j-1]&&data[9*i+j]==data[9*i+j-2]){
                    count_score();
                    count_score();
                    typ[9*i+j]=4;
                    data[9*(i+1)+j]=-1;
                    data[9*(i+2)+j]=-1;
                    data[9*(i)+j-1]=-1;
                    data[9*(i)+j-2]=-1;





                }
                else{
                    if(data[9*(i+1)+j]==data[9*(i+1)+j-1]&&data[9*(i+1)+j]==data[9*(i+1)+j-2]){
                        typ[9*(i+1)+j]=4;
                        data[9*(i)+j]=-1;
                        data[9*(i+2)+j]=-1;
                        data[9*(i+1)+j-1]=-1;
                        data[9*(i+1)+j-2]=-1;





                }


                else {if(data[9*(i+2)+j]==data[9*(i+2)+j-1]&&data[9*(i+1)+j]==data[9*(i+2)+j-2]){
                    typ[9*(i+2)+j]=4;
                    data[9*(i)+j]=-1;
                    data[9*(i+1)+j]=-1;
                    data[9*(i+2)+j-1]=-1;
                    data[9*(i+2)+j-2]=-1;
                    }
                    }
                }



        }



        }
    }

    for(int j=1;j<8;++j){
        for(int i=0;i<7;++i){
            if(data[9*i+j]!=-1&&data[9*i+j]==data[9*(i+1)+j]&&data[9*i+j]==data[9*(i+2)+j]){
                if(data[9*i+j]==data[9*i+j+1]&&data[9*i+j]==data[9*i+j-1]){
                    count_score();
                    count_score();
                    typ[9*i+j]=4;
                    data[9*(i+1)+j]=-1;
                    data[9*(i+2)+j]=-1;
                    data[9*(i)+j+1]=-1;
                    data[9*(i)+j-1]=-1;





                }
                else{
                    if(data[9*(i+1)+j]==data[9*(i+1)+j+1]&&data[9*(i+1)+j]==data[9*(i+1)+j-1]){
                        typ[9*(i+1)+j]=4;
                        data[9*(i)+j]=-1;
                        data[9*(i+2)+j]=-1;
                        data[9*(i+1)+j+1]=-1;
                        data[9*(i+1)+j-1]=-1;





                }


                else {if(data[9*(i+2)+j]==data[9*(i+2)+j+1]&&data[9*(i+1)+j]==data[9*(i+2)+j-1]){
                    typ[9*(i+2)+j]=4;
                    data[9*(i)+j]=-1;
                    data[9*(i+1)+j]=-1;
                    data[9*(i+2)+j+1]=-1;
                    data[9*(i+2)+j-1]=-1;
                    }
                }
                }



        }



        }
    }


}
void MainWindow::set_special(){
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){

            if(data[9*i+j]==-1){
                if(typ[9*i+j]==2){
                for(int k=0;k<9;++k){
                    count_score();
                    data[9*i+k]=-1;


                }
               }else if(typ[9*i+j]==3){
                    for(int k=0;k<9;++k){
                        count_score();
                        data[9*k+j]=-1;


                    }




                }


            }
        }
    }
}
void MainWindow::set_five(int a, int b){
    QTextStream out(stdout);
    out << QString::number(a);
    out << QString("\nSetfive=\n");
    out << QString::number(b);
    int tmp;
    tmp=data[b];
    if(typ[a]==5){
        data[a]=-1;
        typ[a]=1;
        if(data!=data2)
        for(int i=0;i<9;++i){
            for(int j=0;j<9;++j){
                out << QString::number(9*i+j);
                out << QString("\n");
                if(data[9*i+j]==tmp){
                    data[9*i+j]=-1;
                    count_score();
                    out << QString("\nSet555555555 data=\n");
                    out << QString::number(9*i+j);


                }


            }
        }


    }






}
void MainWindow::set_T(){
    QTextStream out(stdout);

    out << QString("\nSet T\n");
//    out << QString::number();
    for(int i=0;i<9;++i){
            for(int j=0;j<9;++j){

                if(data[9*i+j]==-1){
                    if(typ[9*i+j]==4){

                        out << QString::number(100100);
                        if((9*(i-1)+j-1)>0&&(9*(i-1)+j-1)<81){
                        data[9*(i-1)+j-1]=-1;
                        count_score();
                        out << QString::number(100100);
                        }

                        if((9*(i-1)+j+1)>0&&(9*(i-1)+j+1)<81){
                        data[9*(i-1)+j+1]=-1;
                        count_score();
                        }

                        if((9*(i-1)+j)>0&&(9*(i-1)+j)<81){

                        data[9*(i-1)+j]=-1;
                        count_score();
                        }

                        if((9*(i)+j-1)>0&&(9*(i)+j-1)<81){
                        data[9*(i)+j-1]=-1;
                        count_score();
                        }


                        if((9*(i)+j+1)>0&&(9*(i)+j+1)<81){
                        data[9*(i)+j+1]=-1;
                        count_score();
                        out << QString::number(100100);
                        }

                        if((9*(i+1)+j-1)>0&&(9*(i+1)+j-1)<81){
                        data[9*(i+1)+j-1]=-1;
                        count_score();
                        }

                        if((9*(i+1)+j+1)>0&&(9*(i+1)+j+1)<81){
                        data[9*(i+1)+j+1]=-1;
                        count_score();
                        }

                        if((9*(i+1)+j)>0&&(9*(i+1)+j)<81){
                        data[9*(i+1)+j]=-1;
                        count_score();
                        }



                    }
                    }
                }
            }
    }

void MainWindow::update_time(){
    tm=(timer.elapsed()/1000);
    ui->label_2->setNum((tm));

}

void MainWindow::step(){
    Move=Move-1;
    ui->label_4->setNum(Move);
    if(Move==0){
        if(star>0)ui->result->setText("You win");
        else ui->result->setText("You lose");
        ui->result->show();


    }



}

void MainWindow::count_score(){
    score=score+10;
    ui->label_6->setNum(score);
    if(score>1000){
        star=1;
        ui->label_8->setNum(star);
        if(score>3000){
            star=2;
            ui->label_8->setNum(star);
            if(score>6000){
                star=3;
                ui->label_8->setNum(star);
            }
        }
    }


}
void MainWindow::clock(){
for(int i=0;i<9;++i){
    for(int j=0;j<9;++j){
     if(data[9*i+j]==-1&&typ[9*i+j]==6)
         Move=Move+2;
     ui->label_4->setNum(Move);

    }
}
}


void MainWindow::create_clock(){
    int a=qrand()%81;
    while(data[a]<0||data[a]>5)
    a=qrand()%81;
    typ[a]=6;


}

void MainWindow::on_pushButton_clicked()
{
    emit quit(star,score);
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
        delete box[9*i+j];
        }
    }
        delete timer2;
        int a;
        turn=1;
        Move=5;
        ui->label_4->setNum(Move);
        star=0;
        score=0;

        //QTimer *timer2;
        tm=0;
        //QTimer::singleShot(1000, this, SLOT(update_time()));
        timer2 = new QTimer(this);
        connect(timer2, SIGNAL(timeout()), this, SLOT(update_time()));
        timer2->start(1000);
        timer.start();
        QTextStream out(stdout);
        out << QString("It took");
        out << QString::number((timer.elapsed()/1000));
        out << QString("milliseconds");
        //timer = new QTimer(this);
        //timer->start(1000);
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        box.resize(81);
        data.resize(81);
        data2.resize(81);
        typ.resize(81);
        for(int i=0;i<9;++i){
            for(int j=0;j<9;++j){
                typ[9*i+j]=1;
                a=qrand()%6;
                //while(i>1)
                while(i>1&&data[9*(i-1)+j]==a&&data[9*(i-2)+j]==a)
                {a=qrand()%6;}
                //while(j>1)
                while(j>1&&data[9*i+j-1]==a&&data[9*i+j-2]==a)
                {a=qrand()%6;}
                data[9*i+j]=a;
                rem[i][j]=false;
                if(data[9*i+j]==0)box[9*i+j]=new A(this,i,j,data[9*i+j]);
                if(data[9*i+j]==1)box[9*i+j]=new A(this,i,j,data[9*i+j]);
                if(data[9*i+j]==2)box[9*i+j]=new A(this,i,j,data[9*i+j]);
                if(data[9*i+j]==3)box[9*i+j]=new A(this,i,j,data[9*i+j]);
                if(data[9*i+j]==4)box[9*i+j]=new A(this,i,j,data[9*i+j]);
                if(data[9*i+j]==5)box[9*i+j]=new A(this,i,j,data[9*i+j]);
                connect(box[9*i+j],SIGNAL(Click(int,int,int)),this,SLOT(BoxClick(int,int,int)));
                data2=data;

            }
        }
        //QTextStream out(stdout);
        out << QString("\nboll=\n");
        SetNum();
        out << QString::number((*box[0])==(*box[9]));
        SetPicture();


}

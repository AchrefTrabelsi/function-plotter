#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <QtDebug>
//change to ° scale = M_PI/180
using namespace std;
float scale =1;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_released()
{
    QString x1,y1,x2,y2;
    x1=ui->PX1->text();
    x2=ui->PX2->text();
    y1=ui->PY1->text();
    y2=ui->PY2->text();
    ui->dessin->drawline(x1.toFloat(),y1.toFloat(),x2.toFloat(),y2.toFloat());
}

void MainWindow::on_pushButton_2_released()
{
    delete ui->dessin;
    ui->dessin =new GLWidget(this);
    ui->layoutdessin->addWidget(ui->dessin);
    ui->dessin->setMinimumSize(540,540);
    ui->dessin->setMaximumSize(540,540);
    ui->dessin->show();
    ui->PY1->setText("");
    ui->PY2->setText("");
    ui->PX2->setText("");
    ui->PX1->setText("");
}

long double calculateall ( string const& f, long double const& x)
{
    vector<char> op;
    vector<long double> num;
    string b = f;
    while(!b.empty())
    {

         if (b[0] == '(')
         {
            int i = 0;
            int go = 1;
            while (go)
            {
                i++;
                if (b[i] == '(')
                    go++;
                else if (b[i] == ')')
                    go--;
            }
            num.push_back(calculateall(b.substr(1, i - 1), x));
            if (i + 1 < b.size())
            {
                i++;
                op.push_back(b[i]);
            }
            b.erase(0, i + 1);

         }
         else if (b[0] == 's')
         {
             b.erase(b.begin());
             int i = 0;
             int go = 1;
             while (go)
             {
                 i++;
                 if (b[i] == '(')
                     go++;
                 else if (b[i] == ')')
                     go--;
             }
             num.push_back(sin(calculateall(b.substr(1, i - 1), x)*scale));
             if (i + 1 < b.size())
             {
                 i++;
                 op.push_back(b[i]);
             }
             b.erase(0, i + 1);


         }
         else if (b[0] == 'c')
         {
             b.erase(b.begin());
             int i = 0;
             int go = 1;
             while (go)
             {
                 i++;
                 if (b[i] == '(')
                     go++;
                 else if (b[i] == ')')
                     go--;
             }
             num.push_back(cos(calculateall(b.substr(1, i - 1), x) * scale));
             if (i + 1 < b.size())
             {
                 i++;
                 op.push_back(b[i]);
             }
             b.erase(0, i + 1);


         }
         else if (b[0] == 'e')
         {
             b.erase(b.begin());
             int i = 0;
             int go = 1;
             while (go)
             {
                 i++;
                 if (b[i] == '(')
                     go++;
                 else if (b[i] == ')')
                     go--;
             }
             num.push_back(exp(calculateall(b.substr(1, i - 1), x)));
             if (i + 1 < b.size())
             {
                 i++;
                 op.push_back(b[i]);
             }
             b.erase(0, i + 1);


         }
         else if (b[0] == 'l')
         {
             b.erase(b.begin());
             int i = 0;
             int go = 1;
             while (go)
             {
                 i++;
                 if (b[i] == '(')
                     go++;
                 else if (b[i] == ')')
                     go--;
             }
             num.push_back(log(calculateall(b.substr(1, i - 1), x)));
             if (i + 1 < b.size())
             {
                 i++;
                 op.push_back(b[i]);
             }
             b.erase(0, i + 1);


         }

         else if (b[0] == 'a')
         {
             b.erase(b.begin());
             int i = 0;
             int go = 1;
             while (go)
             {
                 i++;
                 if (b[i] == '(')
                     go++;
                 else if (b[i] == ')')
                     go--;
             }
             num.push_back(abs(calculateall(b.substr(1, i - 1), x)));
             if (i + 1 < b.size())
             {
                 i++;
                 op.push_back(b[i]);
             }
             b.erase(0, i + 1);


         }

         else
         {
             size_t i;
             if(b.size()>1)
             {
                 if(b[0]=='-'&&b[1]=='x')
                 {
                     num.push_back(-x);
                     b.erase(0, 2);
                     continue;

                 }
             }
             if (b[0] == 'x')
             {
                 num.push_back(x);
                 i = 1;
             }
             else
                 num.push_back(stof(b, &i));
             if (i < b.size())
             {
                 op.push_back(b[i]);
                 i++;
             }
             b.erase(0, i);





         }
    }
    for (int i = 0; i < op.size(); i++)
    {
        if (op[i] == '/')
        {
            num[i] = num[i] / num[i + 1];
            auto it = num.begin();
            advance(it, i + 1);
            num.erase(it);
            auto ito = op.begin();
            advance(ito, i);
            op.erase(ito);
            i--;

        }

    }
    for (int i = 0; i < op.size(); i++)
    {
        if (op[i] == '*')
        {
            num[i] = num[i] * num[i + 1];
            auto it = num.begin();
            advance(it, i + 1);
            num.erase(it);
            auto ito = op.begin();
            advance(ito, i);
            op.erase(ito);
            i--;

        }

    }
    for (int i = 0; i < op.size(); i++)
    {
        if (op[i] == '-')
        {
            num[i] = num[i] - num[i + 1];
            auto it = num.begin();
            advance(it, i + 1);
            num.erase(it);
            auto ito = op.begin();
            advance(ito, i);
            op.erase(ito);
            i--;

        }

    }
    long double sum = num[0];
    for (int i = 1; i < num.size(); i++)
    {
        sum += num[i];
    }
    return sum;

}
#define pas 0.0001
#define width 540
#define height 540
QLineF convert(float fx1,float fy1,float fx2,float fy2)
{
    float x1,x2,y1,y2;
    x1=fx1*38+width/2;
    y1=-fy1*38+height/2;
    x2=fx2*38+width/2;
    y2=-fy2*38+height/2;
    return QLineF(x1,y1,x2,y2);

}
void MainWindow::on_pushButton_3_clicked()
{
    QString a =ui->Function->toPlainText();
    a.replace("sin","s",Qt::CaseInsensitive);
    a.replace("cos","c",Qt::CaseInsensitive);
    a.replace("exp","e",Qt::CaseInsensitive);
    a.replace("ln","l",Qt::CaseInsensitive);
    a.replace("abs","a",Qt::CaseInsensitive);


    string f= a.toStdString();

    QVector<QLineF> res;
    float  x=-7.1;
    float  x1;
    float  y;
    float  y1;
    y=calculateall(f,x);
    while(x<7.11-pas)
    {
        x1=x+pas;
        y1=calculateall(f,x1);
        res.push_back(convert(x,y,x1,y1));
        x=x1;
        y=y1;
    }
    ui->dessin->drawfunction(res);

}

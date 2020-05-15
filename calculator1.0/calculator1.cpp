#include "calculator1.h"
#include "ui_calculator1.h"
#include <QPushButton>
#include <QString>
#include <QDebug>

#define rep(i,a,b) for(int i=a;i<=b;i++)

calculator1::calculator1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::calculator1)
{
    ui->setupUi(this);
     setWindowTitle("神奇计算器");
     this->setFixedSize(600,480);
     ui->less->setFlat(true);
     ui->confirm->setFlat(true);
     ui->confirm_3->setFlat(true);
     ui->confirm_4->setFlat(true);
     ui->confirm_5->setFlat(true);
     ui->confirm_6->setFlat(true);
     ui->confirm_7->setFlat(true);
     ui->confirm_8->setFlat(true);
     ui->confirm_9->setFlat(true);
     ui->confirm_10->setFlat(true);
     ui->confirm_11->setFlat(true);
     ui->confirm_12->setFlat(true);
     ui->confirm_13->setFlat(true);
     ui->confirm_14->setFlat(true);
     ui->NUMBER->setFlat(true);
     ui->pushButton_2->setFlat(true);
     ui->pushButton_3->setFlat(true);
     ui->pushButton_4->setFlat(true);
     ui->pushButton_5->setFlat(true);
     ui->pushButton_6->setFlat(true);
     ui->pushButton_7->setFlat(true);
     ui->pushButton_8->setFlat(true);
     ui->pushButton_9->setFlat(true);
     ui->ans->setFont(QFont("Timers",30,QFont::Light));
     ui->ans1->setFont(QFont("Timers",30,QFont::Bold));
     ui->ans->setStyleSheet("color:red");//文本颜色
     ui->ans1->setStyleSheet("color:red");//文本颜色
   //  ui->ans->setStyleSheet("background-color:transparent");//背景色
   //  ui->ans1->setStyleSheet("background-color:transparent");//背景色
//     ui->ans->setStyleSheet("background:transparent;border-width:0;border-style:outset");
//     ui->ans1->setStyleSheet("background:transparent;border-width:0;border-style:outset");

}

calculator1::~calculator1()
{
    delete ui;
}

void calculator1::on_pushButton_clicked()
{
    this->close();
}

void calculator1::on_confirm_clicked()
{
    this->count();
}

void calculator1::work()
{
            char c2;
            c2=q2.top();q2.pop();
            if(c2=='!')
            {
                double a1=q1.top();q1.pop();
                q1.push(!a1);
            return ;
        }
            double a1,a2;
            a1=q1.top();q1.pop();
            a2=q1.top();q1.pop();
    //      cout<<a1<<" "<<a2;
    //        qDebug()<<c2<<" "<<a1<<" "<<a2<<'\n';
    //        std::cout<<"answer"<<a1+a2;
            if(c2=='+') q1.push(a1+a2);
            else if(c2=='-')
            {
                    q1.push(a2-a1);
            }
            else if(c2=='/')
            {
                    q1.push(a2/a1);
            }
            else if(c2=='*')
            {
                    q1.push(a1*a2);
            }
            else if(c2=='|')
            {
            q1.push(a1||a2);
        }
        else if(c2=='&')
        {
            q1.push(a1&&a2);
        }
}

void calculator1::count()
{
    QString s=ui->ans->text();
    on_ans1_inputRejected();
    int len=s.length();
    rep(i,0,len-1)
    {
        qDebug()<<s[i];
            if(s[i]<='9'&&s[i]>='0')
            {

                    int id1=0;
                    rep(j,i,len-1)
                    {
                            if(s[j]=='/'||s[j]=='*'||s[j]=='+'||s[j]=='-'||s[j]==')'||s[j]=='|'||s[j]=='&'||s[j]=='!')
                            {
                                    id1=j;break;
                            }
                    }
                    if(!id1) id1=s.length();
                    QString s2=s.mid(i,id1-i);
                    double ans3 = s2.toDouble();
                    //qDebug()<<ans3<<"ans3"<<'\n';
                    i=id1-1;
                    q1.push(ans3);
            }
            else if(s[i]=='|')
            {
        while(!q2.empty()&&(q2.top()=='+'||q2.top()=='-'||q2.top()=='*'||q2.top()=='/'||q2.top()=='&'||q2.top()=='!'||q2.top()=='|'))
                    {

                                    work();
                    }
                    q2.push(s[i].unicode());
        ++i;
    }
    else if(s[i]=='&')
    {
        while(!q2.empty()&&(q2.top()=='+'||q2.top()=='-'||q2.top()=='*'||q2.top()=='/'||q2.top()=='&'||q2.top()=='!'))
                    {

                                    work();
                    }
                    q2.push(s[i].unicode());
        ++i;
    }
            else if(s[i]=='+'||s[i]=='-')
            {
                    while(!q2.empty()&&(q2.top()=='+'||q2.top()=='-'||q2.top()=='*'||q2.top()=='/'||q2.top()=='!'))
                    {

                                    work();
                    }
                    q2.push(s[i].unicode());
            }
            else if(s[i]=='*'||s[i]=='/')
            {
                    while(!q2.empty()&&(q2.top()=='*'||q2.top()=='/'||q2.top()=='!'))
                    {
                            work();
                    }
                    q2.push(s[i].unicode());
            }
            else if(s[i]=='!') q2.push(s[i].unicode());
            else if(s[i]=='(') {q2.push(s[i].unicode());}
            else if(s[i]==')')
            {
                    while(q2.top()!='(')
                    {
                            work();
                    }
                    q2.pop();
            }
    }
    while(!q2.empty())
    {
        work();
    }
    double ans=0;
    ans=q1.top();
    ui->ans1->setText(QString::number(ans));
}

void calculator1::on_ans1_inputRejected(){}

void calculator1::on_less_clicked()
{
    QString s1=ui->ans->text();
    s1.append("-");
    ui->ans->setText(s1);
}

void calculator1::on_confirm_3_clicked()
{
    QString s1=ui->ans->text();
    s1.append("+");
    ui->ans->setText(s1);
}

void calculator1::on_confirm_4_clicked()
{
    QString s1=ui->ans->text();
    s1.append("*");
    ui->ans->setText(s1);
}

void calculator1::on_confirm_5_clicked()
{
    QString s1=ui->ans->text();
    s1.append("/");
    ui->ans->setText(s1);
}

void calculator1::on_confirm_6_clicked()
{
    QString s1=ui->ans->text();
    s1.append("||");
    ui->ans->setText(s1);
}

void calculator1::on_confirm_7_clicked()
{
    QString s1=ui->ans->text();
    s1.append("&&");
    ui->ans->setText(s1);
}

void calculator1::on_confirm_8_clicked()
{
    QString s1=ui->ans->text();
    s1.append("!");
    ui->ans->setText(s1);
}

void calculator1::on_confirm_9_clicked()
{
    QString s1=ui->ans->text();
    s1.append("(");
    ui->ans->setText(s1);
}


void calculator1::on_confirm_10_clicked()
{
    QString s1=ui->ans->text();
    s1.append(")");
    ui->ans->setText(s1);
}

void calculator1::on_NUMBER_clicked()
{
    QString s1=ui->ans->text();
    s1.append("0");
    ui->ans->setText(s1);
}

void calculator1::on_pushButton_2_clicked()
{
    QString s1=ui->ans->text();
    s1.append("1");
    ui->ans->setText(s1);
}

void calculator1::on_pushButton_3_clicked()
{
    QString s1=ui->ans->text();
    s1.append("2");
    ui->ans->setText(s1);
}

void calculator1::on_pushButton_4_clicked()
{
    QString s1=ui->ans->text();
    s1.append("3");
    ui->ans->setText(s1);
}

void calculator1::on_pushButton_5_clicked()
{
    QString s1=ui->ans->text();
    s1.append("4");
    ui->ans->setText(s1);
}

void calculator1::on_pushButton_6_clicked()
{
    QString s1=ui->ans->text();
    s1.append("5");
    ui->ans->setText(s1);
}

void calculator1::on_pushButton_7_clicked()
{
    QString s1=ui->ans->text();
    s1.append("6");
    ui->ans->setText(s1);
}

void calculator1::on_pushButton_8_clicked()
{
    QString s1=ui->ans->text();
    s1.append("7");
    ui->ans->setText(s1);
}

void calculator1::on_pushButton_9_clicked()
{
    QString s1=ui->ans->text();
    s1.append("8");
    ui->ans->setText(s1);
}

void calculator1::on_confirm_13_clicked()
{
    QString s1=ui->ans->text();
    s1.append("9");
    ui->ans->setText(s1);
}

void calculator1::on_confirm_14_clicked()
{
    QString s1=ui->ans->text();
    s1.append(".");
    ui->ans->setText(s1);
}

void calculator1::on_confirm_11_clicked()
{
    QString s1=ui->ans->text();
    s1=s1.left(s1.length()-1);
    ui->ans->setText(s1);
}

void calculator1::on_confirm_12_clicked()
{
    QString s1=ui->ans->text();
    s1.clear();
    ui->ans->setText(s1);
}

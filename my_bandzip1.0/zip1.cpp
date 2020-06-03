#include "zip1.h"
#include "ui_zip1.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QWidget>

using namespace std;

zip1::zip1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::zip1)
{
    ui->setupUi(this);
    resize(910,530);
    this->setWindowTitle("Bandzip1.0");
    //ui->pushButton->setFlat(true);
    connect(ui->actionnew,&QAction::triggered,ui->pushButton,&QPushButton::clicked);
    connect(ui->actionclose,&QAction::triggered,this,&QWidget::close);
    connect(ui->actionsize,&QAction::triggered,[=]()
    {
        QMessageBox::information(this,"info","压缩大小限制在10m以内");
    }
    );
    connect(ui->actionhow,&QAction::triggered,[=]()
    {
        QMessageBox::information(this,"info","每次解压时把解压文件和.code在同一目录下");
    }
    );
}

zip1::~zip1()
{
    delete ui;
}


void zip1::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\11861\\Desktop");
    if(path!=nullptr)
    {qDebug()<<path;
    a.read(path);
    a.count();
    a.make_haffman();
    a.zip();
    a.write(path);
    a.savecode();
    //qDebug()<<a.origin_size<<a.final_size;
    double ans=(a.final_size/a.origin_size)*100;
    QString s=QString::number(ans);
    QMessageBox::information(this,"cue","压缩后和压缩前之比"+s+"%");
    }
}

void tree::preoeder(int tem_code,int tem_len)
{
        code=tem_code;
        code_len=tem_len;
        if(left_tree) left_tree->preoeder(tem_code<<1,tem_len+1);
        if(right_tree) right_tree->preoeder((tem_code<<1)|1,tem_len+1);
}

void haffman::read(QString s)//读入
{
        FILE *tem;
        int tem1=0;
        strcpy(first_name,s.toLocal8Bit().data());//转换字符串
        tem=fopen(first_name,"rb");
        if(tem==NULL)
        {
                return;
        }
        strcpy(code_name,first_name);
        while(code_name[tem1]!='.'&&code_name[tem1]) ++tem1;
        strcpy(code_name+tem1,".cod");

        char *tem2=r;
        tem1=0;
        lenth=0;
        do
        {
                tem1=fread(tem2,sizeof(char),1024,tem);
                lenth+=tem1;
                if(lenth>10*1024*1024)//1m=1024kb 1kb=1024b
                {
                        lenth=10*1024*1024;
                        break;
                }
                tem2+=tem1;
        } while (tem1==1024);
        fclose(tem);
        QFile tem3(first_name);
        origin_size=tem3.size();
}

void haffman::new_sort(tree *a[],int b,int e)//快排原理
{
        if(b>=e) return;
        tree *tem;
        int k=a[b]->times,left=b,right=e;
        while(left<right)
        {
                while(left<right&&a[right]->times>=k) right--;
                tem=a[left];a[left]=a[right];a[right]=tem;
                while(left<right&&a[left]->times<k) left++;
                tem=a[left];a[left]=a[right];a[right]=tem;
        }
        a[right] = a[left] ;
        new_sort(a,b,right-1);
        new_sort(a,right+1,e);
}

void haffman::count()//计算频率
{
        bas_len=0;
        char *s=r;
        for(int i=0;i<lenth;++i)
        {
                int j,sym=1;
                for(j=0;bas[j];j++)
                {
                        if(bas[j]->data==*s)
                        {
                                bas[j]->times++;
                                sym=0;
                                break;
                        }
                }
                if(sym)//新的字符
                {
                        bas[j]=new tree;
                        bas[j]->data=*s;
                        bas[j]->times=1;
                        ++bas_len;
                }
                ++s;
        }
}

void haffman::make_haffman()
{
        tree *tem[bas_len];
        memcpy(tem,bas,sizeof(tree*)*bas_len);
        if(haff_root) delete haff_root;
        int num=0;
        while(num<bas_len-1)
        {
                new_sort(tem,num,bas_len-1);
                haff_root=new tree;
                haff_root->times=tem[num]->times+tem[num+1]->times;
                haff_root->left_tree=tem[num];
                haff_root->right_tree=tem[num+1];
                tem[num+1]=haff_root;
                ++num;
        }
        haff_root->preoeder(0,0);//haffman 序列形成
}

void haffman::wbit(int i)
{
        buffer[max_bu]=buffer[max_bu]|(i<<bu);
        ++bu;
        if(bu>=8)
        {
                bu=0;
                ++max_bu;//bit+1
        }
}

void haffman::zip()//压缩字符串到缓冲区
{
     max_bu=bu=0;
    char *s=r;
    for(int i=0;i<lenth;++i)    //压缩内容到buffer,直到 r 内容结束
    {
        int j=0;
        for(j=0;j<bas_len;++j)
        {
            if(bas[j]->data==*s)break;
        }
        for(int k=bas[j]->code_len-1;k>=0;--k)
        {
            wbit(1&(bas[j]->code>>k));
        }
        ++s;
    }
}

void haffman::write(QString path) //缓冲区写入文件
{
        FILE *tem;
        char s[100];
        int num2=path.length();
        for(int i = num2-1;i>=0;i--)
        {
            if(path[i]=='.') {num2=i;break;}
        }
        formulate=path.right(path.length()-num2);//截取原来的文件格式保存起来
        path=path.left(num2);
        path+=".zip";
        strcpy(s,path.toLocal8Bit().data());
        int num=0;
        strcpy(code_name,s);
        while(code_name[num]!='.'&&code_name[num]) ++num;
        strcpy(code_name+num,".cod");

        tem=fopen(s,"wb");
        if(tem==0)
        {
                 return;
        }
        for(int i=0;i<=max_bu;++i)
        {
                fputc(buffer[i],tem);
        }
        fclose(tem);
        QFile tem1(path);
        final_size=tem1.size();
}

void haffman::savecode()
{
        FILE *tem;
        tem=fopen(code_name,"w");
        if(tem==0)
        {
                return;
        }
        char s1[10];
        strcpy(s1,formulate.toLatin1().data());
        fprintf(tem,"%s\n",s1);//保存文件格式
        fprintf(tem,"%d %d\n",max_bu,bu);//保存缓冲区大小
        for(int i=0;i<bas_len;++i)//保存字符 编码 编码长度
        {
                fprintf(tem,"%d %d %d\n",bas[i]->data,bas[i]->code,bas[i]->code_len);
        }
        fclose(tem);
}

void haffman::readbuffer(QString path)//读取文件内容到缓冲区
{
        read(path);
        memcpy(buffer,r,lenth*sizeof(char));
}

void haffman::readcode()
{
     FILE *tem;
        tem=fopen(code_name,"r");
        if(tem==0)
        {
                return ;
        }
        bas_len=0;
        char s1[10];
        fscanf(tem,"%s",&s1);
        formulate=s1;//读取文件格式
        fscanf(tem,"%d %d",&max_bu,&bu);//读取缓冲区大小
        while(!feof(tem))//读取字符 编码 编码长度
        {
                bas[bas_len]=new tree;
                if(fscanf(tem,"%d %d %d",&bas[bas_len]->data,&bas[bas_len]->code,&bas[bas_len]->code_len)==3) ++bas_len;
        }
        fclose(tem);
}

void haffman::unzip(QString path)
{
        int tem1=0,i=0;
        int c=0,len=0;
        FILE *tem;
        int num2=path.length();
        for(int i = num2-1;i>=0;i--)
        {
            if(path[i]=='.') {num2=i;break;}
        }
        path=path.left(num2);
        path+=formulate;
        qDebug()<<formulate;
        strcpy(final_name,path.toLatin1().data());
        tem=fopen(final_name,"wb");
        if(tem==0)
        {

                return;
        }
        while(tem1<max_bu||(tem1==max_bu&&i<bu))//解压,直到缓冲区结束
        {
                c=c<<1;
                c|=1&(buffer[tem1]>>i);
                ++i;
                if(i>=8)
                {
                        i=0;
                        ++tem1;//bit++
                }
                ++len;
                for(int j=0;j<bas_len;++j)
                {
                        if(len==bas[j]->code_len&&c==bas[j]->code)
                        {
                                len=c=0;
                                fputc(bas[j]->data,tem);
                                break;
                        }
                }
        }
        fclose(tem);
}

void zip1::on_pushButton_2_clicked()
{
     QString path = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\11861\\Desktop");
     if(path!=nullptr)
    {
    a.readbuffer(path);
    a.readcode();
    a.unzip(path);
    }
}

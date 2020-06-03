#ifndef ZIP1_H
#define ZIP1_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE


class tree//haffman tree
{
        public :
        int times;//hez
        char data;//data
        int code;//字符
        int code_len;//字符长度
        tree *left_tree,*right_tree;
        tree(){times=code=code_len=0;data=NULL;left_tree=right_tree=0;}
        ~tree()
        {
                if(left_tree)
                delete left_tree;
                if(right_tree)
                delete right_tree;
        }
        void preoeder(int,int);//先序遍历,生成haffman编码
};

class haffman
{
        private:
        char first_name[100];//被压缩的名字（用来存路径）
        char final_name[100];//
        char code_name[100];//
        tree *bas[551];//基础字符编码树
        tree *haff_root;//根节点
        int bas_len;//基础字符树个数
        char *buffer,*r;//缓冲区,读入文件内容
        int lenth;//读入内容长度
        int max_bu,bu;//最大缓冲区段基值,偏移量
        QString formulate;
        public :
        double origin_size,final_size;
        haffman()
        {
                haff_root=NULL;
                buffer = new char [10*1024*1024];//1m=1024kb 1kb=1024b;
                r= new char [10*1021*1024];
                memset(bas,0,sizeof(bas));
        }
        ~haffman()
        {
                delete buffer;
                delete r;
                delete haff_root;
        }
        void read(QString s);
        void count();//计算字符出现频率
        void new_sort(tree *a[],int,int);//快排
        void make_haffman();//生成haffman树
        void wbit(int);//向缓冲区写入一个字节
        void zip();
        void write(QString);//写入文件缓冲区中的内容
        void savecode();//保存haffman编码和缓冲区大小,供解压用
        void readbuffer(QString);//读入压缩文件内容到缓冲区
        void readcode();//读取haffman编码和缓冲区大小,供解压用
        void unzip(QString);
};

namespace Ui { class zip1; }
QT_END_NAMESPACE

class zip1 : public QMainWindow
{
    Q_OBJECT

public:
    zip1(QWidget *parent = nullptr);
    ~zip1();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private:
    Ui::zip1 *ui;
    haffman a;
};

#endif // ZIP1_H

#include "widget.h"
#include "ui_widget.h"
#include"mytread.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建子线程对象
    Generate* gen=new Generate;
    BubbleSort* bubble=new BubbleSort;
    QuickSort* quick=new QuickSort;

    connect(this,&Widget::starting,gen,&Generate::recvnum);
    //启动子线程
    connect(ui->Button_start,&QPushButton::clicked,this,[=]()
    {
        emit starting(10000);
        gen->start();
    });
    connect(gen,&Generate::sendArray,bubble,&BubbleSort::recvnum);
    connect(gen,&Generate::sendArray,quick,&QuickSort::recvnum);
    //处理子线程返回的信号结果
    connect(gen,&Generate::sendArray,this,[=](QVector<int>list)
    {
        bubble->start();
        quick->start();
        for(int i=0;i<list.size();i++)
        {
            ui->list_rand->addItem(QString::number(list.at(i)));
        }
    });
    connect(bubble,&BubbleSort::finish,this,[=](QVector<int>list)
    {
        for(int i=0;i<list.size();i++)
        {
            ui->list_bubble->addItem(QString::number(list.at(i)));
        }
    });
    connect(quick,&QuickSort::finish,this,[=](QVector<int>list)
    {
        for(int i=0;i<list.size();i++)
        {
            ui->list_quick->addItem(QString::number(list.at(i)));
        }
    });
}

Widget::~Widget()
{
    delete ui;
}


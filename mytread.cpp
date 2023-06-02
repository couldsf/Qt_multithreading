#include "mytread.h"
#include<QElapsedTimer>
#include<QDebug>
#include <QRandomGenerator>
Generate::Generate(QObject *parent) : QThread{parent}
{

}

void Generate::recvnum(int num)
{
    m_num=num;
}

void Generate::run()
{
    QRandomGenerator* generator = QRandomGenerator::global();
    qDebug()<<"生成随机数的线程地址:"<<QThread::currentThread();
    QVector<int> list;
    QElapsedTimer timer;
    timer.start();
    for(int i=0;i<m_num;i++)
    {
       list.push_back(generator->bounded(10000));
    }
    qDebug()<<"生成随机数的时间:"<<timer.elapsed()<<"毫秒";
    emit sendArray(list);
}

BubbleSort::BubbleSort(QObject *parent):QThread(parent)
{

}

void BubbleSort::recvnum(QVector<int> list)
{
   m_list=list;
}
void BubbleSort::run()
{
    int temp;
    qDebug()<<"冒泡排序的线程地址:"<<QThread::currentThread();
    QElapsedTimer timer;
    timer.start();
    for (int i = 0; i < m_list.size() - 1; i++)
    {
            for (int j = 0; j < m_list.size() - i - 1; j++)
            {
                if (m_list[j] > m_list[j + 1])
                {
                    // 交换两个数的位置
                    temp = m_list[j];
                    m_list[j] = m_list[j + 1];
                    m_list[j + 1] = temp;
                }
            }
   }
    qDebug()<<"冒泡排序的时间:"<<timer.elapsed()<<"毫秒";
    emit finish(m_list);
}

QuickSort::QuickSort(QObject *parent):QThread(parent)
{

}

void QuickSort::recvnum(QVector<int> list)
{
    m_list=list;
}

void QuickSort::quick_sort(QVector<int> &s, int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                s[i++] = s[j];

            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // 递归调用
        quick_sort(s, i + 1, r);
    }
}

void QuickSort::run()
{
    qDebug()<<"快速排序的线程地址:"<<QThread::currentThread();
    QElapsedTimer timer;
    timer.start();
    quick_sort(m_list,0,m_list.size()-1);
    qDebug()<<"快速排序的时间:"<<timer.elapsed()<<"毫秒";
    emit finish(m_list);
}

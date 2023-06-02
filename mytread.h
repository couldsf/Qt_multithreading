#ifndef MYTREAD_H
#define MYTREAD_H

#include <QThread>
#include<QVector>
//生成随机数
class Generate : public QThread
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);
    void recvnum(int num);
//重写run()
protected:
    void run() override;
signals:
    void sendArray(QVector<int> list);
private:
    int m_num;

};


class BubbleSort : public QThread
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
    void recvnum(QVector<int> list);
//重写run()
protected:
    void run() override;
signals:
    void finish(QVector<int> list);
private:
    QVector<int> m_list;

};

class QuickSort : public QThread
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
    void recvnum(QVector<int> list);
    void quick_sort(QVector<int> &s,int l,int r);
//重写run()
protected:
    void run() override;
signals:
    void finish(QVector<int> list);
private:
    QVector<int> m_list;

};
#endif // MYTREAD_H

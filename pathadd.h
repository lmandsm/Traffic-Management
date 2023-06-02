#pragma execution_character_set("utf-8")
#ifndef PATHADD_H
#define PATHADD_H

#include <QWidget>
#include<ALGraph.h>

namespace Ui {
class PathAdd;
}

class PathAdd : public QWidget
{
    Q_OBJECT

public:
    explicit PathAdd(QWidget *parent = nullptr);
    ~PathAdd();

private slots:
    void on_PathAdd_Confirm_pushButton_clicked();

    void on_PathAdd_Exit_pushButton_clicked();
    void PathST_EditDay();
    void PathET_EditDay();

signals:
    //传输线路的交通工具，车次，起始站，终点站，出发时间，到达时间，旅费
    void sendPathInf(struct LineNode);
private:
    Ui::PathAdd *ui;
    QStringList monthList;
    int dayN=31;
    int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    QStringList dayList;
    QStringList hourList;
    QStringList minList;
};

#endif // PATHADD_H

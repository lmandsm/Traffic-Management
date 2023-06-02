#pragma execution_character_set("utf-8")
#ifndef PATHMODIFY_H
#define PATHMODIFY_H

#include <QWidget>
#include<ALGraph.h>
namespace Ui {
class PathModify;
}

class PathModify : public QWidget
{
    Q_OBJECT

public:
    explicit PathModify(QWidget *parent = nullptr);
    ~PathModify();

private slots:
    void on_PathMdy_Confirm_pushButton_clicked();

    void on_PathMdy_Exit_pushButton_clicked();
    void PathMdyST_EditDay();
    void PathMdyET_EditDay();
signals:
    void sendIsMdy(bool flag);
    //传输修改过后的线路的交通工具，车次，起始站，终点站，出发时间，到达时间，旅费
    void sendPathMdyInf( struct LineNode);
private:
    Ui::PathModify *ui;
    QStringList monthList;
    int dayN=31;
    int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    QStringList dayList;
    QStringList hourList;
    QStringList minList;
};

#endif // PATHMODIFY_H

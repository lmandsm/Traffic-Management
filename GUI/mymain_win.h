#ifndef MYMAIN_WIN_H
#define MYMAIN_WIN_H
#pragma execution_character_set("utf-8")//避免中文乱码
#include <QMainWindow>
#include<QPushButton>
#include<QLayout>
#include<QComboBox>
#include<QDebug>//打印输出
#include<QCompleter>//Qcompleter头文件
#include<QMap>
#include<QString>
#include <QHeaderView>
#include<QMessageBox>
#include<ALGraph.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MyMain_win; }
QT_END_NAMESPACE

class MyMain_win : public QMainWindow
{
    Q_OBJECT

public:
    MyMain_win(QWidget *parent = nullptr);
    ~MyMain_win();
    void switchPage();//切换页面
    void init_Page_PathChoose();
    void init_Page_PathCheck();
    void init_Page_CityCheck();
private slots:
    void save_transportation();
    void save_choose_src();
    void save_choose_des();
    void save_choose_preferchoice();
    void save_choose_month();
    void save_choose_day();
    void save_choose_hour();
    void save_choose_min();
    void on_Check_pushButton_clicked();

private:
    Ui::MyMain_win *ui;
    QString choose_transportation;
    QString choose_src;
    QString choose_des;
    bool PreferChoice;
    QString choose_month;
    QString choose_day;
    QString choose_hour;
    QString choose_min;
    QStringList srcList;
    QStringList desList;
    QStringList monthList;
    int dayN=31;
    int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    QStringList dayList;
    QStringList hourList;
    QStringList minList;
    //QStringList dayl

};
#endif // MYMAIN_WIN_H

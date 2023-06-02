#include "pathadd.h"
#include "ui_pathadd.h"

PathAdd::PathAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathAdd)
{
    ui->setupUi(this);
    //初始化界面
        //交通工具选择
    ui->Path_Trans_comboBox->addItem("飞机");
    ui->Path_Trans_comboBox->addItem("火车");
        //出发时间和到达时间
        //月
    monthList<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12";
    ui->PathST_month_comboBox->addItems(monthList);
    ui->PathET_month_comboBox->addItems(monthList);
    connect(ui->PathST_month_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(PathST_EditDay()));
    connect(ui->PathET_month_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(PathET_EditDay()));
        //日

        //小时
    QString tmp;
    for(int i=0;i<=23;++i){
        tmp=QString::number(i,10);
        hourList<<tmp;
    }
    ui->PathST_hour_comboBox->addItems(hourList);
    ui->PathET_hour_comboBox->addItems(hourList);
    //connect(ui->hour_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(save_choose_hour()));
        //分钟
    for(int i=0;i<=59;++i){
        tmp=QString::number(i,10);
        minList<<tmp;
    }
    ui->PathST_min_comboBox->addItems(minList);
    ui->PathET_min_comboBox->addItems(minList);
}


PathAdd::~PathAdd()
{
    delete ui;
}
//设置添加出发时间的添加月份
void PathAdd::PathST_EditDay(){
    //获取选择月份的天数
    dayN=day[ui->PathST_month_comboBox->currentIndex()];
    dayList.clear();
    QString tmpday;
    //插入天数
    for(int i=1;i<=dayN;++i){
        tmpday=QString::number(i,10);
        dayList<<tmpday;
    }
    ui->PathST_day_comboBox->clear();
    ui->PathST_day_comboBox->addItems(dayList);
}
//设置添加到达时间的添加月份
void PathAdd::PathET_EditDay(){
    dayN=day[ui->PathET_month_comboBox->currentIndex()];
    dayList.clear();
    QString tmpday;
    for(int i=1;i<=dayN;++i){
        tmpday=QString::number(i,10);
        dayList<<tmpday;
    }
    ui->PathET_day_comboBox->clear();
    ui->PathET_day_comboBox->addItems(dayList);
}
void PathAdd::on_PathAdd_Confirm_pushButton_clicked()
{
    struct Time tmpST(ui->PathST_month_comboBox->currentText().toInt(),ui->PathST_day_comboBox->currentText().toInt(),ui->PathST_hour_comboBox->currentText().toInt(),ui->PathST_min_comboBox->currentText().toInt());
    struct Time tmpET(ui->PathET_month_comboBox->currentText().toInt(),ui->PathET_day_comboBox->currentText().toInt(),ui->PathET_hour_comboBox->currentText().toInt(),ui->PathET_min_comboBox->currentText().toInt());
    struct LineNode tmpLineNode(ui->Path_Trans_comboBox->currentText().toStdString(),ui->order_lineEdit->text().toStdString(),ui->PathSrc_lineEdit->text().toStdString(),ui->PathDes_lineEdit->text().toStdString(),tmpST,tmpET,ui->PayMoney_lineEdit->text().toFloat());
    emit sendPathInf(tmpLineNode);
    this->close();
}


void PathAdd::on_PathAdd_Exit_pushButton_clicked()
{
    this->close();
}


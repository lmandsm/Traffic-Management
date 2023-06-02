#include "pathmodify.h"
#include "ui_pathmodify.h"

PathModify::PathModify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathModify)
{
    ui->setupUi(this);
    //初始化界面
        //交通工具选择
    ui->PathMdy_Trans_comboBox->addItem("飞机");
    ui->PathMdy_Trans_comboBox->addItem("火车");
        //出发时间和到达时间
        //月
    monthList<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12";
    ui->PathMdyST_month_comboBox->addItems(monthList);
    ui->PathMdyET_month_comboBox->addItems(monthList);
    connect(ui->PathMdyST_month_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(PathMdyST_EditDay()));
    connect(ui->PathMdyET_month_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(PathMdyET_EditDay()));
        //日

        //小时
    QString tmp;
    for(int i=0;i<=23;++i){
        tmp=QString::number(i,10);
        hourList<<tmp;
    }
    ui->PathMdyST_hour_comboBox->addItems(hourList);
    ui->PathMdyET_hour_comboBox->addItems(hourList);
    //connect(ui->hour_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(save_choose_hour()));
        //分钟
    for(int i=0;i<=59;++i){
        tmp=QString::number(i,10);
        minList<<tmp;
    }
    ui->PathMdyST_min_comboBox->addItems(minList);
    ui->PathMdyET_min_comboBox->addItems(minList);
}

PathModify::~PathModify()
{
    delete ui;
}
void PathModify::PathMdyST_EditDay(){
    //获取选择月份的天数
    dayN=day[ui->PathMdyST_month_comboBox->currentIndex()];
    dayList.clear();
    QString tmpday;
    //插入天数
    for(int i=1;i<=dayN;++i){
        tmpday=QString::number(i,10);
        dayList<<tmpday;
    }
    ui->PathMdyST_day_comboBox->clear();
    ui->PathMdyST_day_comboBox->addItems(dayList);
}
void PathModify::PathMdyET_EditDay(){
    dayN=day[ui->PathMdyET_month_comboBox->currentIndex()];
    dayList.clear();
    QString tmpday;
    for(int i=1;i<=dayN;++i){
        tmpday=QString::number(i,10);
        dayList<<tmpday;
    }
    ui->PathMdyET_day_comboBox->clear();
    ui->PathMdyET_day_comboBox->addItems(dayList);
}
void PathModify::on_PathMdy_Confirm_pushButton_clicked()
{
    struct Time tmpST(ui->PathMdyST_month_comboBox->currentText().toInt(),ui->PathMdyST_day_comboBox->currentText().toInt(),ui->PathMdyST_hour_comboBox->currentText().toInt(),ui->PathMdyST_min_comboBox->currentText().toInt());
    struct Time tmpET(ui->PathMdyET_month_comboBox->currentText().toInt(),ui->PathMdyET_day_comboBox->currentText().toInt(),ui->PathMdyET_hour_comboBox->currentText().toInt(),ui->PathMdyET_min_comboBox->currentText().toInt());
    struct LineNode tmpLineNode(ui->PathMdy_Trans_comboBox->currentText().toStdString(),ui->PathMdy_order_lineEdit->text().toStdString(),ui->PathMdySrc_lineEdit->text().toStdString(),ui->PathMdyDes_lineEdit->text().toStdString(),tmpST,tmpET,ui->MdyPayMoney_lineEdit->text().toFloat());
    emit sendPathMdyInf(tmpLineNode);
    emit sendIsMdy(true);
    this->close();
}


void PathModify::on_PathMdy_Exit_pushButton_clicked()
{
    emit sendIsMdy(false);
    this->close();
}


#pragma execution_character_set("utf-8")
#include "mymain_win.h"
#include "ui_mymain_win.h"

MyMain_win::MyMain_win(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMain_win)
{
    ui->setupUi(this);

    //界面切换按钮设置
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->PathChoose_pushButton,&QPushButton::clicked,this,&MyMain_win::switchPage);
    connect(ui->PathCheck_pushButton,&QPushButton::clicked,this,&MyMain_win::switchPage);
    connect(ui->CityCheck_pushButton,&QPushButton::clicked,this,&MyMain_win::switchPage);
    connect(ui->Return_pushButton,&QPushButton::clicked,this,&MyMain_win::switchPage);
    connect(ui->Return_pushButton_2,&QPushButton::clicked,this,&MyMain_win::switchPage);
    connect(ui->Return_pushButton_3,&QPushButton::clicked,this,&MyMain_win::switchPage);
    //初始化三个按钮界面
    init_Page_PathChoose();
    init_Page_PathCheck();
    init_Page_CityCheck();


}

MyMain_win::~MyMain_win()
{
    delete ui;
}
void MyMain_win::switchPage(){
    QPushButton *button=qobject_cast<QPushButton*>(sender());//获取按下按钮的指针
    if(button==ui->PathChoose_pushButton){
        ui->stackedWidget->setCurrentIndex(1);//根据按下的按钮转至对应索引页
    }else if(button==ui->PathCheck_pushButton){
        ui->stackedWidget->setCurrentIndex(2);
    }else if(button==ui->CityCheck_pushButton){
        ui->stackedWidget->setCurrentIndex(3);
    }else if(button==ui->Return_pushButton||button==ui->Return_pushButton_2||button==ui->Return_pushButton_3){
        ui->stackedWidget->setCurrentIndex(0);
    }
}
void MyMain_win::init_Page_PathChoose(){
    //路径选择widget设置

    //交通工具选择
    ui->Way_comboBox->addItem("飞机");
    ui->Way_comboBox->addItem("火车");
    connect(ui->Way_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(save_transportation()));


    //起始地点
        //对初始地点集合初始化
    srcList<<"北京"<<"上海"<<"山东";
        //构建模糊查询对象
    QCompleter *MySrcInfor=new QCompleter(srcList);
        //设置src_lineEdit的模糊查询对象
    ui->src_lineEdit->setCompleter(MySrcInfor);
    connect(ui->src_lineEdit,SIGNAL(editingFinished()),this,SLOT(save_choose_src()));


    //终点地点
        //对终点地点集合初始化
    desList<<"北京"<<"上海"<<"山东";
        //构建模糊查询对象
    QCompleter *MyDesInfor=new QCompleter(desList);
        //设置des_lineEdit的模糊查询对象
    ui->des_lineEdit->setCompleter(MyDesInfor);
    connect(ui->des_lineEdit,SIGNAL(editingFinished()),this,SLOT(save_choose_des()));

    //选择耗时短,花费少,中转少
    ui->PreferChoice_comboBox->addItem("耗时短");
    ui->PreferChoice_comboBox->addItem("花费少");
    ui->PreferChoice_comboBox->addItem("中转少");
    connect(ui->PreferChoice_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(save_choose_preferchoice()));


    //出发时间
        //月
    monthList<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12";
    ui->month_comboBox->addItems(monthList);
    connect(ui->month_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(save_choose_month()));
        //日
    connect(ui->day_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(save_choose_day()));
        //小时
    QString tmp;
    for(int i=0;i<=23;++i){
        tmp=QString::number(i,10);
        hourList<<tmp;
    }
    ui->hour_comboBox->addItems(hourList);
    connect(ui->hour_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(save_choose_hour()));
        //分钟
    for(int i=0;i<=59;++i){
        tmp=QString::number(i,10);
        minList<<tmp;
    }
    ui->min_comboBox->addItems(minList);
    connect(ui->min_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(save_choose_min()));

    //结果显示Table初始化

    ui->PathChoose_Table->setColumnCount(6);
        //表格表头：车次，起始站，终点站，出发时间，到站时间，耗时,花销
    QStringList tmpheader;
    tmpheader<<"班次"<<"起始站"<<"终点站"<<"出发时间"<<"到达时间"<<"旅费";
    ui->PathChoose_Table->setHorizontalHeaderLabels(tmpheader);
    ui->PathChoose_Table->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->PathChoose_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
    ui->PathChoose_Table->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    ui->PathChoose_Table->verticalHeader()->setVisible(true);   //隐藏列表头
    connect(ui->Check_pushButton,SIGNAL(&QPushButton::click),this,SLOT(on_Check_pushButton_clicked()));
    //ui->PathChoose_Table->setRowCount(2);
    //QComboBox *tmpcomBox = new QComboBox();
    //tmpcomBox->addItem("Y");
    //tmpcomBox->addItem("N");
    //ui->PathChoose_Table->setCellWidget(0,0,tmpcomBox);
    //connect(ui->Check_pushButton,&QPushButton::clicked,this,&MyMain_win::on_Check_pushButton_clicked);

}
void MyMain_win::init_Page_PathCheck(){

}
void MyMain_win::init_Page_CityCheck(){

}

void MyMain_win::save_transportation()
{
    choose_transportation=ui->Way_comboBox->currentText();
    //qDebug()<<choose_transportation;
}
void MyMain_win::save_choose_src()
{
    choose_src=ui->src_lineEdit->text();
    //qDebug()<<choose_src;
}
void MyMain_win::save_choose_des()
{
    choose_des=ui->des_lineEdit->text();
    //qDebug()<<choose_des;
}

void MyMain_win::save_choose_preferchoice()
{
   PreferChoice=ui->PreferChoice_comboBox->currentIndex();
   //qDebug()<<PreferChoice;
}
void MyMain_win::save_choose_month()
{
    choose_month=ui->month_comboBox->currentText();
    dayN=day[ui->month_comboBox->currentIndex()];
    dayList.clear();
    QString tmpday;
    for(int i=1;i<=dayN;++i){
        tmpday=QString::number(i,10);
        dayList<<tmpday;
    }
    ui->day_comboBox->clear();
    ui->day_comboBox->addItems(dayList);
    //qDebug()<<choose_month;
}
void MyMain_win::save_choose_day()
{
    choose_day=ui->day_comboBox->currentText();
    //qDebug()<<choose_day;
}
void MyMain_win::save_choose_hour()
{
    choose_hour=ui->hour_comboBox->currentText();
    //qDebug()<<choose_day;
}
void MyMain_win::save_choose_min()
{
    choose_min=ui->min_comboBox->currentText();
    //qDebug()<<choose_day;
}

void MyMain_win::on_Check_pushButton_clicked()
{
    ALGraph a;
    struct Time tmpSt(choose_month.toInt(),choose_day.toInt(),choose_hour.toInt(),choose_min.toInt());
    if(PreferChoice==0){//耗时短
        a.printLeastTimePath(ui->PathChoose_Table,choose_src.toStdString(),choose_des.toStdString(),tmpSt.getTotalMinute());
    }else if (PreferChoice==1){ //花费少
        a.printLeastMoneyPath(ui->PathChoose_Table,choose_src.toStdString(),choose_des.toStdString(),tmpSt.getTotalMinute());
    }else if(PreferChoice==2){//中转少
        a.printLeastTransferPath(ui->PathChoose_Table,choose_src.toStdString(),choose_des.toStdString(),tmpSt.getTotalMinute());
    }
}


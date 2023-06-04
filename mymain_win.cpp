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
    //退出按钮
    connect(ui->SystemExit_pushButton,SIGNAL(&QPushButton::clicked),this,SLOT(on_SystemExit_pushButton_clicked()));
    //初始化三个按钮界面
    init_Page_PathChoose();
    init_Page_PathCheck();
    init_Page_CityCheck();
    //导入初始化城市和路径
    Train_graph.addCityFromFile("./train_city.txt");
    Train_graph.addLineFromFile("./train_line.txt");
    Plane_graph.addCityFromFile("./plane_city.txt");
    Plane_graph.addLineFromFile("./plane_line.txt");
//    Train_graph.addCityFromFile("D:\\App\\Qt\\project\\TrafficManagement\\train_city.txt");
//    Train_graph.addLineFromFile("D:\\App\\Qt\\project\\TrafficManagement\\train_line.txt");
//    Plane_graph.addCityFromFile("D:\\App\\Qt\\project\\TrafficManagement\\plane_city.txt");
//    Plane_graph.addLineFromFile("D:\\App\\Qt\\project\\TrafficManagement\\plane_line.txt");
    //初始化中转时间
    Train_graph.Transit_time = 60;

    Plane_graph.Transit_time = 120;


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

    //初始化变量
    PreferChoice = 0;
    choose_transportation = "飞机";

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

    //结果显示Label初始化
    ui->PathCheckReslabel->setText("该路线 共中转 0 次，总用时：0 天 0 小时 0 分，总花费 ：0 元");

}
void MyMain_win::init_Page_PathCheck(){

    //初始化选择查看方式
        //按钮初始化,绑定信号和槽函数
    PathCheckGroupButton=new QButtonGroup(this);
    PathCheckGroupButton->addButton(ui->PlaneLineSearch_radioButton,0);
    PathCheckGroupButton->addButton(ui->TrainLineSearch_radioButton,1);
    //ui->Choose_Plane_radioButton->setChecked(true);//默认查看飞机航班
    //connect(ui->SearchPath_pushButton,SIGNAL(&QPushButton::click),this,SLOT(on_SearchPath_pushButton_clicked()));//这里的信号不能用SIGNAL(click(bool)),这样会同时执行两次槽函数
    connect(ui->PlaneLineSearch_radioButton,SIGNAL(&QPushButton::click),this,SLOT(on_PlaneLineSearch_radioButton_clicked()));
    connect(ui->TrainLineSearch_radioButton,SIGNAL(&QPushButton::click),this,SLOT(on_TrainLineSearch_radioButton_clicked()));

    //查看表格初始化
    ui->PathCheck_Table->setColumnCount(6);
        //表格表头：车次，起始站，终点站，出发时间，到站时间，耗时,花销
    QStringList tmpheader;
    tmpheader<<"班次"<<"起始站"<<"终点站"<<"出发时间"<<"到达时间"<<"旅费";
    ui->PathCheck_Table->setHorizontalHeaderLabels(tmpheader);
    ui->PathCheck_Table->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->PathCheck_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
    ui->PathCheck_Table->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    ui->PathCheck_Table->verticalHeader()->setVisible(true);   //隐藏列表头

}

void MyMain_win::init_Page_CityCheck(){
    //查看表格初始化
    ui->CityCheck_Table->setColumnCount(1);
        //表格表头：城市名
    QStringList tmpheader;
    tmpheader<<"城市名";
    ui->CityCheck_Table->setHorizontalHeaderLabels(tmpheader);
    ui->CityCheck_Table->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->CityCheck_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
    ui->CityCheck_Table->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    ui->CityCheck_Table->verticalHeader()->setVisible(true);   //隐藏列表头



    //初始化按钮
    connect(ui->CityPlane_radioButton,SIGNAL(&QPushButton::click),this,SLOT(on_CityPlane_radioButton_clicked()));
    connect(ui->CityTrain_radioButton,SIGNAL(&QPushButton::click),this,SLOT(on_CityTrain_radioButton_clicked()));
    connect(ui->City_Add_pushButton,SIGNAL(&QPushButton::click),this,SLOT(on_City_Add_pushButton_clicked()));
    connect(ui->City_Del_pushButton,SIGNAL(&QPushButton::click),this,SLOT(on_City_Del_pushButton_clicked()));
}

void MyMain_win::on_SystemExit_pushButton_clicked()
{
    Plane_graph.saveCity("./Plane_city.txt");
    Plane_graph.saveLine("./Plane_line.txt");
    Train_graph.saveCity("./train_city.txt");
    Train_graph.saveLine("./train_line.txt");
    this->close();
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

//页面pathCheck:查询路径函数
void MyMain_win::on_Check_pushButton_clicked()
{


    struct Time tmpSt(choose_month.toInt(),choose_day.toInt(),choose_hour.toInt(),choose_min.toInt());
    if( choose_transportation == "火车"){
        if(PreferChoice==0){//耗时短
            Train_graph.printLeastTimePath(ui->PathChoose_Table,ui->PathCheckReslabel,choose_src.toStdString(),choose_des.toStdString(),tmpSt.getTotalMinute());
        }else if (PreferChoice==1){ //花费少
            Train_graph.printLeastMoneyPath(ui->PathChoose_Table,ui->PathCheckReslabel,choose_src.toStdString(),choose_des.toStdString(),tmpSt.getTotalMinute());
        }else if(PreferChoice==2){//中转少
            Train_graph.printLeastTransferPath(ui->PathChoose_Table,ui->PathCheckReslabel,choose_src.toStdString(),choose_des.toStdString(),tmpSt.getTotalMinute());
        }
    }
    else{
        if(PreferChoice==0){//耗时短
            Plane_graph.printLeastTimePath(ui->PathChoose_Table,ui->PathCheckReslabel,choose_src.toStdString(),choose_des.toStdString(),tmpSt.getTotalMinute());
        }else if (PreferChoice==1){ //花费少
            Plane_graph.printLeastMoneyPath(ui->PathChoose_Table,ui->PathCheckReslabel,choose_src.toStdString(),choose_des.toStdString(),tmpSt.getTotalMinute());
        }else if(PreferChoice==2){//中转少
            Plane_graph.printLeastTransferPath(ui->PathChoose_Table,ui->PathCheckReslabel,choose_src.toStdString(),choose_des.toStdString(),tmpSt.getTotalMinute());
        }
    }
}

void MyMain_win::on_PlaneLineSearch_radioButton_clicked()
{
    Plane_graph.showAllLine(ui->PathCheck_Table);
}


void MyMain_win::on_TrainLineSearch_radioButton_clicked()
{
    Train_graph.showAllLine(ui->PathCheck_Table);
}

void MyMain_win::receivePathInf(LineNode tmpPath){
    if(tmpPath.vehicle=="飞机"){
        Plane_graph.addLine(tmpPath);
    }else if(tmpPath.vehicle=="火车"){
        Train_graph.addLine(tmpPath);
    }
}
void MyMain_win::receivePathMdyInf(struct LineNode tmpPath){
    if(tmpPath.vehicle=="飞机"){
        Plane_graph.addLine(tmpPath);
    }else if(tmpPath.vehicle=="火车"){
        Train_graph.addLine(tmpPath);
    }
    //ui->PathCheck_Table->removeRow(del_line);
}
void MyMain_win::receiveIsMdy(bool flag){
    IsPathMdy=flag;
}
void MyMain_win::on_PathCheck_Add_pushButton_clicked()
{
    PathAdd *v;
    v=new PathAdd();
    v->show();
    connect(v,SIGNAL(sendPathInf(LineNode)),this,SLOT(receivePathInf(LineNode)));
}
void MyMain_win::on_PathCheck_Del_pushButton_clicked()
{
    QList<QTableWidgetItem*>tmpitems=ui->PathCheck_Table->selectedItems();
    if(!tmpitems.empty()){
        //qDebug()<<"选中了第"<<ui->CityCheck_Table->currentRow()<<"行";
        int tmprow=ui->PathCheck_Table->currentRow();
        QTableWidgetItem *tmpitem=tmpitems.at(0);
        QString tmpLineNum=tmpitem->text();
        if(ui->TrainLineSearch_radioButton->isChecked()){
            //qDebug()<<"火车的班次为"<<tmpLineNum;
            Train_graph.delLine(tmpLineNum.toStdString());
        }else if(ui->PlaneLineSearch_radioButton->isChecked()){
            //qDebug()<<"飞机的班次为"<<tmpLineNum;
            Plane_graph.delLine(tmpLineNum.toStdString());
        }
        ui->PathCheck_Table->removeRow(tmprow);

    }else{
        QMessageBox::critical(ui->CityCheck_Table,"错误","不存在对应数据,请先选择城市！");
    }
}
void MyMain_win::on_PathCheck_Mdy_pushButton_clicked()
{
    QList<QTableWidgetItem*>tmpitems=ui->PathCheck_Table->selectedItems();
    if(!tmpitems.empty()){
        //qDebug()<<"选中了第"<<ui->CityCheck_Table->currentRow()<<"行";
        int tmprow=ui->PathCheck_Table->currentRow();
        QTableWidgetItem *tmpitem=tmpitems.at(0);
        QString tmpLineNum=tmpitem->text();


        PathModify *v;
        v=new PathModify();
        v->show();
        connect(v,SIGNAL(sendPathMdyInf(LineNode)),this,SLOT(receivePathMdyInf(LineNode)));
        connect(v,SIGNAL(sendIsMdy(bool)),this,SLOT(receiveIsMdy(bool)));
        if(IsPathMdy){
            if(ui->TrainLineSearch_radioButton->isChecked()){
                //qDebug()<<"火车的班次为"<<tmpLineNum;
                Train_graph.delLine(tmpLineNum.toStdString());

            }else if(ui->PlaneLineSearch_radioButton->isChecked()){
                //qDebug()<<"飞机的班次为"<<tmpLineNum;
                Plane_graph.delLine(tmpLineNum.toStdString());
            }
        }

    }else{
        QMessageBox::critical(ui->CityCheck_Table,"错误","不存在对应数据,请先选择城市！");
    }
}
void MyMain_win::on_CityPlane_radioButton_clicked()
{
    Plane_graph.showAllCity(ui->CityCheck_Table);
}


void MyMain_win::on_CityTrain_radioButton_clicked()
{
    Train_graph.showAllCity(ui->CityCheck_Table);
}


void MyMain_win::receiveCityInf(std::string Transportation , std::string CityName){
    if(Transportation=="飞机")Plane_graph.addCity(CityName);
    else if(Transportation=="火车")Train_graph.addCity(CityName);
}

void MyMain_win::on_City_Add_pushButton_clicked()
{
    CityEdit *v;
    v=new CityEdit();
    v->show();
    connect(v,SIGNAL(sendCityInf(std::string,std::string)),this,SLOT(receiveCityInf(std::string,std::string)));
}

void MyMain_win::on_City_Del_pushButton_clicked()
{
    QList<QTableWidgetItem*>tmpitems=ui->CityCheck_Table->selectedItems();
    if(!tmpitems.empty()){
        //qDebug()<<"选中了第"<<ui->CityCheck_Table->currentRow()<<"行";

        int tmprow=ui->CityCheck_Table->currentRow();
        QTableWidgetItem *tmpitem=tmpitems.at(0);
        QString tmpCityName=tmpitem->text();
        if(ui->CityTrain_radioButton->isChecked()){
            Train_graph.delCity(tmpCityName.toStdString());

        }else if(ui->CityPlane_radioButton->isChecked()){
            Plane_graph.delCity(tmpCityName.toStdString());
        }
        ui->CityCheck_Table->removeRow(tmprow);

    }else{
        QMessageBox::critical(ui->CityCheck_Table,"错误","不存在对应数据,请先选择城市！");
    }

}

#include "cityedit.h"
#include "ui_cityedit.h"

CityEdit::CityEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CityEdit)
{
    ui->setupUi(this);
    //交通工具选择
    ui->Trans_comboBox->addItem("飞机");
    ui->Trans_comboBox->addItem("火车");
}

CityEdit::~CityEdit()
{
    delete ui;
}

void CityEdit::on_CityEdit_Confirm_pushButton_clicked()
{
    QString Transportation, CityName;
    Transportation=ui->Trans_comboBox->currentText();
    CityName=ui->CityName_lineEdit->text();
    emit sendCityInf(Transportation.toStdString(),  CityName.toStdString());
    this->close();
}


void CityEdit::on_CityEdit_Exit_pushButton_clicked()
{
    this->close();
}


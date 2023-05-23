#include "cityedit.h"
#include "ui_cityedit.h"

CityEdit::CityEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CityEdit)
{
    ui->setupUi(this);
}

CityEdit::~CityEdit()
{
    delete ui;
}

void CityEdit::on_CityEdit_Confirm_pushButton_clicked()
{
    QString CityName;
    int dis;
    CityName=ui->CityName_lineEdit->text();
    emit sendCityInf(CityName.toStdString());
    this->close();
}


void CityEdit::on_CityEdit_Exit_pushButton_clicked()
{
    this->close();
}


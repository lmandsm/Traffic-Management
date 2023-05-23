#include "pathedit.h"
#include "ui_pathedit.h"

PathEdit::PathEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathEdit)
{
    ui->setupUi(this);
}

PathEdit::~PathEdit()
{
    delete ui;
}

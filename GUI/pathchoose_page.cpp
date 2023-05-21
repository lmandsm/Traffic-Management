#include "pathchoose_page.h"
#include "ui_pathchoose_page.h"

PathChoose_page::PathChoose_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathChoose_page)
{
    ui->setupUi(this);
}

PathChoose_page::~PathChoose_page()
{
    delete ui;
}

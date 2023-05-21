#ifndef PATHCHOOSE_PAGE_H
#define PATHCHOOSE_PAGE_H

#include <QWidget>
#include"ui_pathchoose_page.h"
namespace Ui {
class PathChoose_page;
}

class PathChoose_page : public QWidget
{
    Q_OBJECT

public:
    explicit PathChoose_page(QWidget *parent = nullptr);
    ~PathChoose_page();

private:
    Ui::PathChoose_page *ui;
};

#endif // PATHCHOOSE_PAGE_H

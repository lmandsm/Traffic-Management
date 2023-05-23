#ifndef PATHEDIT_H
#define PATHEDIT_H

#include <QWidget>

namespace Ui {
class PathEdit;
}

class PathEdit : public QWidget
{
    Q_OBJECT

public:
    explicit PathEdit(QWidget *parent = nullptr);
    ~PathEdit();

private:
    Ui::PathEdit *ui;
};

#endif // PATHEDIT_H

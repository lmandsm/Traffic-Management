#pragma execution_character_set("utf-8")
#ifndef CITYEDIT_H
#define CITYEDIT_H

#include <QWidget>
#include<string>
namespace Ui {
class CityEdit;
}

class CityEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CityEdit(QWidget *parent = nullptr);
    ~CityEdit();

private slots:
    void on_CityEdit_Confirm_pushButton_clicked();

    void on_CityEdit_Exit_pushButton_clicked();

signals:
    void sendCityInf(std::string ,std::string);
private:
    Ui::CityEdit *ui;
};

#endif // CITYEDIT_H

#include "mymain_win.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMain_win w;
    w.show();
    return a.exec();
}

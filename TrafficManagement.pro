QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ALGraph.cpp \
    cityedit.cpp \
    main.cpp \
    mymain_win.cpp \
    pathadd.cpp

HEADERS += \
    ALGraph.h \
    C:/Users/laomahecx/Documents/Tencent Files/1759440214/FileRecv/ALGraph.h \
    cityedit.h \
    mymain_win.h \
    pathadd.h

FORMS += \
    cityedit.ui \
    mymain_win.ui \
    pathadd.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
#//避免中文乱码
#win32-msvc* {
#    QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
#}

DISTFILES += \
    plane_city.txt \
    plane_line.txt \
    train_city.txt \
    train_line.txt

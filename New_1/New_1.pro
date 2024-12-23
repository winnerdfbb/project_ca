QT       += core gui

#自行加入的
#//表示操作word.excel的
CONFIG += qaxcontainer
#//操作数据库的
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calculate.cpp \
    main.cpp \
    mainwindow.cpp \
    start.cpp

HEADERS += \
    calculate.h \
    mainwindow.h \
    start.h

FORMS += \
    calculate.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

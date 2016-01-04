#-------------------------------------------------
#
# Project created by QtCreator 2016-01-01T13:57:24
#
#-------------------------------------------------

QT       += core gui\
            network \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myPlayer
TEMPLATE = app

QMAKE_INFO_PLIST = /Users/chencong/project/qt5/myPlayer/Info.plist

SOURCES += main.cpp\
        mainwindow.cpp \
    requests.cpp

HEADERS  += mainwindow.h \
    requests.h

FORMS    += mainwindow.ui


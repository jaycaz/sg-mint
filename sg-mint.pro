#-------------------------------------------------
#
# Project created by QtCreator 2013-12-24T15:56:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sg-mint
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    BaseEditor.cpp \
    GridAxisItem.cpp

HEADERS  += MainWindow.h \
    BaseEditor.h \
    GridAxisItem.h

FORMS    += MainWindow.ui \
    BaseEditor.ui

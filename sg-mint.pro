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
    GridAxisItem.cpp \
    GrammarShape.cpp \
    ShapeEditor.cpp

HEADERS  += MainWindow.h \
    BaseEditor.h \
    GridAxisItem.h \
    GrammarShape.h \
    ShapeEditor.h

FORMS    += MainWindow.ui \
    BaseEditor.ui \
    ShapeEditor.ui

RESOURCES += \
    resources/icons/editor-icons.qrc

OTHER_FILES +=

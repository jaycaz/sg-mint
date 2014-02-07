#-------------------------------------------------
#
# Project created by QtCreator 2013-12-24T15:56:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sg-mint
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        MainWindow.cpp \
    GridAxisItem.cpp \
    GrammarShape.cpp \
    ShapeEditor.cpp \
    EditorArea.cpp \
    EditorUtils.cpp \
    DragHandle.cpp

HEADERS  += MainWindow.h \
    GridAxisItem.h \
    GrammarShape.h \
    ShapeEditor.h \
    EditorArea.h \
    EditorUtils.h \
    DragHandle.h

FORMS    += MainWindow.ui \
    ShapeEditor.ui

RESOURCES += \
    resources/icons/editor-icons.qrc

OTHER_FILES +=

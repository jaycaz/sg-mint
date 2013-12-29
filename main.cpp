#include "MainWindow.h"
#include "BaseEditor.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BaseEditor e;
    e.show();

    return a.exec();
}

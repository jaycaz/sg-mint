#include "MainWindow.h"
#include <QApplication>

// Delete later
#include "ShapeEditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ShapeEditor editor;
    editor.show();

    return a.exec();
}

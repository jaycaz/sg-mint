#ifndef BASEEDITOR_H
#define BASEEDITOR_H

#include <QWidget>
#include "GridAxisItem.h"

namespace Ui {
class BaseEditor;
}

class BaseEditor : public QWidget
{
    Q_OBJECT

public:
    explicit BaseEditor(QWidget *parent = 0);
    ~BaseEditor();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::BaseEditor *ui;
    GridAxisItem *grid;

    void RedrawGrid();
};

#endif // BASEEDITOR_H

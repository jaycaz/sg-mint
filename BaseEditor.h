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
    //QGraphicsScene *getScene();
    void addItem(QGraphicsItem *item);

    // Map to/from Cartesian coordinate system centered at axis origin

    //QPointF MapFromCart(QPointF cartPoint); // TODO
    //QPointF MapToCart(QPointF viewPoint); // TODO
    ~BaseEditor();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::BaseEditor *ui;
    GridAxisItem *grid;

    void RedrawGrid();
};

#endif // BASEEDITOR_H

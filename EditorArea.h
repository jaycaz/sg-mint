#ifndef EDITORAREA_H
#define EDITORAREA_H

#include <QGraphicsView>
#include <QMouseEvent>

#include "GridAxisItem.h"

class EditorArea : public QGraphicsView
{
    Q_OBJECT
public:
    explicit EditorArea(QWidget *parent = 0);

    void addItem(QGraphicsItem *item);

    // Map to/from Cartesian coordinate system centered at axis origin

    //QPointF MapFromCart(QPointF cartPoint); // TODO
    //QPointF MapToCart(QPointF viewPoint); // TODO
    ~EditorArea();

protected:
//    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);

private:
    GridAxisItem *grid;

    void InitGrid();

};

#endif // EDITORAREA_H

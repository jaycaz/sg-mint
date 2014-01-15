#ifndef EDITORAREA_H
#define EDITORAREA_H

#include <QGraphicsView>
#include <QMouseEvent>

#include "GridAxisItem.h"

/**
 * @brief Controller layer for ShapeEditor and RuleEditor objects
 */
class EditorArea : public QGraphicsView
{
    Q_OBJECT
public:
    explicit EditorArea(QWidget *parent = 0);
    ~EditorArea();

    /**
     * @brief Add any QGraphicsItem to the scene of the EditorArea
     * @param item
     */
    void addItem(QGraphicsItem *item);

    // Map to/from Cartesian coordinate system centered at axis origin
    //QPointF MapFromCart(QPointF cartPoint); // TODO
    //QPointF MapToCart(QPointF viewPoint); // TODO

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    GridAxisItem *grid;

    void InitGrid();

};

#endif // EDITORAREA_H

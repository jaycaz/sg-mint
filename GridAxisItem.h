#ifndef GRIDAXISITEM_H
#define GRIDAXISITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QWidget>

/**
 * @brief Used to control the display of the grid and axis in an EditorArea canvas
 */
class GridAxisItem : public QGraphicsItem
{
public:
    /**
     * @param parent Parent widget GridAxisItem will be embedded in,
     * item will expand to fill parent widget
     */
//    GridAxisItem(QWidget *parent)
//    {
//        this->parent = parent;
//    }

    GridAxisItem()
    {
        parent = NULL;
    }

    GridAxisItem(QGraphicsScene *scene)
    {
        parent = scene;

    }

    GridAxisItem(QGraphicsView *view)
    {
        this->view = view;
    }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:

    //QWidget *parent;
    QGraphicsScene *parent;
    QGraphicsView *view;

    static const int PADDING = 5;
    static const int ARROW_LENGTH = 6;
    static const int ARROW_WIDTH = 4;
    static const int DOT_RADIUS = 1;
    static const int DOT_SPACING = 10;

};

#endif // GRIDAXISITEM_H

#ifndef GRIDAXISITEM_H
#define GRIDAXISITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>

/**
 * @brief Used to control the display of the grid and axis in an EditorArea canvas
 */
class GridAxisItem : public QGraphicsItem
{
private:

    QWidget *parent;

    static const int ARROW_LENGTH = 6;
    static const int ARROW_WIDTH = 4;
    static const int DOT_RADIUS = 1;
    static const int DOT_SPACING = 10;

public:
    /**
     * @param parent Parent widget GridAxisItem will be embedded in,
     * item will expand to fill parent widget
     */
    GridAxisItem(QWidget *parent)
    {
        this->parent = parent;
    }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
};

#endif // GRIDAXISITEM_H

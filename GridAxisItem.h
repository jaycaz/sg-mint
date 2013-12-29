#ifndef GRIDAXISITEM_H
#define GRIDAXISITEM_H

#include <QGraphicsItem>
#include <QPainter>

class GridAxisItem : public QGraphicsItem
{
private:

    int parentWidth;
    int parentHeight;

    static const int ARROW_LENGTH = 6;
    static const int ARROW_WIDTH = 4;
    static const int DOT_RADIUS = 1;
    static const int DOT_SPACING = 10;

public:
    GridAxisItem(int pWidth, int pHeight)
        : parentWidth(pWidth), parentHeight(pHeight)
    {}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
};

#endif // GRIDAXISITEM_H

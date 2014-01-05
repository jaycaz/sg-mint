#ifndef GRIDAXISITEM_H
#define GRIDAXISITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>

class GridAxisItem : public QGraphicsItem
{
private:

    //qreal parentWidth;
    //qreal parentHeight;
    QWidget *parent;

    static const int ARROW_LENGTH = 6;
    static const int ARROW_WIDTH = 4;
    static const int DOT_RADIUS = 1;
    static const int DOT_SPACING = 10;

public:
    GridAxisItem(QWidget *parent)
    {
        this->parent = parent;
        //parentWidth = parent->width();
        //parentHeight = parent->height();

        //QObject::connect(parent, QWidget::resize, this, setSize)
    }

//    GridAxisItem(QSize parentSize)
//        : parentWidth(parentSize.width()), parentHeight(parentSize.height())
//    {}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

public slots:
    void setSize(QSize newSize);
};

#endif // GRIDAXISITEM_H

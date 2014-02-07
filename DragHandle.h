#ifndef DRAGHANDLE_H
#define DRAGHANDLE_H

#include <QGraphicsSceneEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

#include "EditorUtils.h"

class DragHandle : public QGraphicsItem
{
public:
    DragHandle(QGraphicsItem *item, const QPointF &pos, int index);

    QGraphicsItem* item() { return _item; }
    int index() { return _index; }

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QGraphicsItem* _item;
    int _index;

    static const int DRAG_HANDLE_RADIUS = 3;
};

#endif // DRAGHANDLE_H

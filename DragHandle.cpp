#include "DragHandle.h"

DragHandle::DragHandle(QGraphicsItem *item, const QPointF &pos, int index)
{
    _item = item;
    _index = index;
    setPos(pos);
    qDebug() << "Added handle at " << pos << endl;
    qDebug() << "mapFromParent(pos()): " << mapFromParent(this->pos()) << endl;
    qDebug() << "mapToParent(pos()): " << mapToParent(this->pos()) << endl;
    qDebug() << "mapFromScene(pos()): " << mapFromScene(this->pos()) << endl;
    qDebug() << "mapToScene(pos()): " << mapToScene(this->pos()) << endl;
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

void DragHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QColor(Qt::black)));
    painter->drawEllipse(mapFromParent(pos()), DRAG_HANDLE_RADIUS, DRAG_HANDLE_RADIUS);
}

QRectF DragHandle::boundingRect() const
{
    return QRectF(mapFromParent(pos()), QSizeF(DRAG_HANDLE_RADIUS * 2, DRAG_HANDLE_RADIUS * 2));
}

void DragHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);

    qDebug() << "Handle moved to: " << event->pos() << endl;

    // Calculate movement difference and apply it
    qreal dx = event->pos().x() - event->lastPos().x();
    qreal dy = event->pos().y() - event->lastPos().y();

    QPointF oldPos = pos();
    moveBy(dx, dy);
    QPointF newPos = pos();

    qDebug() << "Handle moved from " << oldPos <<
                " to " << newPos << endl;

    //QGraphicsItem *item = item();
    if(_item == NULL)
    {
        return;
    }

    // Identify item type and point index, and move item vertex to mouse position
    switch(_item->type())
    {
        case EditorUtils::GraphicsItemType::LINE:
        {
            auto *lineItem = dynamic_cast<QGraphicsLineItem*>(_item);
            if(lineItem == NULL)
            {
                qDebug() << "Error: failed cast from QGraphicsItem to " <<
                            "QGraphicsLineItem in EditorArea::onMoveDragHandle()" <<
                            endl;
                break;
            }
            int pointIndex = _index;
            QLineF line = lineItem->line();
            QPointF newPoint;
            if(pointIndex == 0)
            {
                newPoint = line.p1();
                newPoint.setX(newPoint.x() + dx);
                newPoint.setY(newPoint.y() + dy);
                line.setP1(newPoint);
//                line.setP1(event->pos());
            }
            else if(pointIndex == 1)
            {
                newPoint = line.p2();
                newPoint.setX(newPoint.x() + dx);
                newPoint.setY(newPoint.y() + dy);
                line.setP2(newPoint);
//                line.setP2(event->pos());
            }
            else
            {
                qDebug() << "Error: improper point index (" << pointIndex <<
                            ") for line item in EditorArea::onMoveDragHandle()" <<
                            endl;
                break;
            }

            lineItem->setLine(line);

            break;
        }

        case EditorUtils::GraphicsItemType::POLYGON:
        {

            break;
        }

        default:
        break;
    }
    update();

}

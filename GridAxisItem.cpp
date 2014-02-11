#include "GridAxisItem.h"

GridAxisItem::GridAxisItem(QGraphicsView *view)
{
    this->view = view;
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setZValue(-1);
}

QRectF GridAxisItem::boundingRect() const
{
    //return QRectF(0, 0, view->width() - PADDING, view->height() - PADDING);
    //QRectF r = view->sceneRect();
    return view->sceneRect();
}

void GridAxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    //painter->drawText(boundingRect(), "This is the grid", QTextOption(Qt::AlignRight));
//    int parentWidth = view->width();
//    int parentHeight = view->height();
    QRectF scene = view->sceneRect();
    int parentWidth = scene.width();
    int parentHeight = scene.height();
    int parentLeft = scene.x();
    int parentTop = scene.y();
    int gridLeft = scene.x() + PADDING;
    int gridTop = scene.y() + PADDING;
    int gridWidth = scene.width() - (2 * PADDING);
    int gridHeight = scene.height() - (2 * PADDING);
    int gridRight = gridLeft + gridWidth;
    int gridBottom = gridTop + gridHeight;
    int gridWMid = gridLeft + (gridWidth / 2);
    int gridHMid = gridTop + (gridHeight / 2);

    QPen axisPen;
    QColor axisColor(80, 80, 80);
    axisPen.setWidth(2);
    axisPen.setColor(axisColor);
    painter->setRenderHint(QPainter::Antialiasing);

    QPen dotPen(axisPen);
    dotPen.setWidth(1);
    dotPen.setColor(QColor(50, 50, 50, 100));

    // Draw axis lines
    painter->setPen(axisPen);
    painter->setBrush(axisColor);
    painter->drawLine(gridLeft + ARROW_LENGTH, gridHMid, gridRight - ARROW_LENGTH, gridHMid);
    painter->drawLine(gridWMid, gridTop + ARROW_LENGTH, gridWMid, gridBottom - ARROW_LENGTH);

    // Draw axis arrows
    QVector<QPoint> topArrowPoints;
    topArrowPoints.push_back(QPoint(gridWMid, gridTop));
    topArrowPoints.push_back(QPoint((gridWMid) + (ARROW_WIDTH / 2), gridTop + ARROW_LENGTH));
    topArrowPoints.push_back(QPoint((gridWMid) - (ARROW_WIDTH / 2), gridTop + ARROW_LENGTH));
    QPolygon topArrow(topArrowPoints);
    painter->drawPolygon(topArrow);

    QVector<QPoint> leftArrowPoints;
    leftArrowPoints.push_back(QPoint(gridLeft, gridHMid));
    leftArrowPoints.push_back(QPoint(gridLeft + ARROW_LENGTH, (gridHMid) - (ARROW_WIDTH / 2)));
    leftArrowPoints.push_back(QPoint(gridLeft + ARROW_LENGTH, (gridHMid) + (ARROW_WIDTH / 2)));
    QPolygon leftArrow(leftArrowPoints);
    painter->drawPolygon(leftArrow);

    QVector<QPoint> rightArrowPoints;
    rightArrowPoints.push_back(QPoint(gridRight, gridHMid));
    rightArrowPoints.push_back(QPoint(gridRight - ARROW_LENGTH, (gridHMid) - (ARROW_WIDTH / 2)));
    rightArrowPoints.push_back(QPoint(gridRight - ARROW_LENGTH, (gridHMid) + (ARROW_WIDTH / 2)));
    QPolygon rightArrow(rightArrowPoints);
    painter->drawPolygon(rightArrow);

    QVector<QPoint> botArrowPoints;
    botArrowPoints.push_back(QPoint(gridWMid, gridBottom));
    botArrowPoints.push_back(QPoint((gridWMid) + (ARROW_WIDTH / 2), gridBottom - ARROW_LENGTH));
    botArrowPoints.push_back(QPoint((gridWMid) - (ARROW_WIDTH / 2), gridBottom - ARROW_LENGTH));
    QPolygon botArrow(botArrowPoints);
    painter->drawPolygon(botArrow);

    // Draw grid dots
    painter->setPen(dotPen);
    for(int i = gridWMid % DOT_SPACING; i <= gridRight; i += DOT_SPACING)
    {
        for(int j = gridHMid % DOT_SPACING; j <= gridBottom; j += DOT_SPACING)
        {
            if(i >= gridLeft && j >= gridTop && i != gridLeft + (gridWidth / 2) && j != gridTop + (gridHeight / 2))
            {
                painter->drawEllipse(QPoint(i, j), DOT_SIZE, DOT_SIZE);
            }
        }
    }
}

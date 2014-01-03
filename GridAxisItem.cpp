#include "GridAxisItem.h"

QRectF GridAxisItem::boundingRect() const
{
    return QRectF(0, 0, parentWidth, parentHeight);
}

void GridAxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    //painter->drawText(boundingRect(), "This is the grid", QTextOption(Qt::AlignRight));

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
    painter->drawLine(ARROW_LENGTH, parentHeight / 2, parentWidth - ARROW_LENGTH, parentHeight / 2);
    painter->drawLine(parentWidth / 2, ARROW_LENGTH, parentWidth / 2, parentHeight - ARROW_LENGTH);

    // Draw axis arrows
    QVector<QPoint> topArrowPoints;
    topArrowPoints.push_back(QPoint(parentWidth / 2, 0));
    topArrowPoints.push_back(QPoint((parentWidth / 2) + (ARROW_WIDTH / 2), ARROW_LENGTH));
    topArrowPoints.push_back(QPoint((parentWidth / 2) - (ARROW_WIDTH / 2), ARROW_LENGTH));
    QPolygon topArrow(topArrowPoints);
    painter->drawPolygon(topArrow);

    QVector<QPoint> leftArrowPoints;
    leftArrowPoints.push_back(QPoint(0, parentHeight / 2));
    leftArrowPoints.push_back(QPoint(ARROW_LENGTH, (parentHeight / 2) - (ARROW_WIDTH / 2)));
    leftArrowPoints.push_back(QPoint(ARROW_LENGTH, (parentHeight / 2) + (ARROW_WIDTH / 2)));
    QPolygon leftArrow(leftArrowPoints);
    painter->drawPolygon(leftArrow);

    QVector<QPoint> rightArrowPoints;
    rightArrowPoints.push_back(QPoint(parentWidth, parentHeight / 2));
    rightArrowPoints.push_back(QPoint(parentWidth - ARROW_LENGTH, (parentHeight / 2) - (ARROW_WIDTH / 2)));
    rightArrowPoints.push_back(QPoint(parentWidth - ARROW_LENGTH, (parentHeight / 2) + (ARROW_WIDTH / 2)));
    QPolygon rightArrow(rightArrowPoints);
    painter->drawPolygon(rightArrow);

    QVector<QPoint> botArrowPoints;
    botArrowPoints.push_back(QPoint(parentWidth / 2, parentHeight));
    botArrowPoints.push_back(QPoint((parentWidth / 2) + (ARROW_WIDTH / 2), parentHeight - ARROW_LENGTH));
    botArrowPoints.push_back(QPoint((parentWidth / 2) - (ARROW_WIDTH / 2), parentHeight - ARROW_LENGTH));
    QPolygon botArrow(botArrowPoints);
    painter->drawPolygon(botArrow);

    // Draw grid dots
    painter->setPen(dotPen);
    for(int i = (int) (parentWidth/2) % DOT_SPACING; i <= parentWidth; i += DOT_SPACING)
    {
        for(int j = (int) (parentHeight/2) % DOT_SPACING; j <= parentHeight; j += DOT_SPACING)
        {
            if(i != parentWidth/2 && j != parentHeight/2)
            {
                painter->drawEllipse(QPoint(i, j), DOT_RADIUS, DOT_RADIUS);
            }
        }
    }
}

void GridAxisItem::setSize(QSize newSize)
{
    parentWidth = newSize.width();
    parentHeight = newSize.height();
}

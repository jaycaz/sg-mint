#include "EditorArea.h"

EditorArea::EditorArea(QWidget *parent) :
    QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene();
    setScene(scene);
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //InitGrid();
    //qreal trX = grid->boundingRect().width() / 2;
    //qreal trY = grid->boundingRect().height() / 2;
    //translate(trX, trY);
    //scale(1, -1);
    QGraphicsTextItem *text = new QGraphicsTextItem("L");
    text->setX(0);
    text->setY(0);
    addItem(text);
}

EditorArea::~EditorArea()
{
    delete grid;
}

void EditorArea::addItem(QGraphicsItem *item)
{
    scene()->addItem(item);
}

void EditorArea::showEvent(QShowEvent *event)
{
//    adjustSize();
//    qreal w = scene()->width();
//    qreal h = scene()->height();
    qreal w = width();
    qreal h = height();
//    fitInView(0, 0, scene()->width(), scene()->height());
//    grid = new GridAxisItem(this);
    grid = new GridAxisItem(this);
    addItem(grid);
    repaint();
}

void EditorArea::mouseMoveEvent(QMouseEvent *event)
{
    //event->ignore();
    if(parent() != NULL)
    {
        parent()->event(static_cast<QEvent*>(event));
    }
}

void EditorArea::mousePressEvent(QMouseEvent *event)
{
    //event->ignore();
    if(parent() != NULL)
    {
        parent()->event(static_cast<QEvent*>(event));
    }
}

void EditorArea::mouseReleaseEvent(QMouseEvent *event)
{
    //event->ignore();
    if(parent() != NULL)
    {
        parent()->event(static_cast<QEvent*>(event));
    }
}

void EditorArea::InitGrid()
{
    QGraphicsScene *scene = new QGraphicsScene();
    //grid = new GridAxisItem(this);
    setScene(scene);
    //grid = new GridAxisItem(scene);
    //scene->addItem(grid);
    repaint();
}

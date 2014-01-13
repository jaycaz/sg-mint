#include "EditorArea.h"

EditorArea::EditorArea(QWidget *parent) :
    QGraphicsView(parent)
{
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    InitGrid();
}

EditorArea::~EditorArea()
{
    delete grid;
}

void EditorArea::addItem(QGraphicsItem *item)
{
    scene()->addItem(item);
}

void EditorArea::mouseMoveEvent(QMouseEvent *event)
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
    grid = new GridAxisItem(this);
    scene->addItem(grid);
    setScene(scene);
    repaint();
}

#include "EditorArea.h"
#include <QDebug>

EditorArea::EditorArea(QWidget *parent) :
    QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene();
    setScene(scene);
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setDragMode(QGraphicsView::RubberBandDrag);
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));

//    installEventFilter(parent);
}

EditorArea::~EditorArea()
{
    delete grid;
}

void EditorArea::addItemToScene(QGraphicsItem *item)
{
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene()->addItem(item);
}

void EditorArea::addPointToSelection(const QPoint &selPos)
{
    QPainterPath selPath = scene()->selectionArea();
    selPath.addEllipse(selPos, SELECT_RADIUS, SELECT_RADIUS);
    scene()->setSelectionArea(selPath, transform());

//    auto *path = new QGraphicsPathItem(selPath);
//    addItemToScene(path);
//    path->setFlag(QGraphicsItem::ItemIsSelectable, false);

    //qDebug() << "Selection: " << selArea->pos() << endl;
}

void EditorArea::clearSelection()
{
    scene()->setSelectionArea(QPainterPath(), transform());
    scene()->clearSelection();
}

void EditorArea::onSelectionChanged()
{
    for(int i = 0; i < scene()->selectedItems().size(); i++)
    {
        QGraphicsItem *item = scene()->selectedItems()[i];
        qDebug() << "Item " << i << ": type " << item->type() << endl;
    }
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
    scene()->addItem(grid);
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

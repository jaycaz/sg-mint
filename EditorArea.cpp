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

// Intended for external items (shape grammar items and so forth)
void EditorArea::addItemToScene(QGraphicsItem *item)
{
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene()->addItem(item);
}

// Intended for internal items (helper items managed by EditorArea)
void EditorArea::internalAddItemToScene(QGraphicsItem *item)
{
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
    foreach(QGraphicsItem *item, scene()->selectedItems())
    {
        removeDragHandles(item);
    }

    scene()->setSelectionArea(QPainterPath(), transform());
    scene()->clearSelection();
}

void EditorArea::onSelectionChanged()
{
    for(int i = 0; i < scene()->selectedItems().size(); i++)
    {
        QGraphicsItem *item = scene()->selectedItems()[i];
        qDebug() << "Item " << i << ": type " << item->type() << endl;

        // TODO: avoid adding duplicate handles
        addDragHandles(item);
    }
}

void EditorArea::addDragHandles(QGraphicsItem *item)
{
    QList<QPointF> points;
    switch(item->type())
    {
        case EditorUtils::GraphicsItemType::LINE:
        {
            auto *line = dynamic_cast<QGraphicsLineItem*>(item);
            if(line == NULL)
            {
                qDebug() << "Error: failed cast from QGraphicsItem to " <<
                            "QGraphicsLineItem in EditorArea::addDragHandles()" <<
                            endl;
                break;
            }

            points.push_back(line->line().p1());
            points.push_back(line->line().p2());
            break;
        }

        case EditorUtils::GraphicsItemType::POLYGON:
        {
            auto *poly = dynamic_cast<QGraphicsPolygonItem*>(item);
            if(poly == NULL)
            {
                qDebug() << "Error: failed cast from QGraphicsItem to " <<
                            "QGraphicsPolygonItem in EditorArea::addDragHandles()" <<
                            endl;
                break;
            }
            points = poly->polygon().toList();
            break;
        }

        default:
        break;
    }

    QList<QGraphicsEllipseItem*> handles;

    // Take list of points and add handle to scene
    for(int i = 0; i < points.size(); i++)
    {
        QPointF point = points[i];
        DragHandle *handle = new DragHandle(item, point, i);
//        handles.push_back(handle);
        internalAddItemToScene(handle);
        dragHandles.push_back(handle);
        //dragHandles[handle] = QPair<QGraphicsItem*, int>(item, i);
    }

//    dragHandles[item] = handles;

}

void EditorArea::removeDragHandles(QGraphicsItem *item)
{
    // Remove drag handles associated with item from scene and handle map
//    if(dragHandles.contains(item))
//    {
//        QList<QGraphicsEllipseItem*> &handles = dragHandles[item];

//        foreach(QGraphicsEllipseItem *handle, handles)
//        {
//            scene()->removeItem(handle);
//        }
//    }

    // Find all handles with item as the associated graphics item
//    foreach(QGraphicsEllipseItem* handle, dragHandles.keys())
    foreach(DragHandle* handle, dragHandles)
    {
        if(handle->item() == item)
        {
            scene()->removeItem(handle);
            dragHandles.removeAll(handle);
            delete handle;
        }
    }

}

void EditorArea::showEvent(QShowEvent *event)
{
//    adjustSize();
//    qreal w = scene()->width();
//    qreal h = scene()->height();
    qreal w = width();
    qreal h = height();
    scene()->setSceneRect(0, 0, w - SCENE_PADDING, h - SCENE_PADDING);
//    fitInView(0, 0, scene()->width(), scene()->height());
//    grid = new GridAxisItem(this);
    grid = new GridAxisItem(this);
    internalAddItemToScene(grid);
    repaint();
}

void EditorArea::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    int newWidth = std::max(width(), (int) scene()->width()) - SCENE_PADDING;
    int newHeight = std::max(height(), (int) scene()->height()) - SCENE_PADDING;
    scene()->setSceneRect(0, 0, newWidth, newHeight);
}

void EditorArea::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    //event->ignore();
    if(event->buttons() & Qt::LeftButton)
    {
        //Check if item being dragged is a drag handle
        QGraphicsItem *dragItem = scene()->itemAt(event->localPos(), transform());
        auto *handle = dynamic_cast<DragHandle*>(dragItem);

        if(handle != NULL)
        {
            onMoveDragHandle(handle, event);
        }
    }

    if(parent() != NULL)
    {
        parent()->event(static_cast<QEvent*>(event));
    }

    event->ignore();
}

void EditorArea::onMoveDragHandle(DragHandle *handle, QMouseEvent *event)
{
//    if(!dragHandles.contains(handle))
//    {
//        return;
//    }

//    // Calculate movement difference and apply it
//    QPointF oldPos = handle->pos();
//    handle->setPos(mapFromScene(event->pos()));
//    QPointF newPos = handle->pos();

//    qDebug() << "Handle moved from " << oldPos <<
//                " to " << newPos << endl;

//    QGraphicsItem *item = handle->item();
//    if(item == NULL)
//    {
//        return;
//    }

//    // Identify item type and point index, and move item vertex to mouse position
//    switch(item->type())
//    {
//        case EditorUtils::GraphicsItemType::LINE:
//        {
//            auto *lineItem = dynamic_cast<QGraphicsLineItem*>(item);
//            if(lineItem == NULL)
//            {
//                qDebug() << "Error: failed cast from QGraphicsItem to " <<
//                            "QGraphicsLineItem in EditorArea::onMoveDragHandle()" <<
//                            endl;
//                break;
//            }
//            int pointIndex = handle->index();
//            QLineF line = lineItem->line();
//            if(pointIndex == 0)
//            {
//                line.setP1(mapFromScene(event->pos()));
//            }
//            else if(pointIndex == 1)
//            {
//                line.setP2(mapFromScene(event->pos()));
//            }
//            else
//            {
//                qDebug() << "Error: improper point index (" << pointIndex <<
//                            ") for line item in EditorArea::onMoveDragHandle()" <<
//                            endl;
//                break;
//            }

//            lineItem->setLine(line);

//            break;
//        }

//        case EditorUtils::GraphicsItemType::POLYGON:
//        {

//            break;
//        }

//        default:
//        break;
//    }
//    update();
}

void EditorArea::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    //event->ignore();
    lastClickPos = mapToScene(event->pos());

    if(parent() != NULL)
    {
        parent()->event(static_cast<QEvent*>(event));
    }

    event->ignore();
}

void EditorArea::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

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

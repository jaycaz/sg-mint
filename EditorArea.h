#ifndef EDITORAREA_H
#define EDITORAREA_H

#include <QGraphicsView>
#include <QMouseEvent>

#include "DragHandle.h"
#include "EditorUtils.h"
#include "GridAxisItem.h"

/**
 * @brief Controller layer for ShapeEditor and RuleEditor objects
 */
class EditorArea : public QGraphicsView
{
    Q_OBJECT
public:
    explicit EditorArea(QWidget *parent = 0);
    ~EditorArea();

    /**
     * @brief Add any QGraphicsItem to the scene of the EditorArea
     * @param item
     */
    void addItemToScene(QGraphicsItem *item);
    void addPointToSelection(const QPoint &selPos);
    void clearSelection();
    QPointF getLastClickPos() { return lastClickPos; }

    // Map to/from Cartesian coordinate system centered at axis origin
    //QPointF MapFromCart(QPointF cartPoint); // TODO
    //QPointF MapToCart(QPointF viewPoint); // TODO

public slots:
    void onSelectionChanged();

protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void onMoveDragHandle(DragHandle *handle, QMouseEvent *event);

private:
    GridAxisItem *grid;
//    QMap<QGraphicsEllipseItem*, QPair<QGraphicsItem*, int>> dragHandles;
    QList<DragHandle*> dragHandles;
    void InitGrid();
    void addDragHandles(QGraphicsItem *item);
    void removeDragHandles(QGraphicsItem *item);
    void internalAddItemToScene(QGraphicsItem *item);
    QPointF lastClickPos;

    static const int SELECT_RADIUS = 5;
    static const int SCENE_PADDING = 5;
};

#endif // EDITORAREA_H

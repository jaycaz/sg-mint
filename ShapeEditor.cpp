#include "ShapeEditor.h"
#include "ui_ShapeEditor.h"
#include <QDebug>

ShapeEditor::ShapeEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeEditor)
{
    ui->setupUi(this);
    editorMode = SELECT;
    ui->selectButton->setChecked(true);
    addMode = NONE;
    drawingItem = NULL;
    ignoreClick = false;

    grammarShape = new GrammarShape();
    //ui->canvas->addItemToScene(&(grammarShape->items));

    // Init preview dot
    previewDot = new QGraphicsEllipseItem(
                -(PREVIEW_DOT_RADIUS / 2),
                -(PREVIEW_DOT_RADIUS / 2),
                PREVIEW_DOT_RADIUS,
                PREVIEW_DOT_RADIUS);
    previewDot->setPen(QPen(PREVIEW_DOT_COLOR));
    previewDot->setBrush(QBrush(PREVIEW_DOT_COLOR));
    previewDot->setVisible(false);
    ui->canvas->addItemToScene(previewDot);
    // Init toolbar
    //editorTools.addAction()
    update();
}

ShapeEditor::~ShapeEditor()
{
    delete previewDot;
    delete grammarShape;
    delete ui;
}

bool ShapeEditor::eventFilter(QObject *obj, QEvent *event)
{
//    if(obj != ui->canvas)
//        return false;

//    qDebug() << event->type() << endl;
//    if(event->type() == QEvent::MouseMove)
//    {
//        qDebug() << "move" << endl;
//        return true;
//    }
    return false;
}

void ShapeEditor::mouseMoveEvent(QMouseEvent* event)
{
//    QWidget::mouseMoveEvent(event);

//    if(event->buttons() & Qt::LeftButton)
//    {
        //dragMoveEvent(dynamic_cast<QGraphicsSceneDragDropEvent*>(event));
        qreal startPlaceX = ui->canvas->getLastClickPos().x();
        qreal startPlaceY = ui->canvas->getLastClickPos().y();
        switch(editorMode)
        {
            case ShapeEditor::ADD:
            switch(addMode)
            {
                case ShapeEditor::LINE:
                // Only update if mouse is left-clicked
                if(!(event->buttons() & Qt::LeftButton))
                {
                    break;
                }
                if(drawingItem != NULL)
                {
                    // Update line endpoint position
                    QGraphicsLineItem *drawingLine = dynamic_cast<QGraphicsLineItem*>(drawingItem);
                    if(drawingLine != NULL)
                    {
                        drawingLine->setLine(startPlaceX, startPlaceY, placePos.x(), placePos.y());
                    }
                }
                else
                {
                    // Create new line item
                    drawingItem = new QGraphicsLineItem(startPlaceX, startPlaceY, placePos.x(), placePos.y());
                    ui->canvas->addItemToScene(drawingItem);
                }
                break;

                case ShapeEditor::POLYGON:
                if(drawingItem != NULL)
                {
                    // Update last polygon point position
                    QGraphicsPolygonItem *drawingPoly = dynamic_cast<QGraphicsPolygonItem*>(drawingItem);
                    if(drawingPoly != NULL && drawingPoly->polygon().size() != 0)
                    {
                        QPolygonF newPoly = drawingPoly->polygon();
                        QPointF &lastPoint = newPoly.last();
                        lastPoint.setX(placePos.x());
                        lastPoint.setY(placePos.y());
                        drawingPoly->setPolygon(newPoly);
                    }
                }
                break;
            }
            break;

            case ShapeEditor::SELECT:
//            if(event->buttons() & Qt::LeftButton)
//            {

//            }
            break;
        }
    //}
    // Calculate place position based on options
    // TODO: Add snap-to-grid option
//    placePos = event->pos();
    placePos = event->localPos();

    previewDot->setPos(placePos);

    repaint();
}

void ShapeEditor::mousePressEvent(QMouseEvent *event)
{
//    QWidget::mousePressEvent(event);

//    lastClickPos = placePos;
}

void ShapeEditor::mouseReleaseEvent(QMouseEvent *event)
{
//    QWidget::mouseReleaseEvent(event);

    switch(editorMode)
    {
        case ShapeEditor::ADD:
        switch(addMode)
        {
            case ShapeEditor::LINE:
            if(drawingItem != NULL)
            {
                // Add line to grammar shape
//                grammarShape->items.addToGroup(drawingItem);
                grammarShape->items.push_back(drawingItem);
                drawingItem = NULL;
            }
            break;

            case ShapeEditor::POLYGON:
            if(ignoreClick)
            {
                // Extra click after double click; ignore
                ignoreClick = false;
                break;
            }
            if(drawingItem == NULL)
            {
                // Create new polygon item
                QPolygonF initPoly;
                initPoly << QPointF(placePos);
                initPoly << QPointF(placePos);
                QGraphicsPolygonItem *drawingPoly = new QGraphicsPolygonItem(initPoly);
                drawingItem = (QGraphicsItem*) drawingPoly;
                ui->canvas->addItemToScene(drawingItem);
            }
            else
            {
                // Add new point to polygon
                QGraphicsPolygonItem *drawingPoly = dynamic_cast<QGraphicsPolygonItem*>(drawingItem);
                if(drawingPoly != NULL)
                {
                    QPolygonF newPoly = drawingPoly->polygon() << QPointF(placePos);
                    drawingPoly->setPolygon(newPoly);
                }
            }
            break;
        }
        break;

        // Selection tool options
        case ShapeEditor::SELECT:
        QList<QGraphicsItem*> selectedItems = ui->canvas->scene()->selectedItems();
        qDebug() << "Pos: " << event->pos();

        foreach(QGraphicsItem *item, selectedItems)
        {
//            auto *line = (QGraphicsLineItem*) item;
//            if(line != NULL)
//            {
//                line->setPen(QPen(QColor(0, 0, 0)));
//            }
        }

        ui->canvas->clearSelection();
        ui->canvas->addPointToSelection(event->pos());

        // Item(s) selected, mark
        QList<QGraphicsItem*> newSelectedItems = ui->canvas->scene()->selectedItems();
        foreach(QGraphicsItem *item, newSelectedItems)
        {
//            auto *line = (QGraphicsLineItem*) item;
//            if(line != NULL)
//            {
//                line->setPen(QPen(QColor(255, 0, 0)));
//            }
        }

        break;
    }
}

void ShapeEditor::mouseDoubleClickEvent(QMouseEvent *event)
{
//    QWidget::mouseDoubleClickEvent(event);

    switch(editorMode)
    {
        case ShapeEditor::ADD:
        switch(addMode)
        {
            case ShapeEditor::POLYGON:
            if(drawingItem != NULL)
            {
                // Add polygon to grammar shape
//                grammarShape->items.addToGroup(drawingItem);
                grammarShape->items.push_back(drawingItem);
                drawingItem = NULL;
                ignoreClick = true;
            }
            break;
        }
    }
}

void ShapeEditor::on_addLineButton_toggled(bool checked)
{
    onAddButtonToggled(checked);

    if(checked)
    {
        //uncheckAllTools(ui->addLineButton);
        addMode = LINE;
    }
    else
    {
        addMode = NONE;
    }
    update();
}

void ShapeEditor::on_addPolylineButton_toggled(bool checked)
{
    onAddButtonToggled(checked);

    if(checked)
    {
        //uncheckAllTools(ui->addPolylineButton);
        addMode = POLYLINE;
    }
    else
    {
    }
    update();
}

void ShapeEditor::on_addPolygonButton_toggled(bool checked)
{
    onAddButtonToggled(checked);
    if(checked)
    {
        //uncheckAllTools(ui->addPolygonButton);
        addMode = POLYGON;
    }
    else
    {
    }
}

void ShapeEditor::onAddButtonToggled(bool checked)
{
    ignoreClick = false;
    if(checked)
    {
       ui->canvas->setDragMode(QGraphicsView::NoDrag);
       ui->canvas->setCursor(Qt::CrossCursor);
       previewDot->setVisible(true);
       editorMode = ADD;
    }
    else
    {
       ui->canvas->setCursor(Qt::ArrowCursor);
       previewDot->setVisible(false);
    }
}

void ShapeEditor::on_selectButton_toggled(bool checked)
{
    if(checked)
    {
        ui->canvas->setDragMode(QGraphicsView::RubberBandDrag);
        editorMode = SELECT;
        addMode = NONE;
    }
}

void ShapeEditor::paintEvent(QPaintEvent *e)
{
    switch(editorMode)
    {
        case ShapeEditor::ADD:
            break;

        default:
            break;
    }

}

void ShapeEditor::uncheckAllTools(QToolButton *except = NULL)
{
    int numButtons = ui->editorTools->count();
    for(int i = 0; i < numButtons; i++)
    {
        QLayoutItem *item = ui->editorTools->itemAt(i);
        QToolButton *button = dynamic_cast<QToolButton*>(item->widget());
        if(button != NULL && button != except)
        {
            button->setChecked(false);
        }
    }
}

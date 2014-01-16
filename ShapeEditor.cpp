#include "ShapeEditor.h"
#include "ui_ShapeEditor.h"

ShapeEditor::ShapeEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeEditor)
{
    ui->setupUi(this);
    editorMode = DEFAULT;
    addMode = NONE;
    drawingItem = NULL;
    ignoreClick = false;

    grammarShape = new GrammarShape();
    ui->canvas->addItem(&(grammarShape->items));

    // Init preview dot
    previewDot = new QGraphicsEllipseItem(
                -(PREVIEW_DOT_RADIUS / 2),
                -(PREVIEW_DOT_RADIUS / 2),
                PREVIEW_DOT_RADIUS,
                PREVIEW_DOT_RADIUS);
    previewDot->setPen(QPen(PREVIEW_DOT_COLOR));
    previewDot->setBrush(QBrush(PREVIEW_DOT_COLOR));
    previewDot->setVisible(false);
    ui->canvas->addItem(previewDot);

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

void ShapeEditor::mouseMoveEvent(QMouseEvent* event)
{
//    if(event->buttons() & Qt::LeftButton)
//    {
        //dragMoveEvent(dynamic_cast<QGraphicsSceneDragDropEvent*>(event));
        // Drag operations
        switch(editorMode)
        {
            case ShapeEditor::ADD:
            qreal startPlaceX = lastClickPos.x();
            qreal startPlaceY = lastClickPos.y();
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
                    ui->canvas->addItem(drawingItem);
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
        }
    //}
    // Calculate place position based on options
    // TODO: Add snap-to-grid option
    placePos = event->pos();

    previewDot->setPos(placePos);

    repaint();
}

void ShapeEditor::mousePressEvent(QMouseEvent *event)
{
    lastClickPos = placePos;
}

//void dragMoveEvent(QGraphicsSceneDragDropEvent *event)
//{
//}

void ShapeEditor::mouseReleaseEvent(QMouseEvent *event)
{
    switch(editorMode)
    {
        case ShapeEditor::ADD:
        switch(addMode)
        {
            case ShapeEditor::LINE:
            if(drawingItem != NULL)
            {
                // Add line to grammar shape
                grammarShape->items.addToGroup(drawingItem);
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
                ui->canvas->addItem(drawingItem);
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
    }
}

void ShapeEditor::mouseDoubleClickEvent(QMouseEvent *event)
{
    switch(editorMode)
    {
        case ShapeEditor::ADD:
        switch(addMode)
        {
            case ShapeEditor::POLYGON:
            if(drawingItem != NULL)
            {
                // Add polygon to grammar shape
                grammarShape->items.addToGroup(drawingItem);
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
        addMode = NONE;
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
        addMode = NONE;
    }
}

void ShapeEditor::onAddButtonToggled(bool checked)
{
    ignoreClick = false;
    if(checked)
    {
       ui->canvas->setCursor(Qt::CrossCursor);
       previewDot->setVisible(true);
       editorMode = ADD;
    }
    else
    {
       ui->canvas->setCursor(Qt::ArrowCursor);
       previewDot->setVisible(false);
       editorMode = DEFAULT;
    }
}

void ShapeEditor::paintEvent(QPaintEvent *e)
{
    switch(editorMode)
    {
        case ShapeEditor::ADD:
            break;

        case ShapeEditor::DELETE:
            break;

        case ShapeEditor::DEFAULT:
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

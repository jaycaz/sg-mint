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

    grammarShape = new GrammarShape();
    ui->canvas->addItem(&(grammarShape->items));

    previewDot = new QGraphicsEllipseItem(
                -(PREVIEW_DOT_RADIUS / 2),
                -(PREVIEW_DOT_RADIUS / 2),
                PREVIEW_DOT_RADIUS,
                PREVIEW_DOT_RADIUS);
    previewDot->setPen(QPen(PREVIEW_DOT_COLOR));
    previewDot->setBrush(QBrush(PREVIEW_DOT_COLOR));
    previewDot->setVisible(false);
    ui->canvas->addItem(previewDot);
}

ShapeEditor::~ShapeEditor()
{
    delete previewDot;
    delete grammarShape;
    delete ui;
}

void ShapeEditor::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        //dragMoveEvent(dynamic_cast<QGraphicsSceneDragDropEvent*>(event));
        // Drag operations
        switch(editorMode)
        {
            case ShapeEditor::ADD:
            switch(addMode)
            {
                case ShapeEditor::LINE:
                qreal startPlaceX = drawingItemStartPos.x();
                qreal startPlaceY = drawingItemStartPos.y();
                if(drawingItem != NULL)
                {
                    QGraphicsLineItem *drawingLine = static_cast<QGraphicsLineItem*>(drawingItem);
                    drawingLine->setLine(startPlaceX, startPlaceY, placePos.x(), placePos.y());
                    //drawingLine->line().setP2(placePos);
                }
                else
                {
                    drawingItem = new QGraphicsLineItem(startPlaceX, startPlaceY, placePos.x(), placePos.y());
                    ui->canvas->addItem(drawingItem);
                }
            }
        }
    }
    // Calculate place position based on options
    // TODO: Add snap-to-grid option
    placePos = event->pos();

    previewDot->setPos(placePos);
    repaint();
}

void ShapeEditor::mousePressEvent(QMouseEvent *event)
{
    switch(editorMode)
    {
        case ShapeEditor::ADD:
        switch(addMode)
        {
            case ShapeEditor::LINE:
            drawingItemStartPos = placePos;
            break;
        }
        break;
    }
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
                    grammarShape->items.addToGroup(drawingItem);
                    drawingItem = NULL;
                }
            break;
        }
        break;
    }
}

void ShapeEditor::on_addLineButton_toggled(bool checked)
{
   if(checked)
   {
       ui->canvas->setCursor(Qt::CrossCursor);
       previewDot->setVisible(true);
       editorMode = ADD;
       addMode = LINE;
   }
   else
   {
       ui->canvas->setCursor(Qt::ArrowCursor);
       previewDot->setVisible(false);
       editorMode = DEFAULT;
       addMode = NONE;
   }
   repaint();
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

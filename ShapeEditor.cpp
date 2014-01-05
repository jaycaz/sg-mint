#include "ShapeEditor.h"
#include "ui_ShapeEditor.h"

ShapeEditor::ShapeEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeEditor)
{
    shape = new GrammarShape();
    //previewDotPosition = NULL;
    ui->setupUi(this);
    editorMode = DEFAULT;
    addMode = NONE;

    previewDot = new QGraphicsEllipseItem(0, 0, PREVIEW_DOT_RADIUS, PREVIEW_DOT_RADIUS);
    previewDot->setPen(QPen(PREVIEW_DOT_COLOR));
    previewDot->setBrush(QBrush(PREVIEW_DOT_COLOR));
    //previewDot->setVisible(false);
    ui->canvas->addItem(previewDot);
}

ShapeEditor::~ShapeEditor()
{
    delete previewDot;
    delete shape;
    delete ui;
}

void ShapeEditor::mouseMoveEvent(QMouseEvent* event)
{
    previewDot->setPos(event->pos());
    repaint();
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

//void ShapeEditor::paintEvent(QPaintEvent *e)
//{
//    switch(editorMode)
//    {
//        case ShapeEditor::ADD:
//            break;

//        case ShapeEditor::DELETE:
//            break;

//        case ShapeEditor::DEFAULT:
//            break;

//        default:
//            break;
//    }

//}

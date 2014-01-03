#include <QPainter>
#include "BaseEditor.h"
#include "GridAxisItem.h"
#include "ui_BaseEditor.h"
#include "stdlib.h"

BaseEditor::BaseEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseEditor)
{
    ui->setupUi(this);
    grid = new GridAxisItem(size());
    RedrawGrid();
}

BaseEditor::~BaseEditor()
{
    delete grid;
    delete ui;
}

//QGraphicsScene* BaseEditor::getScene()
//{
//    return ui->canvas->scene();
//}

void BaseEditor::addItem(QGraphicsItem *item)
{
    ui->canvas->scene()->addItem(item);
}

void BaseEditor::paintEvent(QPaintEvent *)
{
    //RedrawGrid();
}

void BaseEditor::RedrawGrid()
{
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(grid);
    ui->canvas->setScene(scene);
}

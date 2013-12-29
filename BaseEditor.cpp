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
    grid = new GridAxisItem(width(), height());
    //std::cout << ui->gview->width() << std::endl << ui->gview->height() << std::endl;
}

BaseEditor::~BaseEditor()
{
    delete grid;
    delete ui;
}

void BaseEditor::paintEvent(QPaintEvent *)
{
    RedrawGrid();
}

void BaseEditor::RedrawGrid()
{
    QGraphicsScene *scene = new QGraphicsScene();
    //scene->addText("Hello Editor!", QFont("Arial", 20));
    scene->addItem(grid);
    ui->gview->setScene(scene);
}

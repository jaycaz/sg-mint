#ifndef SHAPEEDITOR_H
#define SHAPEEDITOR_H

#include <QWidget>
#include <QToolBar>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "GrammarShape.h"

namespace Ui {
class ShapeEditor;
}

class ShapeEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ShapeEditor(QWidget *parent = 0);
    ~ShapeEditor();

    enum EditorMode
    {
        ADD,
        DELETE,
        TRANSFORM,
        DEFAULT
    };

    enum AddMode
    {
        LINE,
        POLYLINE,
        POLYGON,
        NONE
    };

    EditorMode editorMode;
    AddMode addMode;

protected:
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_addLineButton_toggled(bool checked);

//protected:
//    void paintEvent(QPaintEvent *);

private:

    //QGraphicsScene *canvasScene;

    // The shape that the Shape Editor is editing
    GrammarShape *shape;

    // Toolbar object that stores all of the tool buttons
    QToolBar editorTools;

    // Preview dot displays to show where a shape component will be added
    QPointF *previewDotPosition;
    QGraphicsEllipseItem *previewDot;
    qreal PREVIEW_DOT_RADIUS = 5;
    QColor PREVIEW_DOT_COLOR = QColor(0, 0, 0, 100); // translucent black

    Ui::ShapeEditor *ui;
};

#endif // SHAPEEDITOR_H

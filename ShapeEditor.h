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

/**
 * @brief A view class for the editor used to view and update GrammarShape objects
 */
class ShapeEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ShapeEditor(QWidget *parent = 0);
    ~ShapeEditor();

    /**
     * @brief Changes depending on what tool/shape is selected
     */
    enum EditorMode
    {
        ADD,
        DELETE,
        TRANSFORM,
        DEFAULT
    };

    /**
     * @brief When ShapeEditor is in ADD mode, indicates the shape being added
     */
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
    void paintEvent(QPaintEvent *event);

private slots:
    void on_addLineButton_toggled(bool checked);

private:

    /**
     * @brief The shape model that the ShapeEditor is currently editing
     */
    GrammarShape *shape;

    /**
     * @brief Allows access to all ShapeEditor tool buttons
     */
    QToolBar editorTools;

    /**
     * @brief Displays to show where an editor tool will be applied
     */
    QGraphicsEllipseItem *previewDot;
    qreal PREVIEW_DOT_RADIUS = 5;
    QColor PREVIEW_DOT_COLOR = QColor(0, 0, 0, 100); // semi-transparent, black

    Ui::ShapeEditor *ui;
};

#endif // SHAPEEDITOR_H

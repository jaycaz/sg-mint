#ifndef SHAPEEDITOR_H
#define SHAPEEDITOR_H

#include <QWidget>
#include <QToolButton>
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
    /**
     * @brief Default constructor. Will construct a new GrammarShape item.
     */
    explicit ShapeEditor(QWidget *parent = 0);

//    /**
//     * @brief Loads targetShape for editing
//     * @param targetShape
//     */
//    explicit ShapeEditor(GrammarShape *targetShape, QWidget *parent = 0);

    ~ShapeEditor();

    /**
     * @brief Changes depending on what tool/shape is selected
     */
    enum EditorMode
    {
        ADD,
        SELECT
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
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void on_addLineButton_toggled(bool checked);

    void on_addPolylineButton_toggled(bool checked);

    void on_addPolygonButton_toggled(bool checked);

    void on_selectButton_toggled(bool checked);

private:

    /**
     * @brief The shape model that the ShapeEditor is currently editing
     */
    GrammarShape *grammarShape;

    /**
     * @brief Used to store an item currently being drawn by the user
     */
    QGraphicsItem *drawingItem;
    bool ignoreClick;

    /**
     * @brief Allows access to all ShapeEditor tool buttons
     */
    //QToolBar editorTools;

    /**
     * @brief Unchecks all buttons in shape editor tool pane
     * @param except An optional button to ignore unchecking
     */
    void uncheckAllTools(QToolButton *except);

    /**
     * @brief Common behavior for any add button
     */
    void onAddButtonToggled(bool checked);

    /**
     * @brief Displays to show where an editor tool will be applied
     */
    QGraphicsEllipseItem *previewDot;
    qreal PREVIEW_DOT_RADIUS = 5;
    QColor PREVIEW_DOT_COLOR = QColor(0, 0, 0, 100); // semi-transparent, black

    /**
     * @brief Position where item points will actually be placed.
     * Will be calculated based on snap-to-grid settings, etc.
     */
    QPointF placePos;

    Ui::ShapeEditor *ui;
};

#endif // SHAPEEDITOR_H

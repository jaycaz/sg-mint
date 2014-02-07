#ifndef EDITORUTILS_H
#define EDITORUTILS_H

/**
 * @brief A class of useful members and methods for the editors
 */
class EditorUtils
{
public:
    enum GraphicsItemType
    {
        BASE = 1,
        PATH = 2,
        RECT = 3,
        ELLIPSE = 4,
        POLYGON = 5,
        LINE = 6,
        PIXMAP = 7,
        TEXT = 8,
        SIMPLE_TEXT = 9,
        GROUP = 10
    };

    EditorUtils();
};

#endif // EDITORUTILS_H

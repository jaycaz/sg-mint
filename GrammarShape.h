#ifndef GRAMMARSHAPE_H
#define GRAMMARSHAPE_H

#include <QGraphicsItemGroup>


class GrammarShape
{
public:
    GrammarShape();
    ~GrammarShape();

//    QGraphicsItemGroup items; // Changed to list to avoid selection issue
    QList<QGraphicsItem*> items;
};

#endif // GRAMMARSHAPE_H

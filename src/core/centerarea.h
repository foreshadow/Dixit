#ifndef CENTERAREA_H
#define CENTERAREA_H

#include <QObject>
#include <QGraphicsItem>

#include "card.h"

class CenterArea : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit CenterArea(int width, int height);
    ~CenterArea();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void clear();
    void addCard(Card *card);

private:
    void reposition();

protected:
    bool dragOver;
    QRect rect;
    QList<Card *> list;

signals:
    void cardDrop(int);

public slots:
};

#endif // CENTERAREA_H

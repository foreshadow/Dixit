#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Card : public QGraphicsItem
{
public:
    explicit Card(int id, QString path);
    ~Card();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

protected:
    int id;
    QImage origin;
    QImage abbr;
    QImage *img;
};

#endif // CARD_H

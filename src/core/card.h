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
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);

    void recordPosition();
    int getId() const;

protected:
    int id;
    double z;
    QPoint p;
    QImage origin;
    QImage abbr;
    QImage *img;
};

#endif // CARD_H

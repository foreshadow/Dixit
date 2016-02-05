#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Card : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Card(int id, QString path);
    ~Card();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);

    void recordPosition();
    int getId() const;

    enum class Location
    {
        DECK_INVISIBLE,
        HAND_DRAGGABLE,
        HAND_INDRAGGABLE,
        CENTER_SELECTABLE
    };

    Location getLocation() const;
    void setLocation(const Location &value);

protected:
    Location loc;
    int id;
    double z;
    QPoint p;
    QImage origin;
    QImage abbr;
    QImage *img;

signals:
    void doubleClicked();
};

#endif // CARD_H

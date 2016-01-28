#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class GraphicsButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit GraphicsButton(QString path);
    ~GraphicsButton();

    QRectF boundingRect() const;
    void paint(QPainter *painter, QStyleOptionGraphicsItem *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

protected:
    QImage image;

signals:
    void clicked();

public slots:

};

#endif // GRAPHICSBUTTON_H

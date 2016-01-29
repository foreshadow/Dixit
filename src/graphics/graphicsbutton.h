#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class GraphicsButton : public QObject,
                       public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit GraphicsButton();
    explicit GraphicsButton(QString path);
    ~GraphicsButton();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

    void load(QString path);

protected:
    QImage image;

signals:
    void clicked();

public slots:

};

#endif // GRAPHICSBUTTON_H

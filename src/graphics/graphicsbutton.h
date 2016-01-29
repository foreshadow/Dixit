#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class GraphicsButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit GraphicsButton(const QString &path = QString());
    ~GraphicsButton();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

    void setImage(QString path);

protected:
    QImage image;
    bool hover;
    bool mouseDown;

signals:
    void clicked();

public slots:

};

#endif // GRAPHICSBUTTON_H

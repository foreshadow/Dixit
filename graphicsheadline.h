#ifndef GRAPHICSHEADLINE_H
#define GRAPHICSHEADLINE_H

#include <QObject>
#include <QGraphicsItem>

class GraphicsHeadline : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit GraphicsHeadline();
    ~GraphicsHeadline();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QString getText() const;
    void setText(const QString &value);
    void setImage(const QString &path);

    QGraphicsTextItem *getTextItem() const;\

protected:
    QImage image;
    QGraphicsTextItem *textItem;

signals:

public slots:
};

#endif // GRAPHICSHEADLINE_H

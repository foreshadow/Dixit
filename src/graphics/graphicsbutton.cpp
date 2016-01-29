#include "graphicsbutton.h"

GraphicsButton::GraphicsButton(const QString &path) :
    image(), hover(false), mouseDown(false)
{
    if (path.size() > 0)
        setImage(path);
    setAcceptHoverEvents(true);
}

GraphicsButton::~GraphicsButton()
{

}

QRectF GraphicsButton::boundingRect() const
{
    return image.rect();
}

void GraphicsButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().toRect(), QPixmap::fromImage(image));
    painter->setPen(QPen(QColor(0, 0, 0, 0)));
    if (mouseDown)
    {
        painter->setBrush(QBrush(QColor(0, 0, 0, 63)));
        painter->drawRect(image.rect());
    }
    else if (hover)
    {
        painter->setBrush(QBrush(QColor(255, 255, 255, 63)));
        painter->drawRect(image.rect());
    }
}

void GraphicsButton::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    hover = true;
    update();
}

void GraphicsButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    hover = false;
    update();
}

void GraphicsButton::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    mouseDown = true;
    update();
}

void GraphicsButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    mouseDown = false;
    emit clicked();
    update();
}

void GraphicsButton::setImage(QString path)
{
    image.load(path);
}


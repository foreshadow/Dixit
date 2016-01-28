#include "graphicsbutton.h"

GraphicsButton::GraphicsButton(QString path) :
    image(path)
{

}

GraphicsButton::~GraphicsButton()
{

}

QRectF GraphicsButton::boundingRect() const
{
    return image.rect();
}

void GraphicsButton::paint(QPainter *painter, QStyleOptionGraphicsItem *)
{
    painter->drawPixmap(boundingRect().toRect(), QPixmap::fromImage(image));
}

void GraphicsButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}


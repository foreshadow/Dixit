#include "graphicsbutton.h"

GraphicsButton::GraphicsButton() :
    image()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

GraphicsButton::GraphicsButton(QString path) :
    image(path)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
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
}

void GraphicsButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}

void GraphicsButton::load(QString path)
{
    image = QImage(path);
}


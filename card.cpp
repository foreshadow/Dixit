#include "card.h"

#include <QGraphicsSceneMouseEvent>

Card::Card(int id, QString path) :
    id(id),
    origin(QImage(path)),
    abbr(origin.scaledToHeight(150)),
    img(&abbr)
{
    this->setFlags(ItemIsSelectable);
    this->setAcceptHoverEvents(true);
}

Card::~Card()
{

}

QRectF Card::boundingRect() const
{
    return origin.rect();
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPixmap(img->rect(), QPixmap::fromImage(*img));
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::black));
    int width = img->width();
    int height = img->height();
    int boarder = qMin(5, qMin(width, height));
    painter->drawRect(0, 0, width, boarder);
    painter->drawRect(0, 0, boarder, height);
    painter->drawRect(0, height - boarder, width, boarder);
    painter->drawRect(width - boarder, 0, boarder, height);
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (img->rect().contains(event->pos().toPoint()) == false)
    {
        event->ignore();
        return;
    }
    z = zValue();
    setZValue(1000);
    p = pos().toPoint();
    this->moveBy((abbr.width() - origin.width()) / 2,
                 abbr.height() - origin.height());
    img = &origin;
    update();
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setZValue(z);
    img = &abbr;
    setPos(p);
    update();
}

void Card::focusInEvent(QFocusEvent *)
{

}

int Card::getId() const
{
    return id;
}

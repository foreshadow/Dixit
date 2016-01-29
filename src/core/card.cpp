#include "card.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QDrag>
#include <QApplication>
#include <QMimeData>
#include <QWidget>

Card::Card(int id, QString path) :
    id(id),
    origin(QImage(path)),
    abbr(origin.scaledToHeight(150)),
    img(&abbr)
{
    setAcceptHoverEvents(true);
}

Card::~Card()
{

}

QRectF Card::boundingRect() const
{
    return img->rect();
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPixmap(img->rect(), QPixmap::fromImage(*img));

    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::black));
    int width = img->width();
    int height = img->height();
    int boarder = qMin(*img == origin ? 4 : 3, qMin(width, height));
    painter->drawRect(0, 0, width, boarder);
    painter->drawRect(0, 0, boarder, height);
    painter->drawRect(0, height - boarder, width, boarder);
    painter->drawRect(width - boarder, 0, boarder, height);
//    painter->setPen(QPen(Qt::darkGray));
//    painter->setBrush(QBrush(Qt::darkGray));
//    boarder = 2;
//    painter->drawRect(0, 0, width, boarder);
//    painter->drawRect(0, 0, boarder, height);
//    painter->drawRect(0, height - boarder, width, boarder);
//    painter->drawRect(width - boarder, 0, boarder, height);
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *)
{

}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
            < QApplication::startDragDistance())
        return;
    QDrag *drag = new QDrag(event->widget());
    drag->setMimeData(new QMimeData);
    QPixmap pix(origin.size());
    QPainter painter(&pix);
    paint(&painter, 0, 0);
    drag->setPixmap(pix);
    drag->setHotSpot(event->pos().toPoint());
    hide();
    drag->exec();
    show();
    hoverLeaveEvent(nullptr); // warning
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{

}

void Card::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (img->rect().contains(event->pos().toPoint()) == false)
    {
        event->ignore();
        return;
    }
    setZValue(1000);
    setPos(p);
    this->moveBy((abbr.width() - origin.width()) / 2,
                 abbr.height() - origin.height());
    img = &origin;
    update();
}

void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    setZValue(z);
    img = &abbr;
    setPos(p);
    update();
}

void Card::recordPosition()
{
    z = zValue();
    p = pos().toPoint();
}

int Card::getId() const
{
    return id;
}

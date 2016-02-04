#include "centerarea.h"

#include <QMimeData>
#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QVariant>
#include "card.h"

CenterArea::CenterArea(int width, int height) :
    dragOver(false), rect(0, 0, width, height)
{
    setAcceptDrops(true);
    setZValue(500);
}

CenterArea::~CenterArea()
{

}

QRectF CenterArea::boundingRect() const
{
    return rect;
}

void CenterArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (dragOver)
    {
        painter->setPen(QPen(QColor(255, 255, 255, 0)));
        painter->setBrush(QBrush(QColor(255, 255, 255, 63)));
        painter->drawRect(rect);
    }
}

void CenterArea::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = true;
    event->accept();
    update();
}

void CenterArea::dragLeaveEvent(QGraphicsSceneDragDropEvent *)
{
    dragOver = false;
    update();
}

void CenterArea::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    emit cardDrop(event->mimeData()->text().toInt());
    update();
}

void CenterArea::clear()
{
    for (Card *c : list)
        c->hide();
    list.clear();
    update();
}

void CenterArea::addCard(Card *card)
{
    card->show();
    card->setLocation(Card::Location::CENTER_SELECTABLE);
    list.append(card);
    reposition();
}

void CenterArea::reposition()
{
    int x = pos().x() - 100;
    int y = pos().y();
    for (Card *c : list)
    {
        c->setPos(x += 100, y);
        c->recordPosition();
        c->update();
    }
    update();
}


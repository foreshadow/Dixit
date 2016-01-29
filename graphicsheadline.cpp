#include "graphicsheadline.h"

#include <QPainter>
#include <QTextItem>

GraphicsHeadline::GraphicsHeadline() :
    image(),
    textItem(new QGraphicsTextItem(this))
{
    textItem->setFont(QFont("微软雅黑", 16));
    textItem->setDefaultTextColor(Qt::white);
}

GraphicsHeadline::~GraphicsHeadline()
{

}

QRectF GraphicsHeadline::boundingRect() const
{
    return image.rect();
}

void GraphicsHeadline::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(image.rect(), QPixmap::fromImage(image));
}

QString GraphicsHeadline::getText() const
{
    return textItem->toPlainText();
}

void GraphicsHeadline::setText(const QString &value)
{
    int width = value.size() * textItem->font().pointSize();
    int height = textItem->font().pointSize() * 2;
    textItem->setPos((image.width() - width) / 2, (image.height() - height) / 2);
    textItem->setPlainText(value);
    update();
}

void GraphicsHeadline::setImage(const QString &path)
{
    image.load(path);
}

QGraphicsTextItem *GraphicsHeadline::getTextItem() const
{
    return textItem;
}






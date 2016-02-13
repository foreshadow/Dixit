#include "graphicscountdown.h"

#include <QtMath>

#include <QFont>

GraphicsCountdown::GraphicsCountdown(int secs)
{
    connect(&clicker, SIGNAL(timeout()), this, SLOT(click()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    clicker.setSingleShot(false);
    timer.setSingleShot(true);
    setPlainText(QString::number(secs));
    clicker.start(1000);
    timer.start(secs * 1000);
}

GraphicsCountdown::~GraphicsCountdown()
{

}

void GraphicsCountdown::click()
{
    setPlainText(QString::number(qCeil(timer.remainingTime() / 1000.)));
    update();
}

void GraphicsCountdown::timeout()
{
    hide();
    deleteLater();
}



GraphicsCountdownTemplate::GraphicsCountdownTemplate(int secs, int x, int y) :
    GraphicsCountdown(secs)
{
    setPos(x, y);
    setFont(QFont("微软雅黑", 28));
    setDefaultTextColor(Qt::white);
}

GraphicsCountdownTemplate::~GraphicsCountdownTemplate()
{

}

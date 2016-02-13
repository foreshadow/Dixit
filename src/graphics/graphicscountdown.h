#ifndef GRAPHICSCOUNTDOWN_H
#define GRAPHICSCOUNTDOWN_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QTimer>

class GraphicsCountdown : public QGraphicsTextItem
{
    Q_OBJECT

public:
    GraphicsCountdown(int secs);
    ~GraphicsCountdown();

protected:
    QTimer clicker;
    QTimer timer;

private slots:
    void click();
    void timeout();
};

class GraphicsCountdownTemplate : public GraphicsCountdown
{
public:
    GraphicsCountdownTemplate(int secs, int x = 0, int y = 0);
    ~GraphicsCountdownTemplate();
};

#endif // GRAPHICSCOUNTDOWN_H

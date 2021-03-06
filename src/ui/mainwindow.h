#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>

#include "tcpsocket.h"
#include "player.h"
#include "deck.h"
#include "chatform.h"
#include "handcards.h"
#include "centerarea.h"
#include "clientdata.h"
#include "serverdata.h"
#include "graphicsbutton.h"
#include "graphicsheadline.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(TcpSocket *socket, QString id);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event);

    void handle(ServerData cd);
    void sendClientData(ClientData cd);
    void sync(ServerData sd);

private:
    Ui::MainWindow *ui;
    TcpSocket *socket;

protected:
    Deck deck;
    HandCards hcards;
    QString myId;
    QList<QGraphicsPixmapItem *> rabbits;
    QList<QGraphicsPixmapItem *> bar1;
    QList<QGraphicsPixmapItem *> bar2;
    QList<QGraphicsTextItem *> ids;
    QList<QGraphicsTextItem *> scores;
//    QList<Player *> players;
    DixitGame *dixitGame;

    CenterArea *ca;
    GraphicsButton *gbReady;
    GraphicsHeadline *headline;
    QRectF pRect;

public slots:
    void chatFormAppend(QString msg);
    void systemMessage(QString msg);
    void received(QByteArray message);
    void chatFormSend(QString message);
    void onGBReadyClicked();
    void playCard(int id);
    void selected();
    void statusChanged();
    void descriptionChanged();
    void tableUpdated();
    void playerListChanged();
};

#endif // MAINWINDOW_H

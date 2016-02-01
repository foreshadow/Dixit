#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>

#include "tcpsocket.h"
#include "player.h"
#include "deck.h"
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
    QList<Player *> players;

    CenterArea *ca;
    GraphicsButton *gbReady;
    GraphicsHeadline *headline;

signals:
    void chatFormAppend(QString);

public slots:
    void received(QByteArray message);
    void chatFormSend(QString message);
    void onGBReadyClicked();
    void playCard(int id);
};

#endif // MAINWINDOW_H

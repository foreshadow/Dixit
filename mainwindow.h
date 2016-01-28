#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>

#include "tcpsocket.h"
#include "player.h"
#include "deck.h"
#include "handcards.h"
#include "clientdata.h"
#include "serverdata.h"

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
private:
    Ui::MainWindow *ui;
    TcpSocket *socket;

protected:
    Deck deck;
    HandCards hcards;
    QString myId;
    QList<QGraphicsPixmapItem *> rabbits;
    QList<Player *> players;

signals:
    void chatFormAppend(QString);

public slots:
    void received(QByteArray message);
    void chatFormSend(QString message);
};

#endif // MAINWINDOW_H

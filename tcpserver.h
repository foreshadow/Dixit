#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpsocket.h"

#include <QtNetwork>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    TcpServer(quint16 port);
    ~TcpServer();

    bool isListening() const;
    void listen(const QHostAddress &address, quint16 port);

    void removeDisconnected();
    int size();
    const QList<TcpSocket *> &getSocketList() const;

protected:
    QTcpServer *server;
    bool listeningStatus;
    QList<TcpSocket *> socketList;

signals:
    void receivedFrom(TcpSocket *, QString);
    void receivedFrom(QVariant, QString);
    void newClientConnected(TcpSocket *);

public slots:
    void send(QVariant id, QString message);
    void send(TcpSocket *socket, QString message);
    void sendToAll(QString message);

protected slots:
    void newPendingConnection();
    void received(QString message);
};

#endif // TCPSERVER_H

#include "tcpserver.h"

TcpServer::TcpServer(const QHostAddress &address, quint16 port) :
    server(new QTcpServer),
    listeningStatus(false/*server->listen(address, port)*/),
    socketList()
{
    connect(server, SIGNAL(newConnection()), this, SLOT(newPendingConnection()));
}

TcpServer::TcpServer(quint16 port) :
    server(new QTcpServer),
    listeningStatus(false/*server->listen(QHostAddress::Any, port)*/),
    socketList()
{
    connect(server, SIGNAL(newConnection()), this, SLOT(newPendingConnection()));
}

TcpServer::~TcpServer()
{
    server->deleteLater();
}

bool TcpServer::isListening() const
{
    return listeningStatus;
}

void TcpServer::listen(const QHostAddress &address, quint16 port)
{
    if (!isListening())
        listeningStatus = server->listen(address, port);
}

void TcpServer::removeDisconnected()
{
    for (int i = 0; i < socketList.size(); i++)
        if (!socketList.at(i)->isConnected())
            socketList.takeAt(i--);
}

int TcpServer::size()
{
    removeDisconnected();
    return socketList.size();
}

const QList<TcpSocket *> &TcpServer::getSocketList() const
{
    return socketList;
}

void TcpServer::send(QVariant id, QString message)
{
    foreach (TcpSocket *socket, socketList)
    {
        if (socket->getId() == id)
        {
            socket->send(message);
            break;
        }
    }
}

void TcpServer::send(TcpSocket *socket, QString message)
{
    socket->send(message);
}

void TcpServer::sendToAll(QString message)
{
    foreach (TcpSocket *socket, socketList)
    {
        send(socket, message);
    }
}

void TcpServer::newPendingConnection()
{
    TcpSocket *socket = new TcpSocket(server->nextPendingConnection());
    connect(socket, SIGNAL(received(QString)), this, SLOT(received(QString)));
    socketList << socket;
    emit newClientConnected(socket);
}

void TcpServer::received(QString message)
{
    TcpSocket *socket = qobject_cast<TcpSocket *>(sender());
    emit receivedFrom(socket->getId(), message);
    emit receivedFrom(socket, message);
}

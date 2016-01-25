#include "tcpsocket.h"

TcpSocket::TcpSocket() :
    socket(new QTcpSocket),
    identifier(qrand()),
    blockSize(0),
    messageReceived()
{

}

TcpSocket::TcpSocket(QTcpSocket *socket) :
    socket(socket),
    identifier(qrand()),
    blockSize(0),
    messageReceived()
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

TcpSocket::~TcpSocket()
{
    socket->deleteLater();
}

void TcpSocket::connectToHost(const QHostAddress &address, quint16 port, QAbstractSocket::OpenMode mode)
{
    connect(socket, SIGNAL(connected()), this, SIGNAL(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    socket->connectToHost(address, port, mode);
    socket->waitForConnected(3000);
}

QAbstractSocket::SocketState TcpSocket::state() const
{
    return socket->state();
}

bool TcpSocket::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

void TcpSocket::reconnect()
{
    if (!isConnected())
        socket->waitForConnected(3000);
}

QVariant TcpSocket::getId() const
{
    return identifier;
}

void TcpSocket::setId(const QVariant &id)
{
    identifier = id;
    emit nameChanged();
}

void TcpSocket::send(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(DATA_STREAM_VERSION);
    out << (__typeof blockSize) 0 << message;
    out.device()->seek(0);
    out << (__typeof blockSize) (block.size() - sizeof blockSize);
    socket->write(block);
}

void TcpSocket::readMessage()
{
    QDataStream in(socket);
    in.setVersion(DATA_STREAM_VERSION);
    if (blockSize == 0)
    {
        if (socket->bytesAvailable() < (int) sizeof blockSize)
            return;
        in >> blockSize;
    }
    if (socket->bytesAvailable() < blockSize)
        return;
    in >> messageReceived;
    emit received(messageReceived);
    messageReceived.clear();
    blockSize = 0;
    readMessage();
}

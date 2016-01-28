#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <QtCore>

class ServerData
{
public:
    enum Type
    {
        CHAT,
        PHRASE,
        REQUEST_ID,
        DESC,
        SYNC,
        READY,
        DRAW,
        SELECT,
        PLAY
    };

    ServerData(QDataStream &&ds);
    ServerData(Type t, const QString &fromUser = QString(), const QString &content = QString(),
               const QList<int> &cards = QList<int>());
    ~ServerData();

    int getType() const;
    QString getFromUser() const;
    QString getContent() const;
    const QList<int> &getCards() const;
    QDateTime getUtc() const;

    friend QDataStream &operator <<(QDataStream &ds, const ServerData &sd);

protected:
    int type;
    QString fromUser;
    QString content;
    QList<int> cards;
    QDateTime utc;
};

#endif // SERVERDATA_H

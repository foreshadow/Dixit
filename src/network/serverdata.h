#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <QtCore>

class ServerData
{
public:
    enum class Type
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
    ServerData(Type t, const QList<int> &cards);
    ServerData(Type t, const QString &fromUser, int card);
    ~ServerData();

    QVariant getData(const QString &key) const;
    Type getType() const;
    QString getFromUser() const;
    QString getContent() const;
    QList<int> getCards() const;
    QDateTime getUtc() const;

    friend QDataStream &operator <<(QDataStream &ds, const ServerData &sd);

protected:
    QMap<QString, QVariant> m;
};

Q_DECLARE_METATYPE(ServerData::Type)

#endif // SERVERDATA_H

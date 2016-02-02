#include "serverdata.h"

ServerData::ServerData(QDataStream &&ds)
{
    ds >> m;
}

ServerData::ServerData(ServerData::Type t, const QString &fromUser,
                       const QString &content, const QList<int> &cards)
{
    m["type"] = QVariant::fromValue(t);
    m["fromUser"] = fromUser;
    m["content"] = content;
    m["cards"] = QVariant::fromValue(cards);
    m["utc"] = QDateTime::currentDateTimeUtc();
}

ServerData::ServerData(ServerData::Type t, const QList<int> &cards)
{
    m["type"] = QVariant::fromValue(t);
    m["cards"] = QVariant::fromValue(cards);
    m["utc"] = QDateTime::currentDateTimeUtc();
}

ServerData::ServerData(ServerData::Type t, const QString &fromUser, int card)
{
    m["type"] = QVariant::fromValue(t);
    m["fromUser"] = fromUser;
    m["cards"] = QVariant::fromValue(QList<int>({card}));
    m["utc"] = QDateTime::currentDateTimeUtc();
}

ServerData::~ServerData()
{

}

QVariant ServerData::getData(const QString &key) const
{
    return m[key];
}

ServerData::Type ServerData::getType() const
{
    return m["type"].value<ServerData::Type>();
}

QString ServerData::getFromUser() const
{
    return m["fromUser"].toString();
}

QString ServerData::getContent() const
{
    return m["content"].toString();
}

QList<int> ServerData::getCards() const
{
    return m["cards"].value<QList<int>>();
}

QDateTime ServerData::getUtc() const
{
    return m["utc"].toDateTime();
}

QDataStream &operator <<(QDataStream &ds, const ServerData &sd)
{
    return ds << sd.m;
}


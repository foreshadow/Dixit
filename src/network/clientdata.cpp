#include "clientdata.h"

ClientData::ClientData(QDataStream &&ds)
{
    ds >> m;
}

ClientData::ClientData(ClientData::Type t, QString fromUser, QString content, QList<int> cards)
{
    m["type"] = QVariant::fromValue(t);
    m["fromUser"] = fromUser;
    m["content"] = content;
    m["cards"] = QVariant::fromValue(cards);
    m["utc"] = QDateTime::currentDateTimeUtc();
}

ClientData::ClientData(ClientData::Type t, QString fromUser, int card)
{
    m["type"] = QVariant::fromValue(t);
    m["fromUser"] = fromUser;
    m["cards"] = QVariant::fromValue(QList<int>({card}));
    m["utc"] = QDateTime::currentDateTimeUtc();
}

ClientData::~ClientData()
{

}

QVariant ClientData::getData(const QString &key) const
{
    return m[key];
}

ClientData::Type ClientData::getType() const
{
    return m["type"].value<ClientData::Type>();
}

QString ClientData::getFromUser() const
{
    return m["fromUser"].toString();
}

QString ClientData::getContent() const
{
    return m["content"].toString();
}

QList<int> ClientData::getCards() const
{
    return m["cards"].value<QList<int>>();
}

QDateTime ClientData::getUtc() const
{
    return m["utc"].toDateTime();
}


QDataStream &operator <<(QDataStream &ds, const ClientData &cd)
{
    return ds << cd.m;
}



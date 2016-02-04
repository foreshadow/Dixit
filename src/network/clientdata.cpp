#include "clientdata.h"

ClientData::ClientData(QDataStream &&ds)
{
    ds >> m;
}

ClientData::ClientData(ClientData::Type t, QString fromUser, QString content, QList<int> cards)
{
    m["type"] = int(t);
    m["fromUser"] = fromUser;
    m["content"] = content;
    QVariantList list;
    for (int c : cards)
        list << c;
    m["cards"] = list;
    m["utc"] = QDateTime::currentDateTimeUtc();
}

ClientData::ClientData(ClientData::Type t, QString fromUser, int card)
{
    m["type"] = int(t);
    m["fromUser"] = fromUser;
    QVariantList list;
    list << card;
    m["cards"] = list;
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
    return ClientData::Type(m["type"].toInt());
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
    QList<int> list;
    QVariantList vlist = m["cards"].toList();
    for (QVariant var : vlist)
        list.append(var.toInt());
    return list;
}

QDateTime ClientData::getUtc() const
{
    return m["utc"].toDateTime();
}


QDataStream &operator <<(QDataStream &ds, const ClientData &cd)
{
    return ds << cd.m;
}



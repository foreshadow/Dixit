#include "serverdata.h"

ServerData::ServerData(QDataStream &&ds)
{
    ds >> m;
}

ServerData::ServerData(ServerData::Type t, const QString &fromUser,
                       const QString &content, const QList<int> &cards)
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

ServerData::ServerData(ServerData::Type t, const QList<int> &cards)
{
    m["type"] = int(t);
    QVariantList list;
    for (int c : cards)
        list << c;
    m["cards"] = list;
    m["utc"] = QDateTime::currentDateTimeUtc();
}

ServerData::ServerData(ServerData::Type t, const QString &fromUser, int card)
{
    m["type"] = int(t);
    m["fromUser"] = fromUser;
    QVariantList list;
    list << card;
    m["cards"] = list;
    m["utc"] = QDateTime::currentDateTimeUtc();
}

ServerData::ServerData(ServerData::Type t, const DixitGame &dixitGame)
{
    m["type"] = int(t);
    QByteArray bytes;
    QDataStream ds(&bytes, QIODevice::WriteOnly);
    ds.setVersion(QDataStream::Qt_5_4);
    ds << dixitGame;
    m["dixitGame"] = bytes;
}

ServerData::~ServerData()
{

}

const DixitGame &ServerData::getDixitGame() const
{
    static DixitGame dg;
    QDataStream ds(m["dixitGame"].toByteArray());
    ds.setVersion(QDataStream::Qt_5_4);
    ds >> dg;
    return dg;
}

QVariant ServerData::getData(const QString &key) const
{
    return m[key];
}

ServerData::Type ServerData::getType() const
{
    return ServerData::Type(m["type"].toInt());
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
    QList<int> list;
    QVariantList vlist = m["cards"].toList();
    for (QVariant var : vlist)
        list.append(var.toInt());
    return list;
}

QDateTime ServerData::getUtc() const
{
    return m["utc"].toDateTime();
}

QDataStream &operator <<(QDataStream &ds, const ServerData &sd)
{
    return ds << sd.m;
}


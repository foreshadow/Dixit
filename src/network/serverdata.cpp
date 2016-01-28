#include "serverdata.h"

ServerData::ServerData(QDataStream &&ds)
{
    ds >> type >> fromUser >> content >> cards >> utc;
}

ServerData::ServerData(ServerData::Type t, const QString &fromUser,
                       const QString &content, const QList<int> &cards) :
    type(t), fromUser(fromUser), content(content), cards(cards), utc(QDateTime::currentDateTimeUtc())
{

}

ServerData::~ServerData()
{

}
int ServerData::getType() const
{
    return type;
}

QString ServerData::getFromUser() const
{
    return fromUser;
}

QString ServerData::getContent() const
{
    return content;
}

const QList<int> &ServerData::getCards() const
{
    return cards;
}
QDateTime ServerData::getUtc() const
{
    return utc;
}

QDataStream &operator <<(QDataStream &ds, const ServerData &sd)
{
    return ds << sd.type << sd.fromUser << sd.content << sd.cards << sd.utc;
}


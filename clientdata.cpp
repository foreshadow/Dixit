#include "clientdata.h"

ClientData::ClientData(QDataStream &&ds)
{
    ds >> type >> fromUser >> content >> cards >> utc;
}

ClientData::ClientData(ClientData::Type t, QString fromUser, QString content, QList<int> cards) :
    type(t), fromUser(fromUser), content(content), cards(cards), utc(QDateTime::currentDateTimeUtc())
{

}

ClientData::~ClientData()
{

}

int ClientData::getType() const
{
    return type;
}

QString ClientData::getFromUser() const
{
    return fromUser;
}

QString ClientData::getContent() const
{
    return content;
}

QList<int> ClientData::getCards() const
{
    return cards;
}

QDateTime ClientData::getUtc() const
{
    return utc;
}


QDataStream &operator <<(QDataStream &ds, const ClientData &cd)
{
    return ds << cd.type << cd.fromUser << cd.content << cd.cards << cd.utc;
}



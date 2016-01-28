#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <QtCore>

class ClientData
{
public:
    enum Type
    {
        CHAT,
        PHRASE,
        SET_ID,
        READY,
        SYNC,
        DESC,
        PLAY,
        SELECT
    };

    ClientData(QDataStream &&ds);
    ClientData(Type t, QString fromUser = QString(), QString content = QString(),
               QList<int> cards = QList<int>());
    ~ClientData();

    int getType() const;
    QString getFromUser() const;
    QString getContent() const;
    QList<int> getCards() const;
    QDateTime getUtc() const;

    friend QDataStream &operator <<(QDataStream &ds, const ClientData &cd);


protected:
    int type;
    QString fromUser;
    QString content;
    QList<int> cards;
    QDateTime utc;
};

#endif // CLIENTDATA_H

#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <QtCore>

class ClientData
{
public:
    enum class Type
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
    ClientData(Type t, QString fromUser, int card);
    ~ClientData();

    QVariant getData(const QString &key) const;
    Type getType() const;
    QString getFromUser() const;
    QString getContent() const;
    QList<int> getCards() const;
    QDateTime getUtc() const;

    friend QDataStream &operator <<(QDataStream &ds, const ClientData &cd);


protected:
    QMap<QString, QVariant> m;
};

Q_DECLARE_METATYPE(ClientData::Type)

#endif // CLIENTDATA_H

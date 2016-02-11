#ifndef PLAYER_H
#define PLAYER_H

//#include <QObject>
#include "tcpsocket.h"

class Player //: public QObject
{
//    Q_OBJECT
public:
    enum class Color
    {
        Unknown = 0,
        Black,
        Blue,
        Green,
        White,
        Yellow,
        Pink,
    };

    Player();
    Player(QString id, TcpSocket *socket);
    ~Player();

    void operator =(const Player &p);
    bool operator ==(const Player &p) const;
    bool operator !=(const Player &p) const;

    friend QDataStream &operator <<(QDataStream &ds, const Player &p);
    friend void operator >>(QDataStream &ds, Player &p);

    int getSeat() const;
    void setSeat(int value);

    QString getId() const;
    void setId(const QString &value);

    bool getReady() const;
    void setReady(bool value = true);

    int getScore() const;
    void setScore(int value);

    TcpSocket *getSocket() const;
    void setSocket(TcpSocket *value);

    QList<int> getHandCards() const;
    void setHandCards(const QList<int> &value);

    bool getActive() const;
    void setActive(bool value = true);

    bool getPlayed() const;
    void setPlayed(bool value = true);

    int getSelected() const;
    void setSelected(bool value = 0);

    Color getColor() const;
    void setColor(const Color &value);

protected:
    int seat;
    Color color;
    QString id;
    bool ready;
    int score;
    TcpSocket *socket;
    QList<int> handCards;
    bool active;
    bool played;
    int selected;

//signals:
//    void updated();
};

#endif // PLAYER_H

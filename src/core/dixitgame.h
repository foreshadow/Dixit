#ifndef DIXITGAME_H
#define DIXITGAME_H

#include <QObject>

#include "player.h"
#include "tcpsocket.h"

class DixitGame : public QObject
{
    Q_OBJECT

    typedef TcpSocket * UniqueId;

public:
    enum Status
    {
        DIXIT_BEFORE_GAME,
        DIXIT_IN_GAME_DESCRIBING,
        DIXIT_IN_GAME_PLAYING,
        DIXIT_IN_GAME_SELECTING,
        DIXIT_IN_GAME_SETTLING
    };

    DixitGame();
    DixitGame(const QList<Player> &playerlist);
    ~DixitGame();

    Status status() const;
    bool isPlaying() const;
    QString description() const;
    QString message() const;
    const QList<int> &table() const;
    QList<Player> &playerList();
    const QList<Player> &constPlayerList() const;
    Player *currentPlayer();

    Player *findPlayer(UniqueId uid);

    void setStatus(Status status);
    void setDescription(QString description);
    void setTable(const QList<int> &list);
    void addToTable(int card);
    void clearTable();

    void update(const DixitGame &dixitGame);

    void ready(UniqueId uid);
    void describe(UniqueId uid, const QString &desc);
    void play(UniqueId uid, int card);
    void select(UniqueId uid, int card);

    friend QDataStream &operator <<(QDataStream &ds, const DixitGame &dixitGame);
    friend void operator >>(QDataStream &ds, DixitGame& dixitGame);

private:
    void setMessage(QString message = QString());
    void clearStatus();
    int notYetReady();
    int notYetPlayed();
    int notYetSelected();

protected:
    QList<Player> p;
    Status s;
    QString d;
    QList<int> t;

    QString m;

signals:
    void updated();
    void message(QString);
    void gameBegin();
    void statusChanged();
    void descriptionChanged();
    void descriptionChangedTo(QString);
    void allPlayed();
    void allSelected();
    void messageUpdated();
    void tableUpdated();
    void playerListChanged();
    void playerChanged(Player *);
    void gameOver();

public slots:
};

Q_DECLARE_METATYPE(DixitGame::Status)
//Q_DECLARE_METATYPE(DixitGame)

#endif // DIXITGAME_H

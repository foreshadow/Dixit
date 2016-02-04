#include "dixitgame.h"

DixitGame::DixitGame() : p()
{

}

DixitGame::DixitGame(const QList<Player> &playerlist) : p(playerlist)
{

}

DixitGame::~DixitGame()
{

}

DixitGame::Status DixitGame::status() const
{
    return s;
}

bool DixitGame::isPlaying() const
{
    return s != DixitGame::Status::DIXIT_BEFORE_GAME;
}

QString DixitGame::description() const
{
    return d;
}

QString DixitGame::message() const
{
    return m;
}

const QList<int> &DixitGame::table() const
{
    return t;
}

QList<Player> &DixitGame::playerList()
{
    return p;
}

const QList<Player> &DixitGame::constPlayerList() const
{
    return p;
}

Player *DixitGame::currentPlayer()
{
    for (Player &player : p)
        if (player.getActive())
            return &player;
    return nullptr;
}

Player *DixitGame::findPlayer(DixitGame::UniqueId uid)
{
    for (Player &player : p)
        if (player.getSocket() == uid)
            return &player;
    return nullptr;
}

void DixitGame::setStatus(DixitGame::Status status)
{
    if (s == status)
        return;
    if (s == DixitGame::Status::DIXIT_IN_GAME_SETTLING)
        clearStatus();
    s = status;
    emit statusChanged();
}

void DixitGame::setDescription(QString description)
{
    if (d == description)
        return;
    d = description;
    emit descriptionChanged();
    emit descriptionChangedTo(d);
}

void DixitGame::setTable(const QList<int> &list)
{
    if (t == list)
        return;
    t = list;
    emit tableUpdated();
}

void DixitGame::addToTable(int card)
{
    t.append(card);
    emit tableUpdated();
}

void DixitGame::clearTable()
{
    t.clear();
    emit tableUpdated();
}

void DixitGame::update(const DixitGame &dixitGame)
{
    if (dixitGame.status() != status())
        setStatus(dixitGame.status());
    if (dixitGame.description() != description())
        setDescription(dixitGame.description());
    if (dixitGame.table() != table())
        setTable(dixitGame.table());
    if (dixitGame.constPlayerList().size() != constPlayerList().size())
    {
        p = dixitGame.constPlayerList();
        emit playerListChanged();
    }
    else
    {
        bool changed = false;
        for (int i = 0; i < constPlayerList().size(); i++)
            if (dixitGame.constPlayerList().at(i) != constPlayerList().at(i))
            {
                p[i] = dixitGame.constPlayerList().at(i);
                emit playerChanged(&p[i]);
                changed = true;
            }
        if (changed)
            emit playerListChanged();
    }
}

void DixitGame::ready(DixitGame::UniqueId uid)
{
    Player *pp = findPlayer(uid);
    if (pp == nullptr)
        return;
    if (pp->getReady())
        return;
    pp->setReady();
    emit playerChanged(pp);
    message(QString("玩家%1准备就绪。").arg(pp->getId()));
    if (notYetReady() > 0)
        setMessage(QString("还有%1位玩家没有准备。").arg(notYetReady()));
    else
    {
        setMessage();
        emit gameBegin();
    }
}

void DixitGame::describe(DixitGame::UniqueId uid, const QString &desc)
{
    Player *pp = findPlayer(uid);
    if (pp == nullptr)
        return;
    if (pp->getActive() == false)
        return;
    if (description() == desc)
        return;
    setDescription(desc);
    message(QString("玩家%1的描述是\n  %2").arg(pp->getId()).arg(desc));
    setMessage();
}

void DixitGame::play(DixitGame::UniqueId uid, int card)
{
    Player *pp = findPlayer(uid);
    if (pp == nullptr)
        return;
    if (pp->getPlayed())
        return;
    pp->setPlayed();
    pp->getHandCards().removeAll(card);
    addToTable(card);
    if (notYetPlayed() > 0)
        setMessage(QString("还有%1位玩家未出牌。").arg(notYetPlayed()));
    else
    {
        setMessage();
        emit allPlayed();
    }
}

void DixitGame::select(DixitGame::UniqueId uid, int card)
{
    Player *pp = findPlayer(uid);
    if (pp == nullptr)
        return;
    if (pp->getActive())
        return;
    if (pp->getSelected())
        return;
    pp->setSelected(card);
    if (notYetSelected() > 0)
        setMessage(QString("还有%1位玩家未选择。").arg(notYetSelected()));
    else
    {
        setMessage();
        emit allSelected();
    }
}

QDataStream &operator <<(QDataStream &ds, const DixitGame &dixitGame)
{
    return ds << dixitGame.p << int(dixitGame.s) << dixitGame.d << dixitGame.t << dixitGame.m;
}

void operator >>(QDataStream &ds, DixitGame &dixitGame)
{
    QVariant var;
    ds >> dixitGame.p >> var >> dixitGame.d >> dixitGame.t >> dixitGame.m;
    dixitGame.s = DixitGame::Status(var.toInt());
}

void DixitGame::setMessage(QString message)
{
    m = message;
    emit messageUpdated();
}

void DixitGame::clearStatus()
{
    for (Player &player : p)
    {
        player.setPlayed(false);
        player.setSelected(false);
    }
}

int DixitGame::notYetReady()
{
    int c = 0;
    for (const Player &player : p)
        if (player.getReady() == false)
            c++;
    return c;
}

int DixitGame::notYetPlayed()
{
    int c = 0;
    for (const Player &player : p)
        if (player.getPlayed() == false)
            c++;
    return c;
}

int DixitGame::notYetSelected()
{
    int c = 0;
    for (const Player &player : p)
        if (player.getSelected() == false)
            c++;
    return c;
}

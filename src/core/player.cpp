#include "player.h"

Player::Player() :
    seat(0), color(Player::Color::Unknown), id(), ready(false), score(0),
    socket(nullptr), handCards(), active(false), played(false), selected(false)
{

}

Player::Player(QString id, TcpSocket *socket) :
    seat(0), color(Player::Color::Unknown), id(id), ready(false), score(0),
    socket(socket), handCards(), active(false), played(false), selected(false)
{

}

Player::~Player()
{

}

void Player::operator =(const Player &p)
{
    socket = p.socket;
    seat = p.seat;
    color = p.color;
    id = p.id;
    ready = p.ready;
    score = p.score;
    handCards = p.handCards;
    active = p.active;
    played = p.played;
    selected = p.selected;
}

bool Player::operator ==(const Player &p) const
{
    return socket == p.socket
           && seat == p.seat
           && color == p.color
           && id == p.id
           && ready == p.ready
           && score == p.score
           && handCards == p.handCards
           && active == p.active
           && played == p.played
           && selected == p.selected;
}

bool Player::operator !=(const Player &p) const
{
    return !((*this) == p);
}

QDataStream &operator <<(QDataStream &ds, const Player &p)
{
    return ds << (int)p.socket << p.seat << (int)p.color << p.id << p.ready << p.score
              << p.handCards << p.active << p.played << p.selected;
}

void operator >>(QDataStream &ds, Player &p)
{
    int pSocket;
    int eColor;
    ds >> pSocket >> p.seat >> eColor >> p.id >> p.ready >> p.score
       >> p.handCards >> p.active >> p.played >> p.selected;
    p.socket = (TcpSocket *)(pSocket);
    p.color = (Player::Color)(eColor);
}

int Player::getSeat() const
{
    return seat;
}

void Player::setSeat(int value)
{
    seat = value;
//    emit updated();
}

QString Player::getId() const
{
    return id;
}

void Player::setId(const QString &value)
{
    id = value;
//    emit updated();
}

bool Player::getReady() const
{
    return ready;
}

void Player::setReady(bool value)
{
    ready = value;
//    emit updated();
}

int Player::getScore() const
{
    return score;
}

void Player::setScore(int value)
{
    score = value;
//    emit updated();
}

TcpSocket *Player::getSocket() const
{
    return socket;
}

void Player::setSocket(TcpSocket *value)
{
    socket = value;
//    emit updated();
}

QList<int> Player::getHandCards() const
{
    return handCards;
}

void Player::setHandCards(const QList<int> &value)
{
    handCards = value;
//    emit updated();
}
bool Player::getActive() const
{
    return active;
}

void Player::setActive(bool value)
{
    active = value;
//    emit updated();
}

bool Player::getPlayed() const
{
    return played;
}

void Player::setPlayed(bool value)
{
    played = value;
//    emit updated();
}

int Player::getSelected() const
{
    return selected;
}

void Player::setSelected(bool value)
{
    selected = value;
//    emit updated();
}
Player::Color Player::getColor() const
{
    return color;
}

void Player::setColor(const Color &value)
{
    color = value;
}












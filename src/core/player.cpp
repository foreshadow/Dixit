#include "player.h"

Player::Player(QString id, TcpSocket *socket) :
    id(id),
    ready(false),
    score(0),
    socket(socket)
{

}

Player::~Player()
{

}
int Player::getScore() const
{
    return score;
}

void Player::setScore(int value)
{
    score = value;
    emit updated();
}

void Player::addScore(int delta)
{
    score += delta;
    emit updated();
}

TcpSocket *Player::getSocket() const
{
    return socket;
}
QString Player::getId() const
{
    return id;
}

void Player::setId(const QString &value)
{
    id = value;
    emit updated();
}
bool Player::getReady() const
{
    return ready;
}

void Player::setReady(bool value)
{
    ready = value;
}




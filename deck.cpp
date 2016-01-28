#include "deck.h"

Deck::Deck(QObject *parent) : QObject(parent)
{

}

Deck::~Deck()
{

}

void Deck::clear()
{
    for (Card *c : list)
        delete c;
    list.clear();
}

void Deck::addCard(Card *card)
{
    list.append(card);
}

Card *Deck::getCard(int id) const
{
    for (Card *c : list)
        if (c->getId() == id)
            return c;
    return nullptr;
}


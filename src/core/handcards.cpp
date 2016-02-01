#include "handcards.h"

HandCards::HandCards()
{

}

HandCards::~HandCards()
{

}

void HandCards::addCard(Card *card)
{
    if (card == nullptr)
        return;
    card->setLocation(Card::Location::HAND_DRAGGABLE);
    list << card;
    reposition();
    card->show();
}

Card *HandCards::takeCard(int id)
{
    for (Card *c : list)
        if (c->getId() == id)
        {
            list.removeOne(c);
            c->setLocation(Card::Location::DECK_INVISIBLE);
            reposition();
            return c;
        }
    return nullptr;
}

void HandCards::reposition()
{
    int x =  50;
    int y = 400;
    for (int i = 0; i < list.size(); i++)
    {
        list[i]->setZValue(100 + i);
        list[i]->setPos(x += 100, y);\
        list[i]->recordPosition();
    }
}


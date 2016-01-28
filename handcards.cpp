#include "handcards.h"

HandCards::HandCards()
{

}

HandCards::~HandCards()
{

}

void HandCards::addCard(Card *card)
{
    list << card;
    reposition();
    card->show();
}

void HandCards::discard(Card *card)
{
    list.removeOne(card);
    reposition();
}

void HandCards::reposition()
{
    int x =  50;
    int y = 400;
    for (int i = 0; i < list.size(); i++)
    {
        list[i]->setZValue(100 + i);
        list[i]->setPos(x += 100, y);
    }
}


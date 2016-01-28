#ifndef HANDCARDS_H
#define HANDCARDS_H

#include <QtCore>

#include "card.h"

class HandCards
{
public:
    HandCards();
    ~HandCards();

    void addCard(Card *card);
    void discard(Card *card);

private:
    void reposition();

protected:
    QList<Card *> list;
};

#endif // HANDCARDS_H

#ifndef DECK_H
#define DECK_H

#include <QObject>
#include <QtCore>
#include "card.h"

class Deck : public QObject
{
    Q_OBJECT
public:
    explicit Deck(QObject *parent = 0);
    ~Deck();

    void clear();
    void addCard(Card *card);
    Card *getCard(int id) const;

protected:
    QList<Card *> list;

signals:

public slots:
};

#endif // DECK_H

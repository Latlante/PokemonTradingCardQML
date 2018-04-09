#ifndef FIGHTAREA_H
#define FIGHTAREA_H

#include "abstractpacketstatic.h"

class CardPokemon;

class FightArea : public AbstractPacketStatic
{
    Q_OBJECT

public:
    FightArea(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~FightArea();
	
    int maxCards() const override;

    CardPokemon* pokemonFighting(int index);



};

#endif // FIGHTAREA_H

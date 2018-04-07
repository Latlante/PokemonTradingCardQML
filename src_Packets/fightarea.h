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

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;



};

#endif // FIGHTAREA_H

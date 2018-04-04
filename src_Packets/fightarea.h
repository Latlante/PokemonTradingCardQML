#ifndef FIGHTAREA_H
#define FIGHTAREA_H

#include "abstractpacket.h"

class CardPokemon;

class FightArea : public AbstractPacket
{
    Q_OBJECT

public:
    FightArea(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~FightArea();
	
    static int maxCards() override;

    CardPokemon* pokemonFighting(int index);

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;



};

#endif // FIGHTAREA_H

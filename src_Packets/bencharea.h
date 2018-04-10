#ifndef BENCHAREA_H
#define BENCHAREA_H

#include "abstractpacketstatic.h"

class ModelListEnergies;

class BenchArea : public AbstractPacketStatic
{
    Q_OBJECT

public:
    BenchArea(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~BenchArea();

    static void declareQML();
	
    int maxCards() const override;

    Q_INVOKABLE ModelListEnergies* modelFromCardPokemon(int index);

private:

};

#endif // BENCHAREA_H

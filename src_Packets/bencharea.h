#ifndef BENCHAREA_H
#define BENCHAREA_H

#include "abstractpacketstatic.h"

class ModelListEnergies;

class BenchArea : public AbstractPacketStatic
{
    Q_OBJECT

public:
//    enum BenchRole {
//        BenchRole_Card = Qt::UserRole,
//        BenchRole_IsCard,
//        BenchRole_Name,
//        BenchRole_ImageCard,
//        BenchRole_ModelEnergies,
//    };
    BenchArea(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~BenchArea();

    static void declareQML();
	
    int maxCards() const override;

    Q_INVOKABLE ModelListEnergies* modelFromCardPokemon(int index);
    //virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//protected:
//    QHash<int, QByteArray> roleNames() const override;

private:

};

#endif // BENCHAREA_H

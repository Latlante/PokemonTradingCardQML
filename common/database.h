#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"

#define INDEX_START_POKEMON     0
#define INDEX_START_ENERGIES    1000
#define INDEX_START_ACTION      1100

class Database : public QObject
{
    Q_OBJECT
public:
    enum Enum_InformationAttack
    {
        InfoAtt_Name = 0,
        InfoAtt_Description,
        InfoAtt_Damage,
        InfoAtt_FirstEnergies,
        InfoAtt_ActionType = InfoAtt_FirstEnergies + AbstractCard::Element_COUNT,
        InfoAtt_ActionArgument,
        InfoAtt_COUNT
    };

    enum Enum_InformationPokemonDatabase
    {
        InfoDbPok_Id = 0,
        InfoDbPok_Name,
        InfoDbPok_Life,
        InfoDbPok_Element,
        InfoDbPok_ElementSecond,
        InfoDbPok_Weakness,
        InfoDbPok_Resistance,
        InfoDbPok_CostRetreat,
        InfoDbPok_IdSubevolution,
        InfoDbPok_Att1,
        InfoDbPok_Att2 = InfoDbPok_Att1 + InfoAtt_COUNT,
        InfoDbPok_Att3 = InfoDbPok_Att2 + InfoAtt_COUNT
    };

    enum Enum_InformationEnergiesDatabase
    {
        InfoDbNrj_Id = 0,
        InfoDbNrj_Name,
        InfoDbNrj_Quantity,
    };

    explicit Database(QObject *parent = nullptr);

    AbstractCard* cardById(int id);

signals:

private:
    CardPokemon* newCardPokemon(const QString &infoCsv);
    CardEnergy* newCardEnergy(const QString& infoCsv);
};

#endif // DATABASE_H

#ifndef ACTIONCHANGEENEMYSTATUS_H
#define ACTIONCHANGEENEMYSTATUS_H

#include "abstractaction.h"
#include "src_Cards/cardpokemon.h"


class ActionChangeEnemyStatus : public AbstractAction
{
public:
    explicit ActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status);

    AbstractAction::Enum_typeOfAction type() override;
    void executeAction() override;

signals:

private:
    CardPokemon::Enum_statusOfPokemon m_status;
};

#endif // ACTIONCHANGEENEMYSTATUS_H

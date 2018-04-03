#ifndef ACTIONCHANGEENEMYSTATUSRANDOM_H
#define ACTIONCHANGEENEMYSTATUSRANDOM_H

#include "abstractaction.h"
#include "src_Cards/cardpokemon.h"

class ActionChangeEnemyStatusRandom : public AbstractAction
{
public:
    explicit ActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon status);

    AbstractAction::Enum_typeOfAction type() override;
    void executeAction() override;

signals:

private:
    CardPokemon::Enum_statusOfPokemon m_status;
};

#endif // ACTIONCHANGEENEMYSTATUSRANDOM_H

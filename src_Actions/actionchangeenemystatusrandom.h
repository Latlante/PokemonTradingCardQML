#ifndef ACTIONCHANGEENEMYSTATUSRANDOM_H
#define ACTIONCHANGEENEMYSTATUSRANDOM_H

#include "abstractaction.h"

class ActionChangeEnemyStatusRandom : public AbstractAction
{
public:
    explicit ActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon status);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

signals:

private:
    CardPokemon::Enum_statusOfPokemon m_status;
};

#endif // ACTIONCHANGEENEMYSTATUSRANDOM_H

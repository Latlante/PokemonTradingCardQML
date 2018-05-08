#ifndef ACTIONCHANGEENEMYSTATUSRANDOM_H
#define ACTIONCHANGEENEMYSTATUSRANDOM_H

#include "abstractaction.h"

class ActionChangeEnemyStatusRandom : public AbstractAction
{
public:
    explicit ActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon statusOnHead, CardPokemon::Enum_statusOfPokemon statusOnTail);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

signals:

private:
    CardPokemon::Enum_statusOfPokemon m_statusOnHead;
    CardPokemon::Enum_statusOfPokemon m_statusOnTail;
};

#endif // ACTIONCHANGEENEMYSTATUSRANDOM_H

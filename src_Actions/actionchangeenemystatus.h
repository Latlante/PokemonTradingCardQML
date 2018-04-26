#ifndef ACTIONCHANGEENEMYSTATUS_H
#define ACTIONCHANGEENEMYSTATUS_H

#include "abstractaction.h"

class ActionChangeEnemyStatus : public AbstractAction
{
public:
    explicit ActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

signals:

private:
    CardPokemon::Enum_statusOfPokemon m_status;
};

#endif // ACTIONCHANGEENEMYSTATUS_H

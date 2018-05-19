#ifndef ACTIONBLOCKONEENEMYATTACKFORONETURN_H
#define ACTIONBLOCKONEENEMYATTACKFORONETURN_H

#include "../abstractaction.h"

class ActionBlockOneEnemyAttackForOneTurn : public AbstractAction
{
public:
    ActionBlockOneEnemyAttackForOneTurn();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;
};

#endif // ACTIONBLOCKONEENEMYATTACKFORONETURN_H

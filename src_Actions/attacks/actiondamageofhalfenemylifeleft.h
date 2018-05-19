#ifndef ACTIONDAMAGEOFHALFENEMYLIFELEFT_H
#define ACTIONDAMAGEOFHALFENEMYLIFELEFT_H

#include "../abstractaction.h"

class ActionDamageOfHalfEnemyLifeLeft : public AbstractAction
{
public:
    ActionDamageOfHalfEnemyLifeLeft();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;
};

#endif // ACTIONDAMAGEOFHALFENEMYLIFELEFT_H

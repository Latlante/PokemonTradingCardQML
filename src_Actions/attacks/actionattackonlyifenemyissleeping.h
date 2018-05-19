#ifndef ACTIONATTACKONLYIFENEMYISSLEEPING_H
#define ACTIONATTACKONLYIFENEMYISSLEEPING_H

#include "../abstractaction.h"
#include "src_Cards/abstractcard.h"

class ActionAttackOnlyIfEnemyIsSleeping : public AbstractAction
{
public:
    ActionAttackOnlyIfEnemyIsSleeping(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONATTACKONLYIFENEMYISSLEEPING_H

#ifndef ACTIONMOREDAMAGEBYENEMYDAMAGE_H
#define ACTIONMOREDAMAGEBYENEMYDAMAGE_H

#include "../abstractaction.h"

class ActionMoreDamageByEnemyDamage : public AbstractAction
{
public:
    ActionMoreDamageByEnemyDamage(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONMOREDAMAGEBYENEMYDAMAGE_H

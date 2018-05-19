#ifndef ACTIONPROTECTEDAGAINSTDAMAGE_H
#define ACTIONPROTECTEDAGAINSTDAMAGE_H

#include "../abstractaction.h"

class ActionProtectedAgainstDamage : public AbstractAction
{
public:
    ActionProtectedAgainstDamage();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;
};

#endif // ACTIONPROTECTEDAGAINSTDAMAGE_H

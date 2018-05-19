#ifndef ACTIONPROTECTEDAGAINSTDAMAGERANDOM_H
#define ACTIONPROTECTEDAGAINSTDAMAGERANDOM_H

#include "../abstractaction.h"

class ActionProtectedAgainstDamageRandom : public AbstractAction
{
public:
    ActionProtectedAgainstDamageRandom();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;
};

#endif // ACTIONPROTECTEDAGAINSTDAMAGERANDOM_H

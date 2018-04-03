#ifndef ACTIONPROTECTEDAGAINSTDAMAGE_H
#define ACTIONPROTECTEDAGAINSTDAMAGE_H

#include "abstractaction.h"

class ActionProtectedAgainstDamage : public AbstractAction
{
public:
    ActionProtectedAgainstDamage();

    AbstractAction::Enum_typeOfAction type() override;
    void executeAction() override;
};

#endif // ACTIONPROTECTEDAGAINSTDAMAGE_H

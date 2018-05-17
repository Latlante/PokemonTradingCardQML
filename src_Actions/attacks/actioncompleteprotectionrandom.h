#ifndef ACTIONCOMPLETEPROTECTIONRANDOM_H
#define ACTIONCOMPLETEPROTECTIONRANDOM_H

#include "../abstractaction.h"

class ActionCompleteProtectionRandom : public AbstractAction
{
public:
    ActionCompleteProtectionRandom();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;
};

#endif // ACTIONCOMPLETEPROTECTIONRANDOM_H

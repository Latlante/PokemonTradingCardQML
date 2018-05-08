#ifndef ACTIONCOMPLETEPROTECTIONBYPAYINGONEENERGY_H
#define ACTIONCOMPLETEPROTECTIONBYPAYINGONEENERGY_H

#include "abstractaction.h"

class ActionCompleteProtectionByPayingOneEnergy : public AbstractAction
{
public:
    ActionCompleteProtectionByPayingOneEnergy();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;
};

#endif // ACTIONCOMPLETEPROTECTIONBYPAYINGONEENERGY_H
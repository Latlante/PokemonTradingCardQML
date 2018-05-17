#ifndef ACTIONCOMPLETEPROTECTIONBYPAYINGONEENERGY_H
#define ACTIONCOMPLETEPROTECTIONBYPAYINGONEENERGY_H

#include "../abstractaction.h"

class ActionCompleteProtectionByPayingOneEnergy : public AbstractAction
{
public:
    ActionCompleteProtectionByPayingOneEnergy(AbstractCard::Enum_element element);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    AbstractCard::Enum_element m_element;
};

#endif // ACTIONCOMPLETEPROTECTIONBYPAYINGONEENERGY_H

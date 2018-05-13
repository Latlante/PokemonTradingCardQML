#ifndef ACTIONREMOVEENERGYATTACHED_H
#define ACTIONREMOVEENERGYATTACHED_H

#include "../abstractaction.h"

class ActionRemoveEnergyAttached : public AbstractAction
{
public:
    ActionRemoveEnergyAttached(unsigned short numberOfEnergiesToRemoved, AbstractCard::Enum_element elementToRemove);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_numberOfEnergiesToRemoved;
    AbstractCard::Enum_element m_elementToRemove;
};

#endif // ACTIONREMOVEENERGYATTACHED_H

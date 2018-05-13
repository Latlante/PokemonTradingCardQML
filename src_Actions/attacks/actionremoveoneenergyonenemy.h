#ifndef ACTIONREMOVEONEENERGYONENEMY_H
#define ACTIONREMOVEONEENERGYONENEMY_H

#include "../abstractaction.h"

class ActionRemoveOneEnergyOnEnemy : public AbstractAction
{
public:
    ActionRemoveOneEnergyOnEnemy(unsigned short numberOfEnergiesToRemoved, AbstractCard::Enum_element elementToRemove);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_numberOfEnergiesToRemoved;
    AbstractCard::Enum_element m_elementToRemove;
};

#endif // ACTIONREMOVEONEENERGYONENEMY_H

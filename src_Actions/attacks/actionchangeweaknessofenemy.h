#ifndef ACTIONCHANGEWEAKNESSOFENEMY_H
#define ACTIONCHANGEWEAKNESSOFENEMY_H

#include "../abstractaction.h"
#include "src_Cards/abstractcard.h"

class ActionChangeWeaknessOfEnemy : public AbstractAction
{
public:
    ActionChangeWeaknessOfEnemy(AbstractCard::Enum_element element);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    AbstractCard::Enum_element m_element;
};

#endif // ACTIONCHANGEWEAKNESSOFENEMY_H

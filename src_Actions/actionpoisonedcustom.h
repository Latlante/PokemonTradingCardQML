#ifndef ACTIONPOISONEDCUSTOM_H
#define ACTIONPOISONEDCUSTOM_H

#include "abstractaction.h"

class ActionPoisonedCustom : public AbstractAction
{
public:
    ActionPoisonedCustom(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONPOISONEDCUSTOM_H

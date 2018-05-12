#ifndef ACTIONMOREDAMAGEBYENERGYONENEMY_H
#define ACTIONMOREDAMAGEBYENERGYONENEMY_H

#include "../abstractaction.h"

class ActionMoreDamageByEnergyOnEnemy : public AbstractAction
{
public:
    ActionMoreDamageByEnergyOnEnemy(unsigned short damageByEnergy);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damageByEnergy;
};

#endif // ACTIONMOREDAMAGEBYENERGYONENEMY_H

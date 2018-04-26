#ifndef ACTIONMOREDAMAGEBYENERGY_H
#define ACTIONMOREDAMAGEBYENERGY_H

#include "abstractaction.h"

class ActionMoreDamageByEnergy : public AbstractAction
{
public:
    ActionMoreDamageByEnergy(unsigned short damageByEnergy);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damageByEnergy;

};

#endif // ACTIONMOREDAMAGEBYENERGY_H

#ifndef ACTIONMOREDAMAGEBYENERGY_H
#define ACTIONMOREDAMAGEBYENERGY_H

#include "abstractaction.h"

class ActionMoreDamageByEnergy : public AbstractAction
{
public:
    ActionMoreDamageByEnergy(unsigned short damageByEnergy);

    AbstractAction::Enum_typeOfAction type() override;
    void executeAction() override;

private:
    unsigned short m_damageByEnergy;

};

#endif // ACTIONMOREDAMAGEBYENERGY_H

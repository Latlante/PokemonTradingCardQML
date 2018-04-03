#include "actionmoredamagebyenergy.h"

ActionMoreDamageByEnergy::ActionMoreDamageByEnergy(unsigned short damageByEnergy) :
    AbstractAction(),
    m_damageByEnergy(damageByEnergy)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionMoreDamageByEnergy::type()
{
    return AbstractAction::Action_MoreDamageByEnergy;
}

void ActionMoreDamageByEnergy::executeAction()
{

}

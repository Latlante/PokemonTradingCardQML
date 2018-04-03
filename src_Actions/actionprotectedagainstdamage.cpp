#include "actionprotectedagainstdamage.h"

ActionProtectedAgainstDamage::ActionProtectedAgainstDamage() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionProtectedAgainstDamage::type()
{
    return AbstractAction::Action_ProtectedAgainstDamage;
}

void ActionProtectedAgainstDamage::executeAction()
{

}

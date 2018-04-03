#include "actionremoveenergyattached.h"

#include "gamemanager.h"

ActionRemoveEnergyAttached::ActionRemoveEnergyAttached(unsigned short numberOfEnergiesToRemoved) :
    AbstractAction(),
    m_numberOfEnergiesToRemoved(numberOfEnergiesToRemoved)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionRemoveEnergyAttached::type()
{
    return AbstractAction::Action_RemoveOneEnergyAttached;
}

void ActionRemoveEnergyAttached::executeAction()
{

}

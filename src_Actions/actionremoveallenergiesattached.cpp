#include "actionremoveallenergiesattached.h"

ActionRemoveAllEnergiesAttached::ActionRemoveAllEnergiesAttached() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionRemoveAllEnergiesAttached::type()
{
    return AbstractAction::Action_RemoveAllEnergiesAttached;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionRemoveAllEnergiesAttached::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionRemoveAllEnergiesAttached::action()
{
    if(pokemonAttacking() != nullptr)
    {
        while(pokemonAttacking()->countEnergies() > 0)
            pokemonAttacking()->removeEnergy(0);
    }
}

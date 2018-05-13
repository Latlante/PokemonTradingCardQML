#include "actioncompleteprotectionbypayingoneenergy.h"

ActionCompleteProtectionByPayingOneEnergy::ActionCompleteProtectionByPayingOneEnergy() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionCompleteProtectionByPayingOneEnergy::type()
{
    return AbstractAction::Action_CompleteProtectionByPayingOneEnergy;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionCompleteProtectionByPayingOneEnergy::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionCompleteProtectionByPayingOneEnergy::action()
{
    if(pokemonAttacking() != nullptr)
        pokemonAttacking()->setInvincibleForTheNextTurn(true);
}

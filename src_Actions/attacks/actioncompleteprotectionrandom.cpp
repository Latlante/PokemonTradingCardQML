#include "actioncompleteprotectionrandom.h"

ActionCompleteProtectionRandom::ActionCompleteProtectionRandom() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionCompleteProtectionRandom::type()
{
    return AbstractAction::Action_CompleteProtectionRandom;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionCompleteProtectionRandom::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionCompleteProtectionRandom::action()
{
    if(pokemonAttacking() != nullptr)
    {
        unsigned short coin = headOrTail();

        if(coin == 1)
            pokemonAttacking()->setInvincibleForTheNextTurn(true);
    }
}

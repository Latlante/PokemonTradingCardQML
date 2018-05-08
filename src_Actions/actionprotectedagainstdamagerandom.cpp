#include "actionprotectedagainstdamagerandom.h"

ActionProtectedAgainstDamageRandom::ActionProtectedAgainstDamageRandom() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionProtectedAgainstDamageRandom::type()
{
    return AbstractAction::Action_ProtectedAgainstDamage;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionProtectedAgainstDamageRandom::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionProtectedAgainstDamageRandom::action()
{
    if(pokemonAttacking() != nullptr)
    {
        if(headOrTail() == 1)
            pokemonAttacking()->setProtectedAgainstDamageForTheNextTurn(true);
    }
}

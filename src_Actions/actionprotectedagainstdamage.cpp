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

QList<AbstractAction::Enum_ElementsToCheck> ActionProtectedAgainstDamage::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionProtectedAgainstDamage::action()
{
    if(pokemonAttacking() != nullptr)
        pokemonAttacking()->setProtectedAgainstDamageForTheNextTurn(true);
}

#include "actionnodamageonthreshold.h"

ActionNoDamageOnThreshold::ActionNoDamageOnThreshold(unsigned short threshold) :
    AbstractAction(),
    m_threshold(threshold)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionNoDamageOnThreshold::type()
{
    return AbstractAction::Action_NoDamageOnThreshold;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionNoDamageOnThreshold::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionNoDamageOnThreshold::action()
{
    if(pokemonAttacking() != nullptr)
        pokemonAttacking()->setProtectedAgainstDamageForTheNextTurn(m_threshold);
}

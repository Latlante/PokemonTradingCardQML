#include "actionhealing.h"

ActionHealing::ActionHealing(unsigned short pv) :
    AbstractAction(),
    m_pv(pv)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionHealing::type()
{
    return AbstractAction::Action_Healing;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionHealing::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionHealing::action()
{
    if(pokemonAttacking() != nullptr)
        pokemonAttacking()->restoreLife(m_pv);
}

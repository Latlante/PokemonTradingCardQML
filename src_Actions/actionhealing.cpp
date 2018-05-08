#include "actionhealing.h"

ActionHealing::ActionHealing(unsigned short pv, AbstractCard::Enum_element energyToPay) :
    AbstractAction(),
    m_pv(pv),
    m_energyToPay(energyToPay)
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

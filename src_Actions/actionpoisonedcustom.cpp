#include "actionpoisonedcustom.h"

ActionPoisonedCustom::ActionPoisonedCustom(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionPoisonedCustom::type()
{
    return AbstractAction::Action_PoisonedCustom;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionPoisonedCustom::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked;
}

void ActionPoisonedCustom::action()
{
    if(pokemonAttacked() != nullptr)
    {
        pokemonAttacked()->setDamagePoisonPerRound(m_damage);
        pokemonAttacked()->setStatus(CardPokemon::Status_Poisoned);
    }
}

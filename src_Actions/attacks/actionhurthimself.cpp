#include "actionhurthimself.h"

ActionHurtHimself::ActionHurtHimself(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionHurtHimself::type()
{
    return AbstractAction::Action_HurtHimself;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionHurtHimself::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionHurtHimself::action()
{
    if(pokemonAttacking() != nullptr)
        pokemonAttacking()->takeDamage(m_damage);
}

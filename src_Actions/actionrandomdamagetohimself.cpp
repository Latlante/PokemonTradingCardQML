#include "actionrandomdamagetohimself.h"

ActionRandomDamageToHimself::ActionRandomDamageToHimself(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionRandomDamageToHimself::type()
{
    return AbstractAction::Action_RandomDamageToHimself;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionRandomDamageToHimself::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionRandomDamageToHimself::action()
{
    if(pokemonAttacking() != nullptr)
    {
        if(headOrTail() == 0)
        {
            pokemonAttacking()->takeDamage(m_damage);
        }
    }
}

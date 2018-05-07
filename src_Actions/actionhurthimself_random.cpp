#include "actionhurthimself_random.h"

ActionHurtHimself_Random::ActionHurtHimself_Random(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionHurtHimself_Random::type()
{
    return AbstractAction::Action_HurtHimself_Random;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionHurtHimself_Random::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionHurtHimself_Random::action()
{
    if(pokemonAttacking() != nullptr)
    {
        if(headOrTail() == 0)
        {
            pokemonAttacking()->takeDamage(m_damage);
        }
    }
}

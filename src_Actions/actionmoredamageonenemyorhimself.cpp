#include "actionmoredamageonenemyorhimself.h"

ActionMoreDamageOnEnemyOrHimself::ActionMoreDamageOnEnemyOrHimself(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionMoreDamageOnEnemyOrHimself::type()
{
    return AbstractAction::Action_MoreDamageOnEnemyOrHimSelf;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionMoreDamageOnEnemyOrHimself::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionMoreDamageOnEnemyOrHimself::action()
{
    unsigned short coin = headOrTail();

    //Hurt the enemy
    if(coin == 1)
    {
        if(pokemonAttacked() != nullptr)
        {
            pokemonAttacked()->takeDamage(m_damage);
        }
    }
    //Hurt himself
    else
    {
        if(pokemonAttacking() != nullptr)
        {
            pokemonAttacking()->takeDamage(m_damage);
        }
    }
}

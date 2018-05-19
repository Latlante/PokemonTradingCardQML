#include "actionmoredamageorhurthimself.h"

ActionMoreDamageOrHurtHimSelf::ActionMoreDamageOrHurtHimSelf(unsigned short damageOnHead, unsigned short damageOnTail) :
    AbstractAction(),
    m_damageOnHead(damageOnHead),
    m_damageOnTail(damageOnTail)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionMoreDamageOrHurtHimSelf::type()
{
    return AbstractAction::Action_MoreDamageOrHurtHimSelf;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionMoreDamageOrHurtHimSelf::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionMoreDamageOrHurtHimSelf::actionAfterAttack()
{
    unsigned short coin = headOrTail();

    //Hurt the enemy
    if(coin == 1)
    {
        if(pokemonAttacked() != nullptr)
        {
            pokemonAttacked()->takeDamage(m_damageOnHead);
        }
    }
    //Hurt himself
    else
    {
        if(pokemonAttacking() != nullptr)
        {
            pokemonAttacking()->takeDamage(m_damageOnTail);
        }
    }
}

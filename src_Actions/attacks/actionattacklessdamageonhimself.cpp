#include "actionattacklessdamageonhimself.h"

ActionAttackLessDamageOnHimself::ActionAttackLessDamageOnHimself(unsigned short originalDamage, unsigned short damagePerMarquer) :
    AbstractAction(),
    m_originalDamage(originalDamage),
    m_damagePerMarquer(damagePerMarquer)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionAttackLessDamageOnHimself::type()
{
    return AbstractAction::Action_AttackLessDamageOnHimself;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionAttackLessDamageOnHimself::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionAttackLessDamageOnHimself::actionAfterAttack()
{
    if(pokemonAttacked() != nullptr)
    {
        unsigned short damageMarquer = pokemonAttacking()->damageMarker();
        unsigned short damageToMake = 0;
        unsigned short ownDamage = damageMarquer * m_damagePerMarquer;

        if(m_originalDamage < ownDamage)
            damageToMake = m_originalDamage - ownDamage;

        pokemonAttacked()->takeDamage(damageToMake);
    }
}


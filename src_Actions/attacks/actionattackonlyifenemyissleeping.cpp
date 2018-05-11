#include "actionattackonlyifenemyissleeping.h"

ActionAttackOnlyIfEnemyIsSleeping::ActionAttackOnlyIfEnemyIsSleeping(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionAttackOnlyIfEnemyIsSleeping::type()
{
    return AbstractAction::Action_AttackOnlyIfEnemyIsSleeping;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionAttackOnlyIfEnemyIsSleeping::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionAttackOnlyIfEnemyIsSleeping::action()
{
    if(pokemonAttacking() != nullptr)
        pokemonAttacking()->takeDamage(m_damage);
}

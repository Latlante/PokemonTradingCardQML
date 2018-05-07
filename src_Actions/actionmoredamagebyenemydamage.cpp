#include "actionmoredamagebyenemydamage.h"

ActionMoreDamageByEnemyDamage::ActionMoreDamageByEnemyDamage(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionMoreDamageByEnemyDamage::type()
{
    return AbstractAction::Action_MoreDamageByEnemyDamage;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionMoreDamageByEnemyDamage::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionMoreDamageByEnemyDamage::action()
{
    if(pokemonAttacked() != nullptr)
    {
        unsigned short damageMarquer = pokemonAttacked()->damageMarker();
        pokemonAttacked()->takeDamage(damageMarquer * m_damage);
    }
}

#include "actionmoredamagebyowndamage.h"

ActionMoreDamageByOwnDamage::ActionMoreDamageByOwnDamage(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionMoreDamageByOwnDamage::type()
{
    return AbstractAction::Action_MoreDamageByOwnDamage;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionMoreDamageByOwnDamage::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionMoreDamageByOwnDamage::action()
{
    if(pokemonAttacked() != nullptr)
    {
        unsigned short damageMarquer = pokemonAttacking()->damageMarker();
        pokemonAttacked()->takeDamage(damageMarquer * m_damage);
    }
}

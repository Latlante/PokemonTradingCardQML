#include "actionmoredamagebyenergyonenemy.h"

ActionMoreDamageByEnergyOnEnemy::ActionMoreDamageByEnergyOnEnemy(unsigned short damageByEnergy) :
    AbstractAction(),
    m_damageByEnergy(damageByEnergy)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionMoreDamageByEnergyOnEnemy::type()
{
    return AbstractAction::Action_MoreDamageByEnergyOnEnemy;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionMoreDamageByEnergyOnEnemy::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionMoreDamageByEnergyOnEnemy::actionAfterAttack()
{
    if((pokemonAttacking() != nullptr) && (pokemonAttacked() != nullptr))
    {
        unsigned short countEnergies = pokemonAttacked()->countEnergies();
        pokemonAttacked()->takeDamage(m_damageByEnergy * countEnergies);
    }
}

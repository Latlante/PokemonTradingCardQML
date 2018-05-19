#include "actionreplicatelastdamagetoenemy.h"

ActionReplicateLastDamageToEnemy::ActionReplicateLastDamageToEnemy() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionReplicateLastDamageToEnemy::type()
{
    return AbstractAction::Action_ReplicateLastDamageToEnemy;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionReplicateLastDamageToEnemy::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionReplicateLastDamageToEnemy::actionAfterAttack()
{
    if((pokemonAttacked() != nullptr) && (pokemonAttacking()))
        pokemonAttacked()->takeDamage(pokemonAttacking()->lastDamageReceived());
}

#include "actionreplicateoneattackfromenemy.h"

ActionReplicateOneAttackFromEnemy::ActionReplicateOneAttackFromEnemy() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionReplicateOneAttackFromEnemy::type()
{
    return AbstractAction::Action_ReplicateOneAttackFromEnemy;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionReplicateOneAttackFromEnemy::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionReplicateOneAttackFromEnemy::action()
{

}

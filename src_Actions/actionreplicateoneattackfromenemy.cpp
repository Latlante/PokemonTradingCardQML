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

void ActionReplicateOneAttackFromEnemy::executeAction()
{

}

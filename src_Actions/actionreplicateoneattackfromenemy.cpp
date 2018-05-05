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
            << AbstractAction::CheckGameManager
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionReplicateOneAttackFromEnemy::action()
{
    if(pokemonAttacked() != nullptr)
    {
        int indexAttackToReplicate = gameManager()->displayAttacks(pokemonAttacked());
        int indexLastAttack = pokemonAttacking()->lastIndexOfAttackUsed();

        if((indexAttackToReplicate >= 0) && (indexLastAttack >= 0) && (pokemonAttacking() != nullptr))
        {
            pokemonAttacking()->replaceOneAttack(indexLastAttack,
                                                 pokemonAttacked()->listAttacks()[indexAttackToReplicate]);
        }
        else
            qCritical() << __PRETTY_FUNCTION__
                        << "Impossible d'exécuter l'action, indexAttackToReplicate="
                        << indexAttackToReplicate
                        << ", indexLastAttack="
                        << indexLastAttack;
    }
}

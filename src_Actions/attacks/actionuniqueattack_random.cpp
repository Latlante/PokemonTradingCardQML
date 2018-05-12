#include "actionuniqueattack_random.h"

ActionUniqueAttack_Random::ActionUniqueAttack_Random(unsigned short index) :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionUniqueAttack_Random::type()
{
    return AbstractAction::Action_UniqueAttack_Random;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionUniqueAttack_Random::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionUniqueAttack_Random::action()
{
    if(pokemonAttacking() != nullptr)
    {
        unsigned short coin = headOrTail();

        if(coin == 0)
            pokemonAttacking()->setNumberOfTurnAttackStillBlocks(indexAttack(), 0xFFFF);
    }
}

#include "actiontrainer_totalguerison.h"

ActionTrainer_TotalGuerison::ActionTrainer_TotalGuerison() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionTrainer_TotalGuerison::type()
{
    return AbstractAction::ActionTrainer_TotalGuerison;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionTrainer_TotalGuerison::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionTrainer_TotalGuerison::action()
{
    if(pokemonAttacking() != nullptr)
    {
        pokemonAttacking()->setStatus(CardPokemon::Status_Normal);
    }
}

#include "actiontrainer_superpotion.h"

ActionTrainer_SuperPotion::ActionTrainer_SuperPotion() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionTrainer_SuperPotion::type()
{
    return AbstractAction::ActionTrainer_SuperPotion;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionTrainer_SuperPotion::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionTrainer_SuperPotion::action()
{
    if(pokemonAttacking() != nullptr)
    {
        pokemonAttacking()->restoreLife(40);
    }
}

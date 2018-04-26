#include "actionchangeenemystatus.h"

ActionChangeEnemyStatus::ActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status) :
    AbstractAction(),
    m_status(status)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionChangeEnemyStatus::type()
{
    return AbstractAction::Action_ChangeEnemyStatus;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionChangeEnemyStatus::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked;
}

void ActionChangeEnemyStatus::action()
{
    if(pokemonAttacked() != nullptr)
        pokemonAttacked()->setStatus(m_status);
}

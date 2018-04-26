#include "actionchangeenemystatusrandom.h"

ActionChangeEnemyStatusRandom::ActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon status) :
    AbstractAction(),
    m_status(status)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionChangeEnemyStatusRandom::type()
{
    return AbstractAction::Action_ChangeEnemyStatus_Random;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionChangeEnemyStatusRandom::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked;
}


void ActionChangeEnemyStatusRandom::action()
{
    if(pokemonAttacked() != nullptr)
    {
        if(headOrTail() == 1)
        {
            pokemonAttacked()->setStatus(m_status);
        }
    }
}

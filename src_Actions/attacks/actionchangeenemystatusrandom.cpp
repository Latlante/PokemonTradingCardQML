#include "actionchangeenemystatusrandom.h"

ActionChangeEnemyStatusRandom::ActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon statusOnHead, CardPokemon::Enum_statusOfPokemon statusOnTail) :
    AbstractAction(),
    m_statusOnHead(statusOnHead),
    m_statusOnTail(statusOnTail)
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


void ActionChangeEnemyStatusRandom::actionAfterAttack()
{
    if(pokemonAttacked() != nullptr)
    {
        if(headOrTail() == 1)
            pokemonAttacked()->setStatus(m_statusOnHead);
        else
            pokemonAttacked()->setStatus(m_statusOnTail);
    }
}

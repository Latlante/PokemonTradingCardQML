#include "actionenemypoisoned.h"

ActionEnemyPoisoned::ActionEnemyPoisoned(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionEnemyPoisoned::type()
{
    return AbstractAction::Action_EnemyPoisoned;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionEnemyPoisoned::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked;
}

void ActionEnemyPoisoned::action()
{
    if(pokemonAttacked() != nullptr)
    {
        pokemonAttacked()->setDamagePoisonPerRound(m_damage);
        pokemonAttacked()->setStatus(CardPokemon::Status_Poisoned);
    }
}

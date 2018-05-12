#include "actiondamageofhalfenemylifeleft.h"

ActionDamageOfHalfEnemyLifeLeft::ActionDamageOfHalfEnemyLifeLeft() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionDamageOfHalfEnemyLifeLeft::type()
{
    return AbstractAction::Action_DamageOfHalfEnemyLifeLeft;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionDamageOfHalfEnemyLifeLeft::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked
            << AbstractAction::CheckPokemonAttacking;
}

void ActionDamageOfHalfEnemyLifeLeft::action()
{
    if(pokemonAttacked() != nullptr)
    {
        unsigned short lifeLeftOnEnemy = pokemonAttacked()->lifeLeft();
        unsigned short damageToMake = lifeLeftOnEnemy / 2;

        if((damageToMake % 10) == 5)
            damageToMake -= 5;

        pokemonAttacked()->takeDamage(damageToMake);
    }
}

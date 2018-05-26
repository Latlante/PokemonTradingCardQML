#include "actionchangeweaknessofenemy.h"

ActionChangeWeaknessOfEnemy::ActionChangeWeaknessOfEnemy() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionChangeWeaknessOfEnemy::type()
{
    return AbstractAction::Action_ChangeWeaknessOfEnemy;
}

bool ActionChangeWeaknessOfEnemy::checkElements()
{
    return true;
}

void ActionChangeWeaknessOfEnemy::actionAfterAttack()
{
    /*if(pokemonAttacked() != nullptr)
        pokemonAttacked()->setWeaknessElement(m_element);*/
}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
QList<AbstractAction::Enum_ElementsToCheck> ActionChangeWeaknessOfEnemy::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked;
}

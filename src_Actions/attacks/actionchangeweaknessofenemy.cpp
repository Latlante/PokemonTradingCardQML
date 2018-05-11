#include "actionchangeweaknessofenemy.h"

ActionChangeWeaknessOfEnemy::ActionChangeWeaknessOfEnemy(AbstractCard::Enum_element element) :
    AbstractAction(),
    m_element(element)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionChangeWeaknessOfEnemy::type()
{
    return AbstractAction::Action_ChangeWeaknessOfEnemy;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionChangeWeaknessOfEnemy::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked;
}


void ActionChangeWeaknessOfEnemy::action()
{
    if(pokemonAttacked() != nullptr)
        pokemonAttacked()->setWeaknessElement(m_element);
}

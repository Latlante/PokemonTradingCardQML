#include "actionchangeresistanceofhimself.h"

ActionChangeResistanceOfHimself::ActionChangeResistanceOfHimself() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionChangeResistanceOfHimself::type()
{
    return AbstractAction::Action_ChangeResistanceOfHimself;
}

bool ActionChangeResistanceOfHimself::checkElements()
{
    return true;
}

void ActionChangeResistanceOfHimself::actionAfterAttack()
{
    /*if(pokemonAttacking() != nullptr)
        pokemonAttacking()->setResistanceElement(m_element);*/
}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
QList<AbstractAction::Enum_ElementsToCheck> ActionChangeResistanceOfHimself::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

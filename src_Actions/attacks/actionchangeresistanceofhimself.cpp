#include "actionchangeresistanceofhimself.h"

ActionChangeResistanceOfHimself::ActionChangeResistanceOfHimself(AbstractCard::Enum_element element) :
    AbstractAction(),
    m_element(element)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionChangeResistanceOfHimself::type()
{
    return AbstractAction::Action_ChangeResistanceOfHimself;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionChangeResistanceOfHimself::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}


void ActionChangeResistanceOfHimself::actionAfterAttack()
{
    if(pokemonAttacking() != nullptr)
        pokemonAttacking()->setResistanceElement(m_element);
}

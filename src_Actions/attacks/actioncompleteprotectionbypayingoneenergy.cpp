#include "actioncompleteprotectionbypayingoneenergy.h"

ActionCompleteProtectionByPayingOneEnergy::ActionCompleteProtectionByPayingOneEnergy(AbstractCard::Enum_element element) :
    AbstractAction(),
    m_element(element)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionCompleteProtectionByPayingOneEnergy::type()
{
    return AbstractAction::Action_CompleteProtectionByPayingOneEnergy;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionCompleteProtectionByPayingOneEnergy::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckGameManager
            << AbstractAction::CheckPokemonAttacking;
}

void ActionCompleteProtectionByPayingOneEnergy::actionBeforeAttack()
{
    if((gameManager() != nullptr) && (pokemonAttacking() != nullptr))
    {
        QList<CardEnergy*> listEnergies = gameManager()->displayEnergiesForAPokemon(pokemonAttacking(), 1, m_element);

        if(listEnergies.count() >= 1)
        {
            pokemonAttacking()->moveEnergiesInTrash(listEnergies);
            pokemonAttacking()->setInvincibleForTheNextTurn(true);
        }
    }
}

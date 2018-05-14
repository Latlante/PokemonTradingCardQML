#include "actionremoveenergyattached.h"

#include "gamemanager.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packettrash.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"

ActionRemoveEnergyAttached::ActionRemoveEnergyAttached(unsigned short numberOfEnergiesToRemoved, AbstractCard::Enum_element elementToRemove) :
    AbstractAction(),
    m_numberOfEnergiesToRemoved(numberOfEnergiesToRemoved),
    m_elementToRemove(elementToRemove)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionRemoveEnergyAttached::type()
{
    return AbstractAction::Action_RemoveEnergyAttached;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionRemoveEnergyAttached::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckGameManager
            << AbstractAction::CheckPokemonAttacking;
}

void ActionRemoveEnergyAttached::action()
{
    if(pokemonAttacking() != nullptr)
    {
        //Si on a plus d'énergies que demandé, on choisit lesquels on veut enlever
        if(pokemonAttacking()->countEnergies() > m_numberOfEnergiesToRemoved)
        {
            QList<int> listIndex = gameManager()->displayEnergiesForAPokemon(pokemonAttacking(), calculOfNumberOfEnergyToRemoved, CardPokemon::Element_Whatever);
            pokemonAttacking()->moveEnergiesInTrash(listIndex);
        }
        //Sinon on enléve tout
        else
        {
            pokemonAttacking()->moveAllEnergiesInTrash();
        }
    }
}

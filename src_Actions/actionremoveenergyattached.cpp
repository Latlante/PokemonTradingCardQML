#include "actionremoveenergyattached.h"

#include "gamemanager.h"
#include "src_Packets/fightarea.h"
#include "src_Cards/cardpokemon.h"

ActionRemoveEnergyAttached::ActionRemoveEnergyAttached(unsigned short numberOfEnergiesToRemoved) :
    AbstractAction(),
    m_numberOfEnergiesToRemoved(numberOfEnergiesToRemoved)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionRemoveEnergyAttached::type()
{
    return AbstractAction::Action_RemoveOneEnergyAttached;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionRemoveEnergyAttached::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionRemoveEnergyAttached::action()
{
    if(pokemonAttacking() != nullptr)
    {
        int numberOfEnergyRemoved = 0;

        while((numberOfEnergyRemoved < m_numberOfEnergiesToRemoved) && (pokemonAttacking()->countEnergies() > 0))
        {
            pokemonAttacking()->removeEnergy(0);
            numberOfEnergyRemoved++;
        }
    }
}

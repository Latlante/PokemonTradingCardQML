#include "actionremoveoneenergyonenemy.h"

#include "gamemanager.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packettrash.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"

ActionRemoveOneEnergyOnEnemy::ActionRemoveOneEnergyOnEnemy(unsigned short numberOfEnergiesToRemoved, AbstractCard::Enum_element elementToRemove) :
    AbstractAction(),
    m_numberOfEnergiesToRemoved(numberOfEnergiesToRemoved),
    m_elementToRemove(elementToRemove)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionRemoveOneEnergyOnEnemy::type()
{
    return AbstractAction::Action_RemoveOneEnergyOnEnemy;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionRemoveOneEnergyOnEnemy::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacked;
}

void ActionRemoveOneEnergyOnEnemy::action()
{
    if(pokemonAttacked() != nullptr)
    {
        //Si on a plus d'énergies que demandé, on choisit lesquels on veut enlever
        if(pokemonAttacked()->countEnergies() > m_numberOfEnergiesToRemoved)
        {
            QList<int> listIndex = gameManager()->displayEnergiesForAPokemon(pokemonAttacked(), m_numberOfEnergiesToRemoved, m_elementToRemove);
            pokemonAttacked()->moveEnergiesInTrash(listIndex);
        }
        //Sinon on enléve tout
        else
        {
            pokemonAttacked()->moveAllEnergiesInTrash();
        }
    }
}

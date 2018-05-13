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
            << AbstractAction::CheckPokemonAttacking;
}

void ActionRemoveEnergyAttached::action()
{
    if(pokemonAttacking() != nullptr)
    {
        Player* playerAttacking = pokemonAttacking()->owner();

        if(playerAttacking != nullptr)
        {
            PacketTrash* trash = playerAttacking->trash();

            if(trash != nullptr)
            {
                int numberOfEnergyRemoved = 0;

                while((numberOfEnergyRemoved < m_numberOfEnergiesToRemoved) && (pokemonAttacking()->countEnergies() > 0))
                {
                    CardEnergy* energy = pokemonAttacking()->takeEnergy(0);
                    trash->addNewCard(energy);
                    numberOfEnergyRemoved++;
                }
            }
        }
    }
}

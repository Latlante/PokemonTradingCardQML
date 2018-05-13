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
        Player* playerAttacked = pokemonAttacked()->owner();

        if(playerAttacked != nullptr)
        {
            PacketTrash* trash = playerAttacked->trash();

            if(trash != nullptr)
            {
                int numberOfEnergyRemoved = 0;

                while((numberOfEnergyRemoved < m_numberOfEnergiesToRemoved) && (pokemonAttacked()->countEnergies() > 0))
                {
                    CardEnergy* energy = pokemonAttacked()->takeEnergy(0);
                    trash->addNewCard(energy);
                    numberOfEnergyRemoved++;
                }
            }
        }
    }
}

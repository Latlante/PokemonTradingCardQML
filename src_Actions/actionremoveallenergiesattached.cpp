#include "actionremoveallenergiesattached.h"

#include "gamemanager.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packettrash.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"

ActionRemoveAllEnergiesAttached::ActionRemoveAllEnergiesAttached() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionRemoveAllEnergiesAttached::type()
{
    return AbstractAction::Action_RemoveAllEnergiesAttached;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionRemoveAllEnergiesAttached::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking;
}

void ActionRemoveAllEnergiesAttached::action()
{
    if(pokemonAttacking() != nullptr)
    {
        Player* playerAttacking = pokemonAttacking()->owner();

        if(playerAttacking != nullptr)
        {
            PacketTrash* trash = playerAttacking->trash();

            if(trash != nullptr)
            {
                while(pokemonAttacking()->countEnergies() > 0)
                {
                    CardEnergy* energy = pokemonAttacking()->takeEnergy(0);
                    trash->addNewCard(energy);
                }
            }
        }
    }
}

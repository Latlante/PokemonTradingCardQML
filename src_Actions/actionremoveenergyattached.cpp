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

void ActionRemoveEnergyAttached::executeAction()
{
    GameManager *manager = GameManager::instance();

    if(manager != NULL)
    {
        Player* playerAttacking = manager->currentPlayer();

        if(playerAttacking != NULL)
        {
            FightArea *fightAr = playerAttacking->fight();

            if(fightAr != NULL)
            {
                CardPokemon *pokemonAttacking = fightAr->pokemonFighter();

                if(pokemonAttacking != NULL)
                {
                    int numberOfEnergyRemoved = 0;

                    while((numberOfEnergyRemoved < m_numberOfEnergiesToRemoved) && (pokemonAttacking->countEnergies() > 0))
                    {
                        pokemonAttacking->removeEnergy(0);
                        numberOfEnergyRemoved++;
                    }
                }
                else
                    qCritical() << __PRETTY_FUNCTION__ << ", pokemonAttacking is NULL";
            }
            else
                qCritical() << __PRETTY_FUNCTION__ << ", fightAr is NULL";
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << ", playerAttacking is NULL";
    }
    else
        qCritical() << __PRETTY_FUNCTION__ << ", manager is NULL";
}

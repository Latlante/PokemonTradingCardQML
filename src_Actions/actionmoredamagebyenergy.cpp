#include "actionmoredamagebyenergy.h"
#include "gamemanager.h"
#include "src_Packets/fightarea.h"
#include "src_Cards/cardpokemon.h"

ActionMoreDamageByEnergy::ActionMoreDamageByEnergy(unsigned short damageByEnergy) :
    AbstractAction(),
    m_damageByEnergy(damageByEnergy)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionMoreDamageByEnergy::type()
{
    return AbstractAction::Action_MoreDamageByEnergy;
}

void ActionMoreDamageByEnergy::executeAction()
{
    bool status = false;
    unsigned short countEnergies = 0;
    GameManager *manager = GameManager::instance();

    if(manager != NULL)
    {
        Player* playerAttacking = manager->currentPlayer();

        if(playerAttacking != NULL)
        {
            FightArea *fightArPlayerAttacking = playerAttacking->fight();

            if(fightArPlayerAttacking != NULL)
            {
                CardPokemon *pokemonAttacking = fightArPlayerAttacking->pokemonFighter();

                if(pokemonAttacking != NULL)
                {
                    AbstractCard::Enum_element elementEnergy = pokemonAttacking->element();
                    countEnergies = pokemonAttacking->countEnergies(elementEnergy);
                    status = true;
                }
                else
                    qCritical() << __PRETTY_FUNCTION__ << ", pokemonAttacking is NULL";
            }
            else
                qCritical() << __PRETTY_FUNCTION__ << ", fightAr of playerAttacking is NULL";
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << ", playerAttacking is NULL";


        if(status == true)
        {
            Player* playerAttacked = manager->currentPlayer();

            if(playerAttacked != NULL)
            {
                FightArea *fightArPlayerAttacked = playerAttacked->fight();

                if(fightArPlayerAttacked != NULL)
                {
                    CardPokemon *pokemonAttacked = fightArPlayerAttacked->pokemonFighter();

                    if(pokemonAttacked != NULL)
                    {
                        pokemonAttacked->takeDamage(m_damageByEnergy * countEnergies);
                    }
                    else
                        qCritical() << __PRETTY_FUNCTION__ << ", pokemonAttacked is NULL";
                }
                else
                    qCritical() << __PRETTY_FUNCTION__ << ", fightAr of playerAttacked is NULL";
            }
            else
                qCritical() << __PRETTY_FUNCTION__ << ", playerAttacked is NULL";
        }

    }
    else
        qCritical() << __PRETTY_FUNCTION__ << ", manager is NULL";
}

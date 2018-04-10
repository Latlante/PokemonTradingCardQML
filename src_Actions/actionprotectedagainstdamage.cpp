#include "actionprotectedagainstdamage.h"
#include "gamemanager.h"
#include "src_Packets/fightarea.h"
#include "src_Cards/cardpokemon.h"

ActionProtectedAgainstDamage::ActionProtectedAgainstDamage() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionProtectedAgainstDamage::type()
{
    return AbstractAction::Action_ProtectedAgainstDamage;
}

void ActionProtectedAgainstDamage::executeAction()
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
                    pokemonAttacking->setInvincibleForTheNextTurn(true);
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

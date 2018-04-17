#include "actionmoredamageonenemyorhimself.h"

#include <QDebug>
#include "gamemanager.h"
#include "src_Cards/cardpokemon.h"
#include "src_Packets/fightarea.h"
#include "utils.h"

ActionMoreDamageOnEnemyOrHimself::ActionMoreDamageOnEnemyOrHimself(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionMoreDamageOnEnemyOrHimself::type()
{
    return AbstractAction::Action_MoreDamageOnEnemyOrHimSelf;
}

void ActionMoreDamageOnEnemyOrHimself::executeAction()
{
    GameManager *manager = GameManager::instance();

    if(manager != NULL)
    {
        unsigned short coin = Utils::headOrTail();

        //Hurt the enemy
        if(coin == 1)
        {
            Player* playerAttacked = manager->playerAttacked();

            if(playerAttacked != NULL)
            {
                FightArea *fightAr = playerAttacked->fight();

                if(fightAr != NULL)
                {
                    CardPokemon *pokemonAttacked = fightAr->pokemonFighter();

                    if(pokemonAttacked != NULL)
                    {
                        pokemonAttacked->takeDamage(m_damage);
                    }
                    else
                        qCritical() << __PRETTY_FUNCTION__ << ", pokemonAttacked is NULL";
                }
                else
                    qCritical() << __PRETTY_FUNCTION__ << ", fightAr is NULL";
            }
            else
                qCritical() << __PRETTY_FUNCTION__ << ", playerAttacked is NULL";
        }
        //Hurt himself
        else
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
                        pokemonAttacking->takeDamage(m_damage);
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
    }
    else
        qCritical() << __PRETTY_FUNCTION__ << ", manager is NULL";

}

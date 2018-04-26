#include "actiondamagemultipliedbytripleheadortail.h"
#include "gamemanager.h"
#include "src_Packets/fightarea.h"
#include "src_Cards/cardpokemon.h"

ActionDamageMultipliedByTripleHeadOrTail::ActionDamageMultipliedByTripleHeadOrTail(unsigned short damageByHead) :
    AbstractAction(),
    m_damageByHead(damageByHead)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionDamageMultipliedByTripleHeadOrTail::type()
{
    return AbstractAction::Action_DamageMultipliedByTripleHeadOrTail;
}

void ActionDamageMultipliedByTripleHeadOrTail::executeAction()
{
    GameManager *manager = GameManager::instance();

    if(manager != NULL)
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
                    unsigned short totalDamage = 0;
                    //Tout est Ok
                    for(int i=0;i<3;++i)
                    {
                        unsigned short coin = manager->headOrTail();
                        if(coin == 1)
                            totalDamage += m_damageByHead;
                    }

                    pokemonAttacked->takeDamage(totalDamage);
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
    else
        qCritical() << __PRETTY_FUNCTION__ << ", manager is NULL";
}

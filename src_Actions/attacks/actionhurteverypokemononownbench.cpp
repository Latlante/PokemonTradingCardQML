#include "actionhurteverypokemononownbench.h"

ActionHurtEveryPokemonOnOwnBench::ActionHurtEveryPokemonOnOwnBench(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionHurtEveryPokemonOnOwnBench::type()
{
    return AbstractAction::Action_HurtEveryPokemonOnOwnBench;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionHurtEveryPokemonOnOwnBench::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckBenchPlayerAttacking;
}

void ActionHurtEveryPokemonOnOwnBench::actionAfterAttack()
{
    if(benchPlayerAttacking() != nullptr)
    {
        for(int i=0;i<benchPlayerAttacking()->countCard();++i)
        {
            AbstractCard* abCard = benchPlayerAttacking()->card(i);

            if(abCard->type() == CardPokemon::TypeOfCard_Pokemon)
            {
                CardPokemon* cardPok = static_cast<CardPokemon*>(abCard);

                if(cardPok != nullptr)
                {
                    cardPok->takeDamage(m_damage);
                }
            }
        }
    }
}

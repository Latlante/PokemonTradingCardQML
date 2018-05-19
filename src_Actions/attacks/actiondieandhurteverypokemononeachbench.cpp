#include "actiondieandhurteverypokemononeachbench.h"

ActionDieAndHurtEveryPokemonOnEachBench::ActionDieAndHurtEveryPokemonOnEachBench(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionDieAndHurtEveryPokemonOnEachBench::type()
{
    return AbstractAction::Action_DieAndHurtEveryPokemonOnEachBench;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionDieAndHurtEveryPokemonOnEachBench::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking
            << AbstractAction::CheckBenchPlayerAttacking
            << AbstractAction::CheckBenchPlayerAttacked;
}

void ActionDieAndHurtEveryPokemonOnEachBench::actionAfterAttack()
{
    if(pokemonAttacking() != nullptr)
        pokemonAttacking()->takeDamage(pokemonAttacking()->lifeTotal());

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

    if(benchPlayerAttacked() != nullptr)
    {
        for(int i=0;i<benchPlayerAttacked()->countCard();++i)
        {
            AbstractCard* abCard = benchPlayerAttacked()->card(i);

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

#include "actiondestruction.h"

ActionDestruction::ActionDestruction(unsigned short damage) :
    AbstractAction(),
    m_damage(damage)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionDestruction::type()
{
    return AbstractAction::Action_Destruction;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionDestruction::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPokemonAttacking
            << AbstractAction::CheckBenchPlayerAttacking;
}

void ActionDestruction::action()
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

    if(pokemonAttacking() != nullptr)
        pokemonAttacking()->takeDamage(pokemonAttacking()->lifeTotal());
}

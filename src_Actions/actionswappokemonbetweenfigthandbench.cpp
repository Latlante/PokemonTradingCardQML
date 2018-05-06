#include "actionswappokemonbetweenfigthandbench.h"

ActionSwapPokemonBetweenFigthAndBench::ActionSwapPokemonBetweenFigthAndBench() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionSwapPokemonBetweenFigthAndBench::type()
{
    return AbstractAction::Action_SwapPokemonBetweenFigthAndBench;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionSwapPokemonBetweenFigthAndBench::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPlayerAttacked
            << AbstractAction::CheckBenchPlayerAttacked;
}

void ActionSwapPokemonBetweenFigthAndBench::action()
{
    if((pokemonAttacked() != nullptr) && (benchPlayerAttacked() != nullptr))
    {
        if(benchPlayerAttacked()->countCard() > 0)
        {
            AbstractCard* cardFigther = playerAttacked()->fight()->takeACard(0);
            //m_gameManager->display();
            //playerAttacked()->move

        }
    }
}
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
            QList<AbstractCard*> listPokemonChoose = gameManager()->displayBench(benchPlayerAttacked());

            if((listPokemonChoose.count() >= 1) && (listPokemonChoose.first()->type() == AbstractCard::TypeOfCard_Pokemon))
                playerAttacked()->swapCardsBetweenBenchAndFight(static_cast<CardPokemon*>(listPokemonChoose.first()));
        }
    }
}

#ifndef ACTIONSWAPPOKEMONBETWEENFIGTHANDBENCH_H
#define ACTIONSWAPPOKEMONBETWEENFIGTHANDBENCH_H

#include "abstractaction.h"

class ActionSwapPokemonBetweenFigthAndBench : public AbstractAction
{
public:
    ActionSwapPokemonBetweenFigthAndBench();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;
};

#endif // ACTIONSWAPPOKEMONBETWEENFIGTHANDBENCH_H

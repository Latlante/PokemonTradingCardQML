#ifndef ACTIONDIEANDHURTEVERYPOKEMONONEACHBENCH_H
#define ACTIONDIEANDHURTEVERYPOKEMONONEACHBENCH_H

#include "abstractaction.h"

class ActionDieAndHurtEveryPokemonOnEachBench : public AbstractAction
{
public:
    ActionDieAndHurtEveryPokemonOnEachBench(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONDIEANDHURTEVERYPOKEMONONEACHBENCH_H

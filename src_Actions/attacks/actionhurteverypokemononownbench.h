#ifndef ACTIONHURTEVERYPOKEMONONOWNBENCH_H
#define ACTIONHURTEVERYPOKEMONONOWNBENCH_H

#include "../abstractaction.h"

class ActionHurtEveryPokemonOnOwnBench : public AbstractAction
{
public:
    ActionHurtEveryPokemonOnOwnBench(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONHURTEVERYPOKEMONONOWNBENCH_H

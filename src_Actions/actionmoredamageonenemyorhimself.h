#ifndef ACTIONMOREDAMAGEONENEMYORHIMSELF_H
#define ACTIONMOREDAMAGEONENEMYORHIMSELF_H

#include "abstractaction.h"

class ActionMoreDamageOnEnemyOrHimself : public AbstractAction
{
public:
    ActionMoreDamageOnEnemyOrHimself(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONMOREDAMAGEONENEMYORHIMSELF_H

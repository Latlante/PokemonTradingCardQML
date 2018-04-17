#ifndef ACTIONMOREDAMAGEONENEMYORHIMSELF_H
#define ACTIONMOREDAMAGEONENEMYORHIMSELF_H

#include "abstractaction.h"

class ActionMoreDamageOnEnemyOrHimself : public AbstractAction
{
public:
    ActionMoreDamageOnEnemyOrHimself(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    void executeAction() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONMOREDAMAGEONENEMYORHIMSELF_H

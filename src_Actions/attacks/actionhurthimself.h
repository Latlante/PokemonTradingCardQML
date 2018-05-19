#ifndef ACTIONHURTHIMSELF_H
#define ACTIONHURTHIMSELF_H

#include "../abstractaction.h"

class ActionHurtHimself : public AbstractAction
{
public:
    ActionHurtHimself(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONHURTHIMSELF_H

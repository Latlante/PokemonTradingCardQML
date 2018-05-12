#ifndef ACTIONATTACKLESSDAMAGEONHIMSELF_H
#define ACTIONATTACKLESSDAMAGEONHIMSELF_H

#include "../abstractaction.h"

class ActionAttackLessDamageOnHimself : public AbstractAction
{
public:
    ActionAttackLessDamageOnHimself(unsigned short originalDamage, unsigned short damagePerMarquer);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_originalDamage;
    unsigned short m_damagePerMarquer;
};

#endif // ACTIONATTACKLESSDAMAGEONHIMSELF_H

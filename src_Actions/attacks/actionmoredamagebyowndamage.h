#ifndef ACTIONMOREDAMAGEBYOWNDAMAGE_H
#define ACTIONMOREDAMAGEBYOWNDAMAGE_H

#include "../abstractaction.h"

class ActionMoreDamageByOwnDamage : public AbstractAction
{
public:
    ActionMoreDamageByOwnDamage(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONMOREDAMAGEBYOWNDAMAGE_H

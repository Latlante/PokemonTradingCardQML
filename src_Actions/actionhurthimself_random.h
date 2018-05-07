#ifndef ACTIONHURTHIMSELF_RANDOM_H
#define ACTIONHURTHIMSELF_RANDOM_H

#include "abstractaction.h"

class ActionHurtHimself_Random : public AbstractAction
{
public:
    ActionHurtHimself_Random(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONHURTHIMSELF_RANDOM_H

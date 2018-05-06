#ifndef ACTIONRANDOMDAMAGETOHIMSELF_H
#define ACTIONRANDOMDAMAGETOHIMSELF_H

#include "abstractaction.h"

class ActionRandomDamageToHimself : public AbstractAction
{
public:
    ActionRandomDamageToHimself(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONRANDOMDAMAGETOHIMSELF_H

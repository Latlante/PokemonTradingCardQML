#ifndef ACTIONDESTRUCTION_H
#define ACTIONDESTRUCTION_H

#include "abstractaction.h"

class ActionDestruction : public AbstractAction
{
public:
    ActionDestruction(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONDESTRUCTION_H

#ifndef ACTIONHEALING_H
#define ACTIONHEALING_H

#include "abstractaction.h"

class ActionHealing : public AbstractAction
{
public:
    ActionHealing(unsigned short pv);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_pv;
};

#endif // ACTIONHEALING_H

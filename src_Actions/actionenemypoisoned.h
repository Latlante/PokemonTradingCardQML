#ifndef ACTIONENEMYPOISONED_H
#define ACTIONENEMYPOISONED_H

#include "abstractaction.h"

class ActionEnemyPoisoned : public AbstractAction
{
public:
    ActionEnemyPoisoned(unsigned short damage);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damage;
};

#endif // ACTIONENEMYPOISONED_H

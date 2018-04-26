#ifndef ACTIONREPLICATEONEATTACKFROMENEMY_H
#define ACTIONREPLICATEONEATTACKFROMENEMY_H

#include "abstractaction.h"

class ActionReplicateOneAttackFromEnemy : public AbstractAction
{
public:
    ActionReplicateOneAttackFromEnemy();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;
};

#endif // ACTIONREPLICATEONEATTACKFROMENEMY_H

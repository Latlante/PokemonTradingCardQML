#ifndef ACTIONREPLICATEONEATTACKFROMENEMY_H
#define ACTIONREPLICATEONEATTACKFROMENEMY_H

#include "abstractaction.h"

class ActionReplicateOneAttackFromEnemy : public AbstractAction
{
public:
    ActionReplicateOneAttackFromEnemy();

    AbstractAction::Enum_typeOfAction type() override;
    void executeAction() override;
};

#endif // ACTIONREPLICATEONEATTACKFROMENEMY_H

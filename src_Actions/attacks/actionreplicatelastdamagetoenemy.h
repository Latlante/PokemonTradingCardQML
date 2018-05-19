#ifndef ACTIONREPLICATELASTDAMAGETOENEMY_H
#define ACTIONREPLICATELASTDAMAGETOENEMY_H

#include "../abstractaction.h"

class ActionReplicateLastDamageToEnemy : public AbstractAction
{
public:
    ActionReplicateLastDamageToEnemy();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;
};

#endif // ACTIONREPLICATELASTDAMAGETOENEMY_H

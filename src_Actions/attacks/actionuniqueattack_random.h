#ifndef ACTIONUNIQUEATTACK_RANDOM_H
#define ACTIONUNIQUEATTACK_RANDOM_H

#include "../abstractaction.h"

class ActionUniqueAttack_Random : public AbstractAction
{
public:
    ActionUniqueAttack_Random(unsigned short index);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;
};

#endif // ACTIONUNIQUEATTACK_RANDOM_H

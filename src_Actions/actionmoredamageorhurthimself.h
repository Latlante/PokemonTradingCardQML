#ifndef ACTIONMOREDAMAGEORHURTHIMSELF_H
#define ACTIONMOREDAMAGEORHURTHIMSELF_H

#include "abstractaction.h"

class ActionMoreDamageOrHurtHimSelf : public AbstractAction
{
public:
    ActionMoreDamageOrHurtHimSelf(unsigned short damageOnHead, unsigned short damageOnTail);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damageOnHead;
    unsigned short m_damageOnTail;
};

#endif // ACTIONMOREDAMAGEORHURTHIMSELF_H

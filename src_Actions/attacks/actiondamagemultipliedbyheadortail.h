#ifndef ACTIONDAMAGEMULTIPLIEDBYHEADORTAIL_H
#define ACTIONDAMAGEMULTIPLIEDBYHEADORTAIL_H

#include "../abstractaction.h"

class ActionDamageMultipliedByHeadOrTail : public AbstractAction
{
public:
    ActionDamageMultipliedByHeadOrTail(unsigned short damageByHead, unsigned short numberOfCoins);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;

private:
    unsigned short m_damageByHead;
    unsigned short m_numberOfCoins;
};

#endif // ACTIONDAMAGEMULTIPLIEDBYHEADORTAIL_H

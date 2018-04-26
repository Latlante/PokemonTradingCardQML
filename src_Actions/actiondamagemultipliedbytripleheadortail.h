#ifndef ACTIONDAMAGEMULTIPLIEDBYTRIPLEHEADORTAIL_H
#define ACTIONDAMAGEMULTIPLIEDBYTRIPLEHEADORTAIL_H

#include "abstractaction.h"

class ActionDamageMultipliedByTripleHeadOrTail : public AbstractAction
{
public:
    ActionDamageMultipliedByTripleHeadOrTail(unsigned short damageByHead);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_damageByHead;
};

#endif // ACTIONDAMAGEMULTIPLIEDBYTRIPLEHEADORTAIL_H

#ifndef ACTIONDAMAGEMULTIPLIEDBYTRIPLEHEADORTAIL_H
#define ACTIONDAMAGEMULTIPLIEDBYTRIPLEHEADORTAIL_H

#include "abstractaction.h"

class ActionDamageMultipliedByTripleHeadOrTail : public AbstractAction
{
public:
    ActionDamageMultipliedByTripleHeadOrTail(unsigned short damageByHead);

    AbstractAction::Enum_typeOfAction type() override;
    void executeAction() override;

private:
    unsigned short m_damageByHead;
};

#endif // ACTIONDAMAGEMULTIPLIEDBYTRIPLEHEADORTAIL_H

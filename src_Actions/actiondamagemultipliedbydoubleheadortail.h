#ifndef ACTIONDAMAGEMULTIPLIEDBYDOUBLEHEADORTAIL_H
#define ACTIONDAMAGEMULTIPLIEDBYDOUBLEHEADORTAIL_H

#include "abstractaction.h"

class ActionDamageMultipliedByDoubleHeadOrTail : public AbstractAction
{
public:
    ActionDamageMultipliedByDoubleHeadOrTail(unsigned short damageByHead);

    AbstractAction::Enum_typeOfAction type() override;
    void executeAction() override;

private:
    unsigned short m_damageByHead;
};

#endif // ACTIONDAMAGEMULTIPLIEDBYDOUBLEHEADORTAIL_H

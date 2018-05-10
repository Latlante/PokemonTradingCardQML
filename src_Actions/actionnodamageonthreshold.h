#ifndef ACTIONNODAMAGEONTHRESHOLD_H
#define ACTIONNODAMAGEONTHRESHOLD_H

#include "abstractaction.h"

class ActionNoDamageOnThreshold : public AbstractAction
{
public:
    ActionNoDamageOnThreshold(unsigned short threshold);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;

private:
    unsigned short m_threshold;
};

#endif // ACTIONNODAMAGEONTHRESHOLD_H

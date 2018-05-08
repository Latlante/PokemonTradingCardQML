#ifndef ACTIONREMOVEALLENERGIESATTACHED_H
#define ACTIONREMOVEALLENERGIESATTACHED_H

#include "abstractaction.h"

class ActionRemoveAllEnergiesAttached : public AbstractAction
{
public:
    ActionRemoveAllEnergiesAttached();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;
};

#endif // ACTIONREMOVEALLENERGIESATTACHED_H

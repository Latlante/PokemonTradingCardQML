#ifndef ACTIONREMOVEENERGYATTACHED_H
#define ACTIONREMOVEENERGYATTACHED_H

#include "abstractaction.h"

class ActionRemoveEnergyAttached : public AbstractAction
{
public:
    ActionRemoveEnergyAttached(unsigned short numberOfEnergiesToRemoved);

    AbstractAction::Enum_typeOfAction type() override;
    void executeAction() override;

private:
    unsigned short m_numberOfEnergiesToRemoved;
};

#endif // ACTIONREMOVEENERGYATTACHED_H

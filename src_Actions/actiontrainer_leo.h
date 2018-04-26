#ifndef ACTIONTRAINER_LEO_H
#define ACTIONTRAINER_LEO_H

#include "abstractaction.h"

class ActionTrainer_Leo : public AbstractAction
{
    Q_OBJECT
public:
    ActionTrainer_Leo();

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void action() override;
};

#endif // ACTIONTRAINER_LEO_H

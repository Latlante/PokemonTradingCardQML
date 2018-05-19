#ifndef ACTIONCHANGERESISTANCEOFHIMSELF_H
#define ACTIONCHANGERESISTANCEOFHIMSELF_H

#include "../abstractaction.h"
#include "src_Cards/abstractcard.h"

class ActionChangeResistanceOfHimself : public AbstractAction
{
public:
    ActionChangeResistanceOfHimself(AbstractCard::Enum_element element);

    AbstractAction::Enum_typeOfAction type() override;
    QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() override;
    void actionAfterAttack() override;

private:
    AbstractCard::Enum_element m_element;
};

#endif // ACTIONCHANGERESISTANCEOFHIMSELF_H

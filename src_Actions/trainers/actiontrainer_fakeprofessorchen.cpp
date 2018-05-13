#include "actiontrainer_fakeprofessorchen.h"

ActionTrainer_FakeProfessorChen::ActionTrainer_FakeProfessorChen() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionTrainer_FakeProfessorChen::type()
{
    return AbstractAction::ActionTrainer_FakeProfessorChen;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionTrainer_FakeProfessorChen::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPlayerAttacked;
}

void ActionTrainer_FakeProfessorChen::action()
{
    if(playerAttacked() != nullptr)
    {
        for(int i=0;i<7;++i)
        {
            playerAttacked()->drawOneCard();
        }
    }
}

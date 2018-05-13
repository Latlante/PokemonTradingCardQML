#include "actiontrainer_professorchen.h"

ActionTrainer_ProfessorChen::ActionTrainer_ProfessorChen()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionTrainer_ProfessorChen::type()
{
    return AbstractAction::ActionTrainer_ProfessorChen;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionTrainer_ProfessorChen::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckPlayerAttacking;
}

void ActionTrainer_ProfessorChen::action()
{
    if(playerAttacking() != nullptr)
    {
        for(int i=0;i<7;++i)
        {
            playerAttacking()->drawOneCard();
        }
    }
}

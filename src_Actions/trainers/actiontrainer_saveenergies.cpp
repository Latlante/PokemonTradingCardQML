#include "actiontrainer_saveenergies.h"

ActionTrainer_SaveEnergies::ActionTrainer_SaveEnergies() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionTrainer_SaveEnergies::type()
{
    return AbstractAction::ActionTrainer_SaveEnergies;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionTrainer_SaveEnergies::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckGameManager
            << AbstractAction::CheckPlayerAttacking;
}

void ActionTrainer_SaveEnergies::action()
{
    if((gameManager() != nullptr) && (playerAttacking() != nullptr))
    {
        //On défausse 1 carte de la main
        QList<AbstractCard*> listCardsHand = gameManager()->displayHand(playerAttacking()->hand(), 1);
        foreach(AbstractCard* card, listCardsHand)
            playerAttacking()->moveCardFromHandToTrash(card);

        //On récupére 2 cartes énergies de la pile de défausse
        QList<AbstractCard*> listCardsTrash = gameManager()->displayTrash(playerAttacking()->trash(), 2, AbstractCard::TypeOfCard_Energy);
        foreach(AbstractCard* card, listCardsTrash)
            playerAttacking()->moveCardFromTrashToHand(card);
    }
}

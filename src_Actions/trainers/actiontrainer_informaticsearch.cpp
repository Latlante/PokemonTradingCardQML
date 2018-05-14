#include "actiontrainer_informaticsearch.h"

#include "src_Packets/packetdeck.h"

ActionTrainer_InformaticSearch::ActionTrainer_InformaticSearch() :
    AbstractAction()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractAction::Enum_typeOfAction ActionTrainer_InformaticSearch::type()
{
    return AbstractAction::ActionTrainer_InformaticSearch;
}

QList<AbstractAction::Enum_ElementsToCheck> ActionTrainer_InformaticSearch::elementToCheck()
{
    return QList<AbstractAction::Enum_ElementsToCheck>()
            << AbstractAction::CheckGameManager
            << AbstractAction::CheckPlayerAttacking;
}

void ActionTrainer_InformaticSearch::action()
{
    if((gameManager() != nullptr) && (playerAttacking() != nullptr))
    {
        QList<int> listCardSelected = gameManager()->displayHand(playerAttacking()->hand(), 2);
        QList<int> listCardsDeck = gameManager()->displayDeck(playerAttacking()->deck(), 1);
        playerAttacking()->deck()->mixCards();
    }
}

#include "ctrlgameboard.h"
#include <QEventLoop>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#include <QtQml/qqml.h>

#include "player.h"
#include "src_Cards/cardpokemon.h"
#include "src_Controler/ctrlselectingcards.h"
#include "src_Models/factorymainpageloader.h"
#include "src_Models/listplayers.h"
#include "src_Models/modelpopupselectcardinpacket.h"
#include "src_Packets/bencharea.h"
#include "src_Packets/packetdeck.h"

CtrlGameBoard::CtrlGameBoard(CtrlSelectingCards &ctrlSelectCards, CtrlPopups &ctrlPopups, QObject *parent) :
    QObject(parent),
#ifdef TESTS_UNITAIRES
    m_gameManager(GameManager::createInstance()),
#else
    m_gameManager(GameManager::createInstance(ctrlPopups)),
#endif
    m_factoryMainPageLoader(new FactoryMainPageLoader()),
    m_ctrlSelectingCards(ctrlSelectCards)
{
    //initGame();
    connect(&m_ctrlSelectingCards, &CtrlSelectingCards::listsComplete, this, &CtrlGameBoard::onListsComplete_CtrlSelectingCards);
    connect(m_gameManager, &GameManager::indexCurrentPlayerChanged, this, &CtrlGameBoard::currentPlayerChanged);
    connect(m_gameManager, &GameManager::gameStatusChanged, this, &CtrlGameBoard::gameStatusChanged);
}

CtrlGameBoard::~CtrlGameBoard()
{
    delete m_factoryMainPageLoader;
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void CtrlGameBoard::declareQML()
{
    qmlRegisterUncreatableType<CtrlGameBoard>("model", 1, 0, "CtrlGameBoard", "CtrlGameBoard error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
bool CtrlGameBoard::install(QQmlApplicationEngine *pEngine)
{
    qDebug() << "installing controleur...";

    bool bInstalled = false;

    if (NULL != pEngine)
    {
        QQmlContext* pContext = pEngine->rootContext();
        if (NULL != pContext)
        {
            bInstalled = true;
            qDebug() << "CtrlGameBoard is installed in QML engine";
            pContext->setContextProperty("ctrlGameBoard", this);
        }
        else
        {
            qCritical() << "Qml context is null.";
        }
    }

    return bInstalled;
}

Player* CtrlGameBoard::currentPlayer()
{
    return m_gameManager->currentPlayer();
}

ConstantesQML::StepGame CtrlGameBoard::gameStatus()
{
    return m_gameManager->gameStatus();
}

ListPlayers* CtrlGameBoard::newListPlayers()
{
    return new ListPlayers();
}

FactoryMainPageLoader* CtrlGameBoard::factory()
{
    return m_factoryMainPageLoader;
}

void CtrlGameBoard::initGame()
{
    m_gameManager->initGame();
}

Player* CtrlGameBoard::playerAt(int index)
{
    return m_gameManager->playerAt(index);
}

void CtrlGameBoard::onClicked_ButtonOk_SelectPlayers(QStringList listOfPlayers)
{
    m_factoryMainPageLoader->displaySelectCards();
    m_ctrlSelectingCards.selectCards(listOfPlayers);

    /*for(int i=0;i<listOfPlayers.count();++i)
    {
        m_ctrlSelectingCards.newSelection(listOfPlayers[i], i == (listOfPlayers.count()-1));

        QEventLoop loop;
        connect(this, &CtrlGameBoard::nextPlayer, &loop, &QEventLoop::quit);
        loop.exec();
    }*/
}

void CtrlGameBoard::displaySelectingCardsForNextPlayers()
{
    //emit nextPlayer();
}

void CtrlGameBoard::onClicked_ButtonOk_SelectCards()
{
    //initGame();

    m_factoryMainPageLoader->displayBoard();
}

void CtrlGameBoard::onClicked_ButtonReadyPreparation()
{
    m_gameManager->setInitReady();
}

void CtrlGameBoard::actionAttack(CardPokemon *card)
{
    //Choix de l'attaque
    //Player* playerAttacking = card->owner();
    //Player* playerAttacked = m_gameManager->ennemyOf(playerAttacking);
    int indexAttack = m_gameManager->displayAttacks(card);

    if(indexAttack < 4)         //Correspond à une attaque
    {
        //Le pokémon attaquant attaque
        CardPokemon::Enum_StatusOfAttack statusOfAttack = m_gameManager->attack(card, indexAttack);

        switch(statusOfAttack)
        {
        case CardPokemon::Attack_OK:
            m_gameManager->endOfTurn();
            break;
        case CardPokemon::Attack_AttackBlocked:
            m_gameManager->displayMessage("Impossible d'utiliser cette attaque pendant ce tour");
            break;
        case CardPokemon::Attack_NotEnoughEnergies:
            m_gameManager->displayMessage("Vous n'avez pas assez d'énergies");
            break;
        case CardPokemon::Attack_WrongStatus:
            m_gameManager->displayMessage("Vous ne pouvez pas attaquer pendant que vous êtes " + card->statusFormatString());
            break;
        case CardPokemon::Attack_IndexNOK:
            qCritical() << __PRETTY_FUNCTION__ << "Erreur d'index";
            break;
        case CardPokemon::Attack_UnknownError:
            qCritical() << __PRETTY_FUNCTION__ << "Erreur inconnue";
            break;
        }

    }
    else if(indexAttack == 4)   //Correspond à la retraite
    {
        bool success = m_gameManager->retreat(card);

        if(success == false)
            qCritical() << __PRETTY_FUNCTION__ << "Erreur lors de l'échange";
    }
    else
    {
        qCritical() << __PRETTY_FUNCTION__ << "erreur de indexAttack=" << indexAttack;
    }
}

void CtrlGameBoard::actionFinishYourTurn()
{
    m_gameManager->endOfTurn();
}

/************************************************************
*****             FONCTIONS SLOTS PRIVEES				*****
************************************************************/
void CtrlGameBoard::onListsComplete_CtrlSelectingCards()
{
    QMap<QString,QList<AbstractCard*> > listCardsByPlayer = m_ctrlSelectingCards.listCardsByPlayer();

    for(int i=0;i<listCardsByPlayer.keys().count();++i)
    {
        QString name = listCardsByPlayer.keys()[i];
        m_gameManager->addNewPlayer(name, listCardsByPlayer[name]);
    }

    m_gameManager->initGame();
    m_factoryMainPageLoader->displayBoard();
    m_gameManager->displayMessage("Préparez votre jeu");

}


#include "ctrlgameboard.h"
#include <QEventLoop>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#include <QtQml/qqml.h>

#include "src_Models/factorymainpageloader.h"
#include "gamemanager.h"
#include "player.h"
#include "src_Controler/ctrlselectingcards.h"
#include "src_Models/listplayers.h"
#include "src_Packets/bencharea.h"
#include "src_Packets/packetdeck.h"

CtrlGameBoard::CtrlGameBoard(CtrlSelectingCards &ctrlSelectCards, QObject *parent) :
    QObject(parent),
    m_gameManager(GameManager::createInstance()),
    m_factoryMainPageLoader(new FactoryMainPageLoader()),
    m_ctrlSelectingCards(ctrlSelectCards)
{
    //initGame();
    connect(&m_ctrlSelectingCards, &CtrlSelectingCards::listsComplete, this, &CtrlGameBoard::onListsComplete_CtrlSelectingCards);
    connect(m_gameManager, &GameManager::indexCurrentPlayerChanged, this, &CtrlGameBoard::currentPlayerChanged);
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
            qDebug() << "FeaturesManagementVision is installed in QML engine";
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

ListPlayers* CtrlGameBoard::newListPlayers()
{
    return new ListPlayers();
}

FactoryMainPageLoader* CtrlGameBoard::factory()
{
    return m_factoryMainPageLoader;
}

void CtrlGameBoard::initGame(QStringList listOfPlayers)
{
    /*QString nom = "Corentin";
    QList<AbstractCard*> listCards = m_gameManager->chooseCards(listOfPlayers[0]);
    Player* playerCorentin = m_gameManager->addNewPlayer(nom, listCards);

    nom = "Alice";
    listCards = m_gameManager->chooseCards(listOfPlayers[1]);
    Player* playerAlice = m_gameManager->addNewPlayer(nom, listCards);*/



    m_gameManager->initGame();
}

Player* CtrlGameBoard::createPlayer(const QString &name)
{
    //qDebug() << __PRETTY_FUNCTION__ << name;
    QList<AbstractCard*> listCards = m_gameManager->chooseCards(name);
    return m_gameManager->addNewPlayer(name, listCards);
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

void CtrlGameBoard::onClicked_ButtonAttack()
{
    //Procédure de fin de tour

    //Le pokémon attaquant attaque
    Player* playerAttacking = m_gameManager->currentPlayer();
    Player* playerAttacked = m_gameManager->playerAttacked();

    m_gameManager->attack(playerAttacking, 0, playerAttacked);

    //Si le pokémon attaqué est mort, le joueur pioche sa récompense

        //On vérifie les conditions de victoires

        //S'il n'y a pas de victoire, le joueur attaqué remplace le pokémon

    //On passe au prochain tour
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
}

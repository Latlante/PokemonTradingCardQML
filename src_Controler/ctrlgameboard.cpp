#include "ctrlgameboard.h"
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#include <QtQml/qqml.h>

#include "src_Models/factorymainpageloader.h"
#include "gamemanager.h"
#include "player.h"
#include "src_Models/listplayers.h"
#include "src_Packets/bencharea.h"
#include "src_Packets/packetdeck.h"

CtrlGameBoard::CtrlGameBoard(QObject *parent) :
    QObject(parent),
    m_gameManager(GameManager::createInstance()),
    m_factoryMainPageLoader(new FactoryMainPageLoader())
{
    //initGame();
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
    QString nom = "Corentin";
    QList<AbstractCard*> listCards = m_gameManager->chooseCards(listOfPlayers[0]);
    Player* playerCorentin = m_gameManager->addNewPlayer(nom, listCards);

    nom = "Alice";
    listCards = m_gameManager->chooseCards(listOfPlayers[1]);
    Player* playerAlice = m_gameManager->addNewPlayer(nom, listCards);

    m_gameManager->initGame();
}

Player* CtrlGameBoard::createPlayer(const QString &name)
{
    //qDebug() << __PRETTY_FUNCTION__ << name;
    QList<AbstractCard*> listCards = m_gameManager->chooseCards(name);
    return m_gameManager->addNewPlayer(name, listCards);
}

BenchArea* CtrlGameBoard::benchArea_P1()
{
    Player* play = m_gameManager->playerAt(0);
    BenchArea* bench = NULL;

    if(play != NULL)
    {
        bench = play->bench();
    }

    return bench;
}

PacketDeck* CtrlGameBoard::deck_P1()
{
    Player* play = m_gameManager->playerAt(0);
    PacketDeck* deck = NULL;

    if(play != NULL)
    {
        deck = play->deck();
    }

    return deck;
}

Player* CtrlGameBoard::playerAt(int index)
{
    return m_gameManager->playerAt(index);
}

void CtrlGameBoard::onClicked_ButtonOk_SelectPlayers(QStringList listOfPlayers)
{
    initGame(listOfPlayers);

    m_factoryMainPageLoader->displaySelectCards();
}

void CtrlGameBoard::onClicked_ButtonOk_SelectCards()
{
    m_factoryMainPageLoader->displayBoard();
}

#include "gamemanager.h"

#include <QDebug>
#include "src_Cards/abstractcard.h"
#include "src_Cards/cardpokemon.h"
#include "src_Packets/fightarea.h"
#include "dlgselectcards.h"
#include "utils.h"

const int GameManager::m_NUMBER_FIRST_CARDS = 10;
const int GameManager::m_NUMBER_REWARDS = 6;
GameManager* GameManager::m_instance = NULL;

GameManager::GameManager(QObject *parent) :
	QObject(parent),
	m_listPlayers(QList<Player*>()),
	m_indexCurrentPlayer(0),
    m_playerAttacking(nullptr),
    m_playerAttacked(nullptr),
	m_gameIsReady(false)
{
	
}

GameManager::~GameManager()
{
	
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
GameManager* GameManager::createInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new GameManager();
    }

    return m_instance;
}

void GameManager::deleteInstance()
{
    if(m_instance != NULL)
    {
        delete m_instance;
        m_instance = NULL;
    }
}

GameManager* GameManager::instance()
{
    return m_instance;
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
void GameManager::initGame()
{
	//Création de 2 joueurs pour le moment
    /*QStringList listNames = QStringList() << "Corentin" << "Alice";
	
	for(int i=0;i<listNames.count();++i)
	{
		//Création du deck
        //QList<AbstractCard*> listCards = chooseCards(listNames[i]);
		
		//Création du nouveau joueur
        //addNewPlayer(listNames[i], listCards);



		

        drawFirstCards();

    }*/

    //Mise en place des récompenses
    foreach(Player *play, m_listPlayers)
    {
        for(int i=0;i<m_NUMBER_REWARDS;++i)
        {
            play->moveCardFromDeckToReward();
        }
    }

    //Distribution de la première main
    drawFirstCards();
	
	//On choisit le joueur qui va jouer en premier
	selectFirstPlayer();
}

QList<AbstractCard*> GameManager::chooseCards(const QString& name)
{
	//Connecter à la fenêtre de sélection
    QList<AbstractCard*> listCards;
    DlgSelectCards *fen = new DlgSelectCards(name);
#ifdef MODE_TEST
    listCards = fen->listOfRandomCards();
#else
    fen->exec();
    listCards = fen->listOfSelectedCards();
#endif

    delete fen;

    return listCards;
}

Player *GameManager::addNewPlayer(QString name, QList<AbstractCard*> listCards)
{
	Player* newPlayer = new Player(name, listCards);

    connect(newPlayer, &Player::endOfTurn, this, &GameManager::onEndOfTurn_Player);

	m_listPlayers.append(newPlayer);

    return newPlayer;
}

Player* GameManager::currentPlayer()
{
    /*Player* playerPlaying = NULL;

    foreach(Player *play, m_listPlayers)
    {
        if (true == play->isPlaying())
        {
            playerPlaying = play;
            break;
        }
    }

    return playerPlaying;*/
    return m_playerAttacking;
}

Player* GameManager::playerAttacked()
{
    /*Player* playerPlaying = NULL;

    foreach(Player *play, m_listPlayers)
    {
        if (false == play->isPlaying())
        {
            playerPlaying = play;
            break;
        }
    }

    return playerPlaying;*/
    return m_playerAttacked;
}

Player* GameManager::playerAt(int index)
{
    Player* play = NULL;

    if((index >= 0) && (index < m_listPlayers.count()))
    {
        play = m_listPlayers[index];
    }
    else
    {
        qCritical() << __PRETTY_FUNCTION__ << "Erreur avec le Player" << index << "/" << m_listPlayers.count();
    }

    return play;
}

void GameManager::startGame()
{
    onEndOfTurn_Player();
}

void GameManager::drawFirstCards()
{
    //qDebug() << "count Players:" << m_listPlayers.count();
    foreach(Player *play, m_listPlayers)
    {
        for(int i=0;i<m_NUMBER_FIRST_CARDS;++i)
        {
            play->drawOneCard();
        }
    }
}

void GameManager::selectFirstPlayer()
{
    int indexCurrentPlayer = Utils::selectFirstPlayer(m_listPlayers.count());
    setIndexCurrentPlayer(indexCurrentPlayer);
}

void GameManager::nextPlayer()
{	
    /*m_indexCurrentPlayer++;
	if (m_listPlayers.count() <= m_indexCurrentPlayer)
		m_indexCurrentPlayer = 0;
		
    m_listPlayers[m_indexCurrentPlayer]->newTurn();*/
    setIndexCurrentPlayer(m_indexCurrentPlayer+1);
    currentPlayer()->newTurn();
}

void GameManager::attack(Player *playAttacking, unsigned short index, Player *playAttacked)
{
    CardPokemon *pokemonAttacking = playAttacking->fight()->pokemonFighting(0);
    CardPokemon *pokemonAttacked = playAttacked->fight()->pokemonFighting(0);

    qDebug() << __PRETTY_FUNCTION__ << pokemonAttacking->name() << " Attack " << pokemonAttacked->name();
    pokemonAttacking->tryToAttack(index, pokemonAttacked);
}

void GameManager::endOfTurn()
{
	foreach(Player* play, m_listPlayers)
	{
		play->blockPlayer();
	}
}

bool GameManager::gameIsFinished()
{
	bool hasAWinner = false;
	
	foreach(Player* play, m_listPlayers)
	{
		hasAWinner |= play->isWinner();
	}
	
	return hasAWinner;
}

/************************************************************
*****			  FONCTIONS SLOTS PRIVEES				*****
************************************************************/
void GameManager::onEndOfTurn_Player()
{
    //On bloque tous les joueurs
    foreach(Player* play, m_listPlayers)
        play->blockPlayer();

    //On vérifie si quelqu'un a gagné
    bool hasAWinner = false;

    foreach(Player* play, m_listPlayers)
        hasAWinner |= play->isWinner();

    //S'il n'y a pas encore de vainqueur, on laisse le prochain joueur jouer
    if(hasAWinner == false)
    {
        nextPlayer();
    }
    else
    {
        foreach(Player* play, m_listPlayers)
        {
            if(play->isWinner())
            {
                qDebug() << "VICTOIRE DE " << play->name();
            }
        }

    }
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
void GameManager::setIndexCurrentPlayer(int index)
{
    //Sécurité pour ne pas dépasser l'index
    index = index % m_listPlayers.count();

    if(m_indexCurrentPlayer != index)
    {
        m_indexCurrentPlayer = index;
        emit indexCurrentPlayerChanged();

        //A REVOIR
        if(index == 0)
        {
            m_playerAttacking = m_listPlayers[0];
            m_playerAttacked = m_listPlayers[1];
        }
        else
        {
            m_playerAttacking = m_listPlayers[1];
            m_playerAttacked = m_listPlayers[0];
        }
    }

}

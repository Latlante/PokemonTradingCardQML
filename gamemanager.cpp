#include "gamemanager.h"

#include <QDebug>
#include "src_Controler/ctrlpopups.h"
#include "src_Cards/cardpokemon.h"
#include "src_Models/modellistenergies.h"
#include "src_Packets/bencharea.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packethand.h"
#include "src_Packets/packetrewards.h"
#include "src_Packets/packettrash.h"
#include "utils.h"

const int GameManager::m_NUMBER_FIRST_CARDS = 10;
const int GameManager::m_NUMBER_REWARDS = 6;
GameManager* GameManager::m_instance = nullptr;

#ifdef TESTS_UNITAIRES
GameManager::GameManager(QObject *parent) :
    QObject(parent),
    m_forcedValueHeadOrTail(false),
    m_nextValueHeadOrTail(0),
#else
GameManager::GameManager(CtrlPopups &ctrlPopups, QObject *parent) :
    QObject(parent),
    m_ctrlPopups(ctrlPopups),
#endif
	m_listPlayers(QList<Player*>()),
    m_indexCurrentPlayer(-1),
    m_playerAttacking(nullptr),
    m_playerAttacked(nullptr),
    m_gameStatus(ConstantesQML::StepPreparation),
	m_gameIsReady(false)
{
	
}

GameManager::~GameManager()
{
	
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
#ifdef TESTS_UNITAIRES
GameManager* GameManager::createInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new GameManager();
    }

    return m_instance;
}
#else
GameManager* GameManager::createInstance(CtrlPopups &ctrlPopups)
{
    if(m_instance == NULL)
    {
        m_instance = new GameManager(ctrlPopups);
    }

    return m_instance;
}
#endif

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
//ACCESSEURS
Player* GameManager::currentPlayer()
{
    return m_playerAttacking;
}

Player* GameManager::playerAttacked()
{
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

ConstantesQML::StepGame GameManager::gameStatus()
{
    return m_gameStatus;
}

void GameManager::setGameStatus(ConstantesQML::StepGame step)
{
    if(m_gameStatus != step)
    {
        m_gameStatus = step;
        emit gameStatusChanged();
    }
}

//PREPARATION DE LA PARTIE
void GameManager::initGame()
{
    //Mise en place des récompenses
    foreach(Player *play, m_listPlayers)
    {
        for(int i=0;i<m_NUMBER_REWARDS;++i)
        {
            play->moveCardFromDeckToReward();
        }
    }

    //Distribution de la première main
    if(checkHandOfEachPlayer() == true)
    {
        //On choisit le joueur qui va jouer en premier
        selectFirstPlayer();
    }
    else
    {
        //On arrête le jeu
        setGameStatus(ConstantesQML::StepFinished);
    }
}

Player *GameManager::addNewPlayer(QString name, QList<AbstractCard*> listCards)
{
	Player* newPlayer = new Player(name, listCards);

    connect(newPlayer, &Player::endOfTurn, this, &GameManager::onEndOfTurn_Player);

	m_listPlayers.append(newPlayer);

    return newPlayer;
}


void GameManager::startGame()
{
    onEndOfTurn_Player();
}


void GameManager::selectFirstPlayer()
{
#ifdef TESTS_UNITAIRES
    setIndexCurrentPlayer(0);
#else
    int indexCurrentPlayer = Utils::selectFirstPlayer(m_listPlayers.count());
    setIndexCurrentPlayer(indexCurrentPlayer);
#endif
}

void GameManager::nextPlayer()
{	
    /*m_indexCurrentPlayer++;
	if (m_listPlayers.count() <= m_indexCurrentPlayer)
		m_indexCurrentPlayer = 0;
		
    m_listPlayers[m_indexCurrentPlayer]->newTurn();*/
    setIndexCurrentPlayer(m_indexCurrentPlayer+1);
    checkStatusPokemonForNewRound();
    currentPlayer()->newTurn();
    currentPlayer()->drawOneCard();
}

void GameManager::attack(CardPokemon *pokemonAttacking, unsigned short index)
{
    CardPokemon::Enum_StatusOfAttack statusOfAttack = CardPokemon::Attack_UnknownError;

    if(pokemonAttacking != nullptr)
    {
        Player* playerAttacked = enemyOf(pokemonAttacking->owner());

        if(playerAttacked != nullptr)
        {
            CardPokemon *pokemonAttacked = playerAttacked->fight()->pokemonFighting(0);

            qDebug() << __PRETTY_FUNCTION__ << pokemonAttacking->name() << " Attack " << pokemonAttacked->name();
            statusOfAttack = pokemonAttacking->tryToAttack(index, pokemonAttacked);

            qDebug() << "Résultat du combat:" << static_cast<int>(statusOfAttack);
            qDebug() << "\t-> Attaquant:" << pokemonAttacking->name() << " - " << pokemonAttacking->lifeLeft() << "/" << pokemonAttacking->lifeTotal() << " - " << pokemonAttacking->status();
            qDebug() << "\t-> Attaqué:" << pokemonAttacked->name() << " - " << pokemonAttacked->lifeLeft() << "/" << pokemonAttacked->lifeTotal() << " - " << pokemonAttacked->status();
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << "playerAttacked is null";
    }
    else
        qCritical() << __PRETTY_FUNCTION__ << "pokemonAttacking is null";
}

bool GameManager::retreat(CardPokemon *pokemonToRetreat)
{
    bool success = false;
    QList<int> listIndexBench;

    //On revérifie qu'on peut
    if(pokemonToRetreat->canRetreat() == true)
    {
        Player* playerAttacking = pokemonToRetreat->owner();
        if(playerAttacking != nullptr)
        {
            if(pokemonToRetreat->costRetreat() > 0)
            {
                //On sélectionne les énergies à mettre dans la pile de défausse
                QList<int> listIndexEnergies = displayEnergiesForAPokemon(pokemonToRetreat, pokemonToRetreat->costRetreat(), AbstractCard::Element_Whatever);
                QList<CardEnergy*> listEnergies;
                ModelListEnergies* modelEnergies = pokemonToRetreat->modelListOfEnergies();

                //On les récupére sans les supprimer du modèle pour ne pas décaler l'index
                foreach(int index, listIndexEnergies)
                    listEnergies.append(modelEnergies->energy(index));

                //Maintenant on peut les supprimer
                foreach(int index, listIndexEnergies)
                    modelEnergies->takeEnergy(index);

                //Maintenant on peut les placer dans la défausse
                foreach(CardEnergy* energy, listEnergies)
                    playerAttacking->trash()->addNewCard(energy);
            }

            listIndexBench = displayBench(playerAttacking->bench());
            success = playerAttacking->swapCardsBetweenBenchAndFight(listIndexBench.first());
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << "pokemonToRetreat->owner() is null";

    }
    else
        qCritical() << __PRETTY_FUNCTION__ << "pokemonToRetreat->canRetreat() is false";

    return success;
}

void GameManager::endOfTurn()
{
    //On débloque des attaques si besoin
    checkAttacksBlocked();

    //Application du poison s'il y a
    checkPokemonPoisoned();

    //Si le pokémon attaqué est mort, le joueur pioche sa récompense
    checkPokemonDead();

    //On vérifie les conditions de victoires
    Player* playerWinner = gameIsFinished();
    if(playerWinner != nullptr)
    {
        qDebug() << "VICTOIRE DE " << playerWinner->name();
    }
    else
    {
        //On passe au prochain tour
        nextPlayer();
    }
}

Player* GameManager::gameIsFinished()
{
    //Conditions de victoire:
    //  -> Plus de récompense à piocher
    //  -> Plus de carte dans le deck
    //  -> Plus de pokémon sur la banc
    Player* playWinner = nullptr;
	
#ifndef TESTS_UNITAIRES
	foreach(Player* play, m_listPlayers)
	{
        if(play->isWinner())
            playWinner = play;
	}
#endif
	
    return playWinner;
}

QList<int> GameManager::displayBench(BenchArea *bench)
{
#ifdef TESTS_UNITAIRES
    Q_UNUSED(card)
    return QList<int>() << 0;
#else
    return m_ctrlPopups.displayBench(bench);
#endif
}

QList<int> GameManager::displayEnergiesForAPokemon(CardPokemon* pokemon, unsigned short quantity, AbstractCard::Enum_element element)
{
#ifdef TESTS_UNITAIRES
    Q_UNUSED(card)
    return QList<int>() << 0;
#else
    return m_ctrlPopups.displayEnergiesForAPokemon(pokemon, quantity, element);
#endif
}

int GameManager::displayAttacks(CardPokemon* card, bool blockRetreat)
{
#ifdef TESTS_UNITAIRES
    Q_UNUSED(card)
    return 0;
#else
    bool authorizeRetreat = false;

    if(blockRetreat == false)
        authorizeRetreat = card->canRetreat();

    return m_ctrlPopups.displayAttacks(card, authorizeRetreat);
#endif
}

#ifdef TESTS_UNITAIRES
void GameManager::setForcedValueHeadOrTail(bool forced, unsigned short value)
{
    m_forcedValueHeadOrTail = forced;
    m_nextValueHeadOrTail = value;
}

unsigned short GameManager::headOrTail()
{
    if(m_forcedValueHeadOrTail)
        return m_nextValueHeadOrTail;

    return Utils::headOrTail();
}
#else
unsigned short GameManager::headOrTail()
{
    return Utils::headOrTail();
}
#endif

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

    //qDebug() << __PRETTY_FUNCTION__ << m_indexCurrentPlayer << index;

    if(m_indexCurrentPlayer != index)
    {
        m_indexCurrentPlayer = index;

        m_playerAttacking = m_listPlayers[index];
        m_playerAttacked = enemyOf(m_playerAttacking);

        emit indexCurrentPlayerChanged();
    }
}

Player* GameManager::enemyOf(Player *play)
{
    Player* playerEnnemy = nullptr;

    //A REVOIR
    if(play == m_listPlayers[0])
    {
        playerEnnemy = m_listPlayers[1];
    }
    else if(play == m_listPlayers[1])
    {
        playerEnnemy = m_listPlayers[0];
    }

    return playerEnnemy;
}

bool GameManager::checkHandOfEachPlayer()
{
    foreach(Player* play, m_listPlayers)
    {
        unsigned short bonusCards = 0;

        drawFirstCards(play);

        //Si la main n'est pas bonne:
        //  -> on remet les cartes dans le deck
        //  -> on repioche
        //  -> les autres joueurs ont le droit à une carte en plus
        while((play->hand()->isFirstHandOk() == false) && (bonusCards < 5))
        {
            play->moveAllCardFromHandToDeck();
            drawFirstCards(play);
            bonusCards++;
        }

        if(bonusCards > 0)
        {
            foreach(Player* playBonusCard, m_listPlayers)
            {
                if(play != playBonusCard)
                {
                    for(int i=0;i<bonusCards;++i)
                    {
                        playBonusCard->drawOneCard();
                    }
                }
            }
        }
    }

    return true;
}

void GameManager::drawFirstCards(Player* play)
{
    for(int i=0;i<m_NUMBER_FIRST_CARDS;++i)
    {
        play->drawOneCard();
    }
}

void GameManager::checkPokemonPoisoned()
{
    foreach (Player* play, m_listPlayers)
    {
        //fight area
        CardPokemon* pokemonFighter = play->fight()->pokemonFighter();
        if(pokemonFighter != nullptr)
        {
            pokemonFighter->applyDamageIfPoisoned();
        }

        //bench
        for(int i=0;i<play->bench()->countCard();++i)
        {
            CardPokemon* pokemonBench = play->bench()->cardPok(i);
            if(pokemonBench != nullptr)
            {
                pokemonBench->applyDamageIfPoisoned();
            }
        }
    }
}

void GameManager::checkPokemonDead()
{
    foreach (Player* play, m_listPlayers)
    {
        //fight area
        CardPokemon* pokemonFighter = play->fight()->pokemonFighter();
        if((pokemonFighter != nullptr) && (pokemonFighter->isDied() == true))
        {
            play->moveCardFromFightToTrash(0);      //On jette le pokemon mort
            //play->moveCardFromBenchToFight(0);      //On remplace par un pokemon sur le banc s'il y a

            if(play->rewards()->countCard() > 0)
                enemyOf(play)->drawOneReward();        //Le joueur adverse pioche une récompense
        }

        //bench
        for(int i=0;i<play->bench()->countCard();++i)
        {
            CardPokemon* pokemonBench = play->bench()->cardPok(i);
            if((pokemonBench != nullptr) && (pokemonBench->isDied() == true))
            {
                play->moveCardFromBenchToTrash(i);

                if(play->rewards()->countCard() > 0)
                    play->drawOneReward();

                i--;
            }
        }

        if((play->fight()->pokemonFighter() == nullptr) && (play->bench()->countCard() > 0))
        {
#ifdef TESTS_UNITAIRES
            play->moveCardFromBenchToFight(0);
#else
            QList<int> listIndexPokemonToReplace = m_ctrlPopups.displayBench(play->bench());
            play->moveCardFromBenchToFight(listIndexPokemonToReplace.first());
            //emit replacePokemonFighter(play);
#endif
        }
    }
}

void GameManager::checkStatusPokemonForNewRound()
{
    Player* playerAttacking = currentPlayer();
    if(playerAttacking != nullptr)
    {
        CardPokemon* pokemonAttacking = playerAttacking->fight()->pokemonFighter();

        if(pokemonAttacking != nullptr)
        {
            switch(pokemonAttacking->status())
            {
            case CardPokemon::Status_Paralyzed:
                pokemonAttacking->setStatus(CardPokemon::Status_Normal);
                break;
            case CardPokemon::Status_Slept:
                if(Utils::headOrTail() == 1)
                    pokemonAttacking->setStatus(CardPokemon::Status_Normal);
                break;
            default:
                //On n'a rien besoin de faire pour le reste
                break;
            }
        }
    }
}

void GameManager::checkAttacksBlocked()
{
    /*foreach (Player* play, m_listPlayers)
    {
        for(int index=0;index<play->fight()->countCard();index++)
            play->fight()->pokemonFighting(index)->decrementNumberOfTurnAttackStillBlocks();

        for(int index=0;index<play->bench()->countCard();index++)
            play->bench()->cardPok(index)->decrementNumberOfTurnAttackStillBlocks();
    }*/

    //On décrémente uniquement le joueur actuel
    for(int index=0;index<currentPlayer()->fight()->countCard();index++)
        currentPlayer()->fight()->pokemonFighting(index)->decrementNumberOfTurnAttackStillBlocks();

    for(int index=0;index<currentPlayer()->bench()->countCard();index++)
        currentPlayer()->bench()->cardPok(index)->decrementNumberOfTurnAttackStillBlocks();
}

#include "gamemanager.h"

#include <QDebug>
#include "src_Controler/ctrlpopups.h"
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

    if(m_gameStatus == ConstantesQML::StepGameInProgress)
    {
        startGame();
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

void GameManager::selectFirstPlayer()
{
#ifdef TESTS_UNITAIRES
    setIndexCurrentPlayer(0);
#else
    int indexCurrentPlayer = Utils::selectFirstPlayer(m_listPlayers.count());
    setIndexCurrentPlayer(indexCurrentPlayer);
#endif
}

void GameManager::setInitReady()
{
    bool everyoneIsReady = true;

    foreach(Player* playerReady, m_listPlayers)
        everyoneIsReady &= playerReady->initReady();

    if(everyoneIsReady == true)
        setGameStatus(ConstantesQML::StepGameInProgress);
}

//PHASE DE COMBAT
void GameManager::startGame()
{
    displayMessage(currentPlayer()->name() + " commence à jouer");
    currentPlayer()->newTurn();
}

void GameManager::nextPlayer()
{	
    setIndexCurrentPlayer(m_indexCurrentPlayer+1);

    currentPlayer()->newTurn();
    currentPlayer()->drawOneCard();
}

CardPokemon::Enum_StatusOfAttack GameManager::attack(CardPokemon *pokemonAttacking, unsigned short index)
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

    return statusOfAttack;
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

    //Vérification des status
    checkStatusPokemonForNewRound();

    //Si le pokémon attaqué est mort, le joueur pioche sa récompense
    checkPokemonDead();

    //On vérifie les conditions de victoires
    Player* playerWinner = gameIsFinished();
    if(playerWinner != nullptr)
    {
        foreach(Player* play, m_listPlayers)
            play->blockPlayer();

        displayMessage("VICTOIRE DE " + playerWinner->name());
    }
    else
    {
        //On passe au prochain tour
        currentPlayer()->blockPlayer();
        nextPlayer();
    }
}

//FIN DE LA GAME
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
        if(play->isLoser())
            playWinner = enemyOf(play);
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

QList<int> GameManager::displayDeck(PacketDeck *deck, unsigned short quantity)
{
    return m_ctrlPopups.displayDeck(deck, quantity);
}

QList<int> GameManager::displayHand(PacketHand *hand, unsigned short quantity)
{
    return m_ctrlPopups.displayHand(hand, quantity);
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

void GameManager::displayMessage(QString message)
{
    m_ctrlPopups.displayMessage(message);
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
    unsigned short coin = Utils::headOrTail();
    qDebug() << __PRETTY_FUNCTION__ << "coin=" << coin;
    m_ctrlPopups.displayHeadOrTail(coin);
    return coin;
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
        hasAWinner |= play->isLoser();

    //S'il n'y a pas encore de vainqueur, on laisse le prochain joueur jouer
    if(hasAWinner == false)
    {
        nextPlayer();
    }
    else
    {
        foreach(Player* play, m_listPlayers)
        {
            if(play->isLoser())
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
    //Status Confus
    //Rien à faire ici, sera appliqué au moment de l'attaque

    //Status Paralysé
    //A supprimer uniquement à la fin du tour du joueur concerné
    Player* playerAttacking = currentPlayer();
    if(playerAttacking != nullptr)
    {
        CardPokemon* pokemonAttacking = playerAttacking->fight()->pokemonFighter();

        if((pokemonAttacking != nullptr) && (pokemonAttacking->status() == CardPokemon::Status_Paralyzed))
        {
            pokemonAttacking->setStatus(CardPokemon::Status_Normal);
        }
    }

    //Status Endormi
    //Possibilité de se réveiller entre chaque tour
    foreach (Player* play, m_listPlayers)
    {
        //fight area
        CardPokemon* pokemonFighter = play->fight()->pokemonFighter();
        if((pokemonFighter != nullptr) && (pokemonFighter->status() == CardPokemon::Status_Slept))
        {
            if(headOrTail() == 1)
                pokemonFighter->setStatus(CardPokemon::Status_Normal);
        }
    }

    //Status Empoisonné
    //Perd un marqueur de dégat entre chaque tour
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

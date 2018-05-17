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

const int GameManager::m_NUMBER_FIRST_CARDS = 7;
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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return m_playerAttacking;
}

Player* GameManager::playerAttacked()
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return m_playerAttacked;
}

Player* GameManager::playerAt(int index)
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return m_gameStatus;
}

void GameManager::setGameStatus(ConstantesQML::StepGame step)
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
	Player* newPlayer = new Player(name, listCards);

    connect(newPlayer, &Player::endOfTurn, this, &GameManager::onEndOfTurn_Player);

	m_listPlayers.append(newPlayer);

    return newPlayer;
}

void GameManager::selectFirstPlayer()
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
#ifdef TESTS_UNITAIRES
    setIndexCurrentPlayer(0);
#else
    int indexCurrentPlayer = Utils::selectFirstPlayer(m_listPlayers.count());
    setIndexCurrentPlayer(indexCurrentPlayer);
#endif
}

void GameManager::setInitReady()
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
    bool everyoneIsReady = true;

    foreach(Player* playerReady, m_listPlayers)
        everyoneIsReady &= playerReady->initReady();

    if(everyoneIsReady == true)
        setGameStatus(ConstantesQML::StepGameInProgress);
}

//PHASE DE COMBAT
void GameManager::startGame()
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
    displayMessage(currentPlayer()->name() + " commence à jouer");
    currentPlayer()->newTurn();
    currentPlayer()->drawOneCard();
}

void GameManager::nextPlayer()
{	
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
    setIndexCurrentPlayer(m_indexCurrentPlayer+1);

    currentPlayer()->newTurn();
    currentPlayer()->drawOneCard();
}

CardPokemon::Enum_StatusOfAttack GameManager::attack(CardPokemon *pokemonAttacking, unsigned short index)
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif
    bool success = false;
    QList<AbstractCard *> listCardsBench;

    //On revérifie qu'on peut
    if(pokemonToRetreat->canRetreat() == true)
    {
        Player* playerAttacking = pokemonToRetreat->owner();
        if(playerAttacking != nullptr)
        {
            if(pokemonToRetreat->costRetreat() > 0)
            {
                //On sélectionne les énergies à mettre dans la pile de défausse
                QList<CardEnergy*> listEnergies = displayEnergiesForAPokemon(pokemonToRetreat, pokemonToRetreat->costRetreat(), AbstractCard::Element_Whatever);

                //On les met dans la défausse
                pokemonToRetreat->moveEnergiesInTrash(listEnergies);
            }

            listCardsBench = displayBench(playerAttacking->bench(), 1);

            if(listCardsBench.first()->type() == AbstractCard::TypeOfCard_Pokemon)
                success = playerAttacking->swapCardsBetweenBenchAndFight(static_cast<CardPokemon*>(listCardsBench.first()));
            else
                success = false;
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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

    //Si le pokémon attaqué est mort, le joueur pioche sa récompense
    checkPokemonDead();

    //On débloque des attaques si besoin
    checkAttacksBlocked();

    //Vérification des status
    checkStatusPokemonForNewRound();

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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

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

QList<AbstractCard *> GameManager::displayBench(BenchArea *bench, unsigned short quantity)
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

#ifdef TESTS_UNITAIRES
    Q_UNUSED(card)
    return QList<int>() << 0;
#else
    return m_ctrlPopups.displayBench(bench, quantity);
#endif
}

QList<AbstractCard *> GameManager::displayDeck(PacketDeck *deck, unsigned short quantity)
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

    return m_ctrlPopups.displayDeck(deck, quantity);
}

QList<AbstractCard *> GameManager::displayHand(PacketHand *hand, unsigned short quantity)
{
    return m_ctrlPopups.displayHand(hand, quantity);
}

QList<AbstractCard *> GameManager::displayTrash(PacketTrash *trash, unsigned short quantity, AbstractCard::Enum_typeOfCard typeOfCard)
{
    return m_ctrlPopups.displayTrash(trash, quantity, typeOfCard);
}

QList<AbstractCard *> GameManager::displaySelectHiddenCard(PacketRewards *rewards, unsigned short quantity)
{
    return m_ctrlPopups.displaySelectHiddenCard(rewards, quantity);
}

QList<CardEnergy*> GameManager::displayEnergiesForAPokemon(CardPokemon* pokemon, unsigned short quantity, AbstractCard::Enum_element element)
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

#ifdef TESTS_UNITAIRES
    Q_UNUSED(card)
    return QList<int>() << 0;
#else
    return m_ctrlPopups.displayEnergiesForAPokemon(pokemon, quantity, element);
#endif
}

int GameManager::displayAttacks(CardPokemon* card, bool blockRetreat)
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

    for(int i=0;i<m_NUMBER_FIRST_CARDS;++i)
    {
        play->drawOneCard();
    }
}

void GameManager::checkPokemonDead()
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

    foreach (Player* play, m_listPlayers)
    {
        //fight area
        CardPokemon* pokemonFighter = play->fight()->pokemonFighter();
        if((pokemonFighter != nullptr) && (pokemonFighter->isDied() == true))
        {
            play->moveCardFromFightToTrash(0);      //On jette le pokemon mort
            //play->moveCardFromBenchToFight(0);      //On remplace par un pokemon sur le banc s'il y a

            if(enemyOf(play)->rewards()->countCard() > 0)
            {
                QList<AbstractCard*> listRewards = displaySelectHiddenCard(enemyOf(play)->rewards());
                enemyOf(play)->drawOneReward(listRewards.first());        //Le joueur adverse pioche une récompense
            }
        }

        //bench
        for(int i=0;i<play->bench()->countCard();++i)
        {
            CardPokemon* pokemonBench = play->bench()->cardPok(i);
            if((pokemonBench != nullptr) && (pokemonBench->isDied() == true))
            {
                play->moveCardFromBenchToTrash(i);

                if(play->rewards()->countCard() > 0)
                {
                    QList<AbstractCard*> listRewards = displaySelectHiddenCard(enemyOf(play)->rewards());
                    enemyOf(play)->drawOneReward(listRewards.first());        //Le joueur adverse pioche une récompense
                }

                i--;
            }
        }

        if((play->fight()->pokemonFighter() == nullptr) && (play->bench()->countCard() > 0))
        {
#ifdef TESTS_UNITAIRES
            play->moveCardFromBenchToFight(0);
#else
            QList<AbstractCard*> listPokemonToReplace = m_ctrlPopups.displayBench(play->bench());

            if(listPokemonToReplace.first()->type() == AbstractCard::TypeOfCard_Pokemon)
                play->moveCardFromBenchToFight(static_cast<CardPokemon*>(listPokemonToReplace.first()));
            else
                qCritical() << __PRETTY_FUNCTION__ << "Card non pokemon sur le banc";
#endif
        }
    }
}

void GameManager::checkStatusPokemonForNewRound()
{
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

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
#ifdef TRACAGE_PRECIS
    qDebug() << __PRETTY_FUNCTION__;
#endif

    /*foreach (Player* play, m_listPlayers)
    {
        for(int index=0;index<play->fight()->countCard();index++)
            play->fight()->pokemonFighting(index)->decrementNumberOfTurnAttackStillBlocks();

        for(int index=0;index<play->bench()->countCard();index++)
            play->bench()->cardPok(index)->decrementNumberOfTurnAttackStillBlocks();
    }*/

    qDebug() << __PRETTY_FUNCTION__ << "Début";

    //On décrémente uniquement le joueur actuel
    for(int index=0;index<currentPlayer()->fight()->countCard();index++)
    {
        qDebug() << __PRETTY_FUNCTION__ << "fighting" << currentPlayer()->name() << index;

        if(currentPlayer()->fight()->pokemonFighting(index) != nullptr)
        {
            qDebug() << __PRETTY_FUNCTION__ << "fighting" << currentPlayer()->name() << currentPlayer()->fight()->pokemonFighting(index)->name();
            currentPlayer()->fight()->pokemonFighting(index)->decrementNumberOfTurnAttackStillBlocks();
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << "pokemonFighting" << index << " is nullptr";
    }

    for(int index=0;index<currentPlayer()->bench()->countCard();index++)
    {
        qDebug() << __PRETTY_FUNCTION__ << "bench" << currentPlayer()->name() << index;

        if(currentPlayer()->bench()->cardPok(index) != nullptr)
        {
            qDebug() << __PRETTY_FUNCTION__ << "bench" << currentPlayer()->name() << currentPlayer()->bench()->cardPok(index)->name();
            currentPlayer()->bench()->cardPok(index)->decrementNumberOfTurnAttackStillBlocks();
        }
        else
            qCritical() << __PRETTY_FUNCTION__ << "pokemonBench" << index << " is nullptr";
    }

    qDebug() << __PRETTY_FUNCTION__ << "Fin";
}

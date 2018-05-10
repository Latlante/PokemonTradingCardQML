#include "player.h"

#include <QDebug>
#include "src_Cards/abstractcard.h"
#include "src_Cards/cardaction.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"
#include "src_Packets/bencharea.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packetdeck.h"
#include "src_Packets/packethand.h"
#include "src_Packets/packetrewards.h"
#include "src_Packets/packettrash.h"

Player::Player(QString name, QList<AbstractCard*> listCards, QObject *parent) :
	QObject(parent),
    m_name(name),
    m_bench(new BenchArea()),
    m_deck(new PacketDeck(listCards)),
    m_fight(new FightArea()),
    m_hand(new PacketHand()),
    m_rewards(new PacketRewards()),
    m_trash(new PacketTrash()),
    m_canPlay(true),
    m_energyPlayedForThisRound(false)
{
    foreach(AbstractCard* card, listCards)
        card->setOwner(this);
}

Player::~Player()
{
    delete m_bench;
    delete m_deck;
    delete m_fight;
    delete m_hand;
    delete m_rewards;
    delete m_trash;
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void Player::declareQML()
{
    qmlRegisterUncreatableType<Player>("model", 1, 0, "Player", "Player error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
const QString Player::name()
{
    return m_name;
}

BenchArea* Player::bench()
{
    return m_bench;
}

PacketDeck* Player::deck()
{
	return m_deck;
}

FightArea* Player::fight()
{
    return m_fight;
}

PacketHand* Player::hand()
{
	return m_hand;
}

PacketRewards* Player::rewards()
{
    return m_rewards;
}

PacketTrash* Player::trash()
{
    return m_trash;
}

void Player::newTurn()
{
    setCanPlay(true);
    m_energyPlayedForThisRound = false;
    //fight()->pokemonFighter()->setStatus(CardPokemon::Status_Normal);
}

void Player::skipYourTurn()
{
    emit endOfTurn();
}

void Player::blockPlayer()
{
    setCanPlay(false);
}

bool Player::isPlaying()
{
    return m_canPlay;
}

void Player::drawOneCard()
{
    //qDebug() << m_name << " - "<< __PRETTY_FUNCTION__;

    moveCardFromDeckToHand();
}

void Player::drawOneReward()
{
    moveCardFromRewardToHand();
}

bool Player::isWinner()
{
    //Conditions de victoire:
    //  -> Plus de récompense à piocher
    //  -> Plus de carte dans le deck
    //  -> Plus de pokémon sur la banc
    bool hasAWinner = false;

    hasAWinner |= rewards()->isEmpty();
    hasAWinner |= deck()->isEmpty();
    hasAWinner |= bench()->isEmpty() && fight()->isEmpty();

    return hasAWinner;
}

bool Player::moveCardFromDeckToHand()
{
    return moveCardFromPacketToAnother(deck(), hand(), 0);
}

bool Player::moveCardFromDeckToReward()
{
    return moveCardFromPacketToAnother(deck(), rewards(), 0);
}

bool Player::moveCardFromHandToBench(int indexHand, int indexBench)
{
    bool moveSuccess = false;

    AbstractCard* cardToMove = hand()->card(indexHand);

    if (cardToMove != nullptr)
    {
        //On autorise uniquement les cartes de type Pokemon a être posé sur le banc
        if (cardToMove->type() == AbstractCard::TypeOfCard_Pokemon)
        {
            CardPokemon* cardPok = static_cast<CardPokemon*>(cardToMove);

            if(cardPok != nullptr)
            {
                //Pokémon de base
                if(cardPok->isBase() == true)
                {
                    moveSuccess = moveCardFromPacketToAnother(hand(), bench(), indexHand);
                }
                //Evolution
                else
                {
                    //On récupére la carte Pokémon a laquelle l'associer
                    AbstractCard* cardToAssociate = bench()->card(indexBench);

                    if ((cardToAssociate != nullptr) && (cardToAssociate->type() == AbstractCard::TypeOfCard_Pokemon))
                    {
                        CardPokemon* pokemonToAssociate = static_cast<CardPokemon*>(cardToAssociate);

                        if (pokemonToAssociate != nullptr)
                        {
                            //On l'associe au Pokémon et on peut la supprimer du paquet d'origine
                            //pour ne pas l'avoir en doublon
                            if(pokemonToAssociate->evolve(cardPok))
                            {
                                hand()->removeFromPacketWithoutDelete(cardPok);
                                moveSuccess = true;
                            }
                        }
                    }
                }
            }
            else
            {
                qDebug() << __PRETTY_FUNCTION__ << ", cardPok est nullptr";
            }
        }
        else if (cardToMove->type() == AbstractCard::TypeOfCard_Energy)
        {
            if((m_energyPlayedForThisRound == false))
            {
                CardEnergy* cardEn = static_cast<CardEnergy*>(cardToMove);

                if (cardEn != nullptr)
                {
                    //On récupére la carte Pokémon a laquelle l'associer
                    AbstractCard* cardToAssociate = bench()->card(indexBench);

                    if ((cardToAssociate != nullptr) && (cardToAssociate->type() == AbstractCard::TypeOfCard_Pokemon))
                    {
                        CardPokemon* pokemonToAssociate = static_cast<CardPokemon*>(cardToAssociate);

                        if (pokemonToAssociate != nullptr)
                        {
                            //On l'associe au Pokémon et on peut la supprimer du paquet d'origine
                            //pour ne pas l'avoir en doublon
                            pokemonToAssociate->addEnergy(cardEn);
                            hand()->removeFromPacketWithoutDelete(cardEn);

                            m_energyPlayedForThisRound = true;
                            moveSuccess = true;
                        }
                    }
                }
            }
        }
        else
        {
            qDebug() << __PRETTY_FUNCTION__ << ", cardToMove n'est pas du bon type:" << cardToMove->type();
        }
    }
    else
    {
        qDebug() << __PRETTY_FUNCTION__ << ", cardToMove is nullptr";
    }

    return moveSuccess;
}

bool Player::moveCardFromHandToDeck(int indexHand)
{
    return moveCardFromPacketToAnother(hand(), deck(), indexHand);
}

bool Player::moveCardFromHandToFight(int indexHand)
{
    bool moveSuccess = false;

    AbstractCard* cardToMove = hand()->card(indexHand);

    if (cardToMove != nullptr)
    {
        //On autorise uniquement les cartes de type Pokemon a être posé sur le banc
        if (cardToMove->type() == AbstractCard::TypeOfCard_Pokemon)
        {
            CardPokemon* cardPok = static_cast<CardPokemon*>(cardToMove);

            //Pokémon de base
            if(cardPok->isBase() == true)
            {
                moveSuccess = moveCardFromPacketToAnother(hand(), fight(), indexHand);
            }
            //Evolution
            else
            {
                //On récupére la carte Pokémon a laquelle l'associer
                AbstractCard* cardToAssociate = fight()->pokemonFighter();

                if ((cardToAssociate != nullptr) && (cardToAssociate->type() == AbstractCard::TypeOfCard_Pokemon))
                {
                    CardPokemon* pokemonToAssociate = static_cast<CardPokemon*>(cardToAssociate);

                    if (pokemonToAssociate != nullptr)
                    {
                        //On l'associe au Pokémon et on peut la supprimer du paquet d'origine
                        //pour ne pas l'avoir en doublon
                        if(pokemonToAssociate->evolve(cardPok))
                        {
                            hand()->removeFromPacketWithoutDelete(cardPok);
                            moveSuccess = true;
                        }
                    }
                }
            }
        }
        else if (cardToMove->type() == AbstractCard::TypeOfCard_Energy)
        {
            if(m_energyPlayedForThisRound == false)
            {
                CardEnergy* cardEn = static_cast<CardEnergy*>(cardToMove);

                if (cardEn != nullptr)
                {
                    //On récupére la carte Pokémon a laquelle l'associer
                    AbstractCard* cardToAssociate = fight()->pokemonFighter();

                    if ((cardToAssociate != nullptr) && (cardToAssociate->type() == AbstractCard::TypeOfCard_Pokemon))
                    {
                        CardPokemon* pokemonToAssociate = static_cast<CardPokemon*>(cardToAssociate);

                        if (pokemonToAssociate != nullptr)
                        {
                            //On l'associe au Pokémon et on peut la supprimer du paquet d'origine
                            //pour ne pas l'avoir en doublon
                            pokemonToAssociate->addEnergy(cardEn);
                            hand()->removeFromPacketWithoutDelete(cardEn);

                            m_energyPlayedForThisRound = true;
                            moveSuccess = true;
                        }
                    }
                }
            }

        }
        else if (cardToMove->type() == AbstractCard::TypeOfCard_Action)
        {
            CardAction* cardTrainer = static_cast<CardAction*>(cardToMove);

            if(cardTrainer != nullptr)
            {
                cardTrainer->executeAction();
                moveSuccess = moveCardFromHandToTrash(indexHand);
            }
        }
        else
        {
            qDebug() << __PRETTY_FUNCTION__ << ", cardToMove n'est pas du bon type:" << cardToMove->type();
        }
    }
    else
    {
        qDebug() << __PRETTY_FUNCTION__ << ", cardToMove is nullptr";
    }

    return moveSuccess;
}

bool Player::moveCardFromHandToTrash(int indexHand)
{
    return moveCardFromPacketToAnother(hand(), trash(), indexHand);
}

bool Player::moveCardFromBenchToFight(int indexBench)
{
    bool moveSuccess = false;

    AbstractCard* cardToMove = bench()->card(indexBench);

    if (cardToMove != nullptr)
    {
        //On autorise uniquement les cartes de type Pokemon a être posé sur le banc
        if (cardToMove->type() == AbstractCard::TypeOfCard_Pokemon)
        {
            CardPokemon* cardPok = static_cast<CardPokemon*>(cardToMove);

            //On refuse les évolutions
            if (cardPok->isBase() == true)
            {
                moveSuccess = moveCardFromPacketToAnother(bench(), fight(), indexBench);
            }
            else
            {
                qDebug() << __PRETTY_FUNCTION__ << ", cardPok n'est pas une base";
            }
        }
        else
        {
            qDebug() << __PRETTY_FUNCTION__ << ", cardToMove n'est pas du bon type:" << cardToMove->type();
        }
    }
    else
    {
        qDebug() << __PRETTY_FUNCTION__ << ", cardToMove is nullptr";
    }

    return moveSuccess;
}

bool Player::moveCardFromBenchToTrash(int index)
{
    CardPokemon* pokemonBench = bench()->cardPok(index);
    QList<AbstractCard*> listCardAttached = pokemonBench->purge();

    foreach(AbstractCard* card, listCardAttached)
        trash()->addNewCard(card);

    return moveCardFromPacketToAnother(bench(), trash(), index);
}

bool Player::moveCardFromFightToTrash(int index)
{
    CardPokemon* pokemonFighter = fight()->pokemonFighting(index);
    QList<AbstractCard*> listCardAttached = pokemonFighter->purge();

    foreach(AbstractCard* card, listCardAttached)
        trash()->addNewCard(card);

    return moveCardFromPacketToAnother(fight(), trash(), index);
}

bool Player::moveCardFromRewardToHand()
{
    return moveCardFromPacketToAnother(rewards(), hand(), 0);
}

bool Player::moveAllCardFromHandToDeck()
{
    bool status = true;

    while((hand()->countCard() > 0) && (status == true))
    {
        status &= moveCardFromHandToDeck(0);
    }

    return status;
}

bool Player::swapCardsBetweenBenchAndFight(int indexBench)
{
    bool status = true;

    if((fight() != nullptr) && (bench() != nullptr))
    {
        if((fight()->pokemonFighting(0) != nullptr) && (bench()->cardPok(indexBench) != nullptr))
        {
            //A ce moment là, on sait que tout est bon
            //On commence donc par récupérer le pokémon qui se bat pour le remplace
            AbstractCard* pokFigther = fight()->takeACard(0);
            status &= moveCardFromBenchToFight(indexBench);
            status &= bench()->addNewCard(pokFigther);
        }
        else
            status = false;
    }
    else
        status = false;

    return status;
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
void Player::setCanPlay(bool status)
{
    if(status != m_canPlay)
    {
        m_canPlay = status;
        emit canPlayChanged();
    }
}

bool Player::moveCardFromPacketToAnother(AbstractPacket *source, AbstractPacket *destination, int index)
{
    bool moveSuccess = false;

    if (destination->isFull() == false)
    {
        AbstractCard* cardToMove = source->takeACard(index);

        if (cardToMove != nullptr)
        {
            destination->addNewCard(cardToMove);
            moveSuccess = true;
        }
        else
        {
            qCritical() << __PRETTY_FUNCTION__ << "Card is nullptr";

        }
    }

    return moveSuccess;
}

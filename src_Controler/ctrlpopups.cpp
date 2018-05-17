#include "ctrlpopups.h"

#include <QDebug>
#include <QEventLoop>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml/qqml.h>

#include "src_Cards/cardpokemon.h"
#include "src_Models/modelpopupselectcardinpacket.h"
#include "src_Models/modelpopupselectenergyinpokemon.h"
#include "src_Packets/abstractpacket.h"
#include "src_Packets/bencharea.h"
#include "src_Packets/packetdeck.h"
#include "src_Packets/packethand.h"
#include "src_Packets/packetrewards.h"
#include "src_Packets/packettrash.h"

CtrlPopups::CtrlPopups(QObject *parent) :
    QObject(parent),
    m_modelSelectCardInPacket(new ModelPopupSelectCardInPacket()),
    m_selectCardInPacketVisible(false),
    m_selectHiddenCardVisible(false),
    m_popupSelectingAttacks_Visible(false),
    m_popupSelectingAttacks_Card(nullptr),
    m_popupSelectingAttacks_IndexAttack(-1),
    m_popupSelectingAttacks_AuthorizeRetreat(false),
    m_modelSelectEnergyInPokemon(new ModelPopupSelectEnergyInPokemon()),
    m_selectEnergiesInPokemonVisible(false),
    m_messageVisible(false),
    m_messageContent(""),
    m_headOrTailVisible(false),
    m_headOrTailValue(0)
{

}

CtrlPopups::~CtrlPopups()
{
    delete m_modelSelectCardInPacket;
    delete m_modelSelectEnergyInPokemon;
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void CtrlPopups::declareQML()
{
    qmlRegisterUncreatableType<CtrlPopups>("model", 1, 0, "CtrlPopups", "CtrlPopups error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
bool CtrlPopups::install(QQmlApplicationEngine *pEngine)
{
    qDebug() << "installing CtrlPopups...";

    bool bInstalled = false;

    if (NULL != pEngine)
    {
        QQmlContext* pContext = pEngine->rootContext();
        if (NULL != pContext)
        {
            bInstalled = true;
            qDebug() << "CtrlPopups is installed in QML engine";
            pContext->setContextProperty("ctrlPopups", this);
        }
        else
        {
            qCritical() << "Qml context is null.";
        }
    }

    return bInstalled;
}

//**************************************
//      SELECT CARD IN PACKET
//**************************************
ModelPopupSelectCardInPacket* CtrlPopups::modelSelectCardInPacket()
{
    return m_modelSelectCardInPacket;
}

QList<AbstractCard *> CtrlPopups::displayBench(BenchArea *packet, unsigned short quantity)
{
    return displayAbstractPacket(packet, quantity, AbstractCard::TypeOfCard_Whatever);
}

QList<AbstractCard *> CtrlPopups::displayDeck(PacketDeck *packet, unsigned short quantity)
{
    return displayAbstractPacket(packet, quantity, AbstractCard::TypeOfCard_Whatever);
}

QList<AbstractCard *> CtrlPopups::displayHand(PacketHand *packet, unsigned short quantity)
{
    return displayAbstractPacket(packet, quantity, AbstractCard::TypeOfCard_Whatever);
}

QList<AbstractCard *> CtrlPopups::displayTrash(PacketTrash *packet, unsigned short quantity, AbstractCard::Enum_typeOfCard typeOfCard)
{
    return displayAbstractPacket(packet, quantity, typeOfCard);
}

bool CtrlPopups::selectCardInPacketVisible()
{
    return m_selectCardInPacketVisible;
}

void CtrlPopups::setSelectCardInPacketVisible(bool state)
{
    if(m_selectCardInPacketVisible != state)
    {
        m_selectCardInPacketVisible = state;
        emit selectCardInPacketVisibleChanged();
    }
}

//**************************************
//          SELECT HIDDEN CARD
//**************************************
QList<AbstractCard *> CtrlPopups::displaySelectHiddenCard(PacketRewards* rewards, unsigned short quantity)
{
    //Initialisation
    m_modelSelectCardInPacket->setNumberOfCardsToSelect(quantity);
    m_modelSelectCardInPacket->addPacketFromAbstractPacket(rewards);
    setSelectHiddenCardVisible(true);

    //En attente
    QEventLoop loop;
    connect(this, &CtrlPopups::selectionFinished, &loop, &QEventLoop::quit);
    loop.exec();

    //Configuration de fin
    setSelectHiddenCardVisible(false);

    return m_modelSelectCardInPacket->listCardsSelected();
}

bool CtrlPopups::selectHiddenCardVisible()
{
    return m_selectHiddenCardVisible;
}

void CtrlPopups::setSelectHiddenCardVisible(bool state)
{
    if(m_selectHiddenCardVisible != state)
    {
        m_selectHiddenCardVisible = state;
        emit selectHiddenCardVisibleChanged();
    }
}

//**************************************
//            SELECT ATTACK
//**************************************
int CtrlPopups::displayAttacks(CardPokemon* card, bool authorizeRetreat)
{
    //Initialisation
    setPopupSelectingAttacks_IndexAttack(-1);
    setPopupSelectingAttacks_AuthorizeRetreat(authorizeRetreat);
    setPopupSelectingAttacks_Card(card);
    setPopupSelectingAttacks_Visible(true);

    qDebug() << __PRETTY_FUNCTION__ << "En attente";

    //En attente
    QEventLoop loop;
    connect(this, &CtrlPopups::selectionFinished, &loop, &QEventLoop::quit);
    loop.exec();

    qDebug() << __PRETTY_FUNCTION__ << "Passé";

    //Configuration de fin
    setPopupSelectingAttacks_Visible(false);

    //Renvoi de l'information
    return m_popupSelectingAttacks_IndexAttack;
}

bool CtrlPopups::popupSelectingAttacks_Visible()
{
    return m_popupSelectingAttacks_Visible;
}

void CtrlPopups::setPopupSelectingAttacks_Visible(bool state)
{
    if(m_popupSelectingAttacks_Visible != state)
    {
        m_popupSelectingAttacks_Visible = state;
        emit popupSelectingAttacks_VisibleChanged();
    }
}

CardPokemon* CtrlPopups::popupSelectingAttacks_Card()
{
    return m_popupSelectingAttacks_Card;
}

void CtrlPopups::setPopupSelectingAttacks_Card(CardPokemon *card)
{
    if(m_popupSelectingAttacks_Card != card)
    {
        m_popupSelectingAttacks_Card = card;
        emit popupSelectingAttacks_CardChanged();
    }
}

int CtrlPopups::popupSelectingAttacks_IndexAttack()
{
    return m_popupSelectingAttacks_IndexAttack;
}

void CtrlPopups::setPopupSelectingAttacks_IndexAttack(int index)
{
    if(m_popupSelectingAttacks_IndexAttack != index)
    {
        m_popupSelectingAttacks_IndexAttack = index;
        emit popupSelectingAttacks_IndexAttackChanged();
    }
}

bool CtrlPopups::popupSelectingAttacks_AuthorizeRetreat()
{
    return m_popupSelectingAttacks_AuthorizeRetreat;
}

void CtrlPopups::setPopupSelectingAttacks_AuthorizeRetreat(bool authorize)
{
    if(m_popupSelectingAttacks_AuthorizeRetreat != authorize)
    {
        m_popupSelectingAttacks_AuthorizeRetreat = authorize;
        emit popupSelectingAttacks_AuthorizeRetreatChanged();
    }
}

//**************************************
//      SELECT ENERGY IN POKEMON
//**************************************
ModelPopupSelectEnergyInPokemon* CtrlPopups::modelSelectEnergyInPokemon()
{
    return m_modelSelectEnergyInPokemon;
}

QList<CardEnergy*> CtrlPopups::displayEnergiesForAPokemon(CardPokemon *pokemon, unsigned short quantity, AbstractCard::Enum_element element)
{
    //Initialisation
    m_modelSelectEnergyInPokemon->setElementFilter(element);
    m_modelSelectEnergyInPokemon->addListEnergyFromPokemon(pokemon);
    m_modelSelectEnergyInPokemon->setNumberOfEnergiesToSelect(quantity);
    setSelectEnergiesInPokemonVisible(true);

    //En attente
    QEventLoop loop;
    connect(this, &CtrlPopups::selectionFinished, &loop, &QEventLoop::quit);
    loop.exec();

    //Configuration de fin
    setSelectEnergiesInPokemonVisible(false);

    //Renvoi de l'information
    return m_modelSelectEnergyInPokemon->listIndexEnergiesSelected();
}

bool CtrlPopups::selectEnergiesInPokemonVisible()
{
    return m_selectEnergiesInPokemonVisible;
}

void CtrlPopups::setSelectEnergiesInPokemonVisible(bool state)
{
    if(m_selectEnergiesInPokemonVisible != state)
    {
        m_selectEnergiesInPokemonVisible = state;
        emit selectEnergiesInPokemonVisibleChanged();
    }
}

void CtrlPopups::selectionCardsFinished()
{
    emit selectionFinished();
}

//**************************************
//              MESSAGE
//**************************************
void CtrlPopups::displayMessage(QString message)
{
    //Initialisation
    setMessageContent(message);
    setMessageVisible(true);

    //En attente
    QEventLoop loop;
    connect(this, &CtrlPopups::selectionFinished, &loop, &QEventLoop::quit);
    loop.exec();

    //Configuration de fin
    setMessageVisible(false);
}

bool CtrlPopups::messageVisible()
{
    return m_messageVisible;
}

void CtrlPopups::setMessageVisible(bool visible)
{
    if(m_messageVisible != visible)
    {
        m_messageVisible = visible;
        emit messageVisibleChanged();
    }
}

QString CtrlPopups::messageContent()
{
    return m_messageContent;
}

void CtrlPopups::setMessageContent(QString message)
{
    if(m_messageContent != message)
    {
        m_messageContent = message;
        emit messageContentChanged();
    }
}

//**************************************
//          COIN HEAD OR TAIL
//**************************************
void CtrlPopups::displayHeadOrTail(int value)
{
    //Initialisation
    setHeadOrTailValue(value);
    setHeadOrTailVisible(true);

    //En attente
    QEventLoop loop;
    connect(this, &CtrlPopups::selectionFinished, &loop, &QEventLoop::quit);
    loop.exec();

    //Configuration de fin
    setHeadOrTailVisible(false);
}

bool CtrlPopups::headOrTailVisible()
{
    return m_headOrTailVisible;
}

void CtrlPopups::setHeadOrTailVisible(bool visible)
{
    if(m_headOrTailVisible != visible)
    {
        m_headOrTailVisible = visible;
        emit headOrTailVisibleChanged();
    }
}

int CtrlPopups::headOrTailValue()
{
    return m_headOrTailValue;
}

void CtrlPopups::setHeadOrTailValue(int value)
{
    if(m_headOrTailValue != value)
    {
        m_headOrTailValue = value;
        emit headOrTailValueChanged();
    }
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
QList<AbstractCard*> CtrlPopups::displayAbstractPacket(AbstractPacket *packet, unsigned short quantity, AbstractCard::Enum_typeOfCard typeOfCard)
{
    //Initialisation
    m_modelSelectCardInPacket->setTypeOfCardFilter(typeOfCard);
    m_modelSelectCardInPacket->setNumberOfCardsToSelect(quantity);
    m_modelSelectCardInPacket->addPacketFromAbstractPacket(packet);
    setSelectCardInPacketVisible(true);

    //En attente
    QEventLoop loop;
    connect(this, &CtrlPopups::selectionFinished, &loop, &QEventLoop::quit);
    loop.exec();

    //Configuration de fin
    setSelectCardInPacketVisible(false);

    //Renvoi de l'information
    return m_modelSelectCardInPacket->listCardsSelected();
}

#ifndef CTRLPOPUPS_H
#define CTRLPOPUPS_H

#include <QObject>

#include "src_Cards/abstractcard.h"

class CardPokemon;
class AbstractPacket;
class BenchArea;
class PacketDeck;
class PacketHand;
class ModelPopupSelectCardInPacket;
class ModelPopupSelectEnergyInPokemon;
class QQmlEngine;
class QQmlApplicationEngine;

class CtrlPopups : public QObject
{
    Q_OBJECT
    //SELECT CARD IN PACKET
    Q_PROPERTY(bool selectCardInPacketVisible READ selectCardInPacketVisible WRITE setSelectCardInPacketVisible NOTIFY selectCardInPacketVisibleChanged)

    //SELECT ATTACK
    Q_PROPERTY(bool popupSelectingAttacks_Visible READ popupSelectingAttacks_Visible WRITE setPopupSelectingAttacks_Visible NOTIFY popupSelectingAttacks_VisibleChanged)
    Q_PROPERTY(CardPokemon* popupSelectingAttacks_Card READ popupSelectingAttacks_Card NOTIFY popupSelectingAttacks_CardChanged)
    Q_PROPERTY(int popupSelectingAttacks_IndexAttack READ popupSelectingAttacks_IndexAttack WRITE setPopupSelectingAttacks_IndexAttack NOTIFY popupSelectingAttacks_IndexAttackChanged)
    Q_PROPERTY(bool popupSelectingAttacks_AuthorizeRetreat READ popupSelectingAttacks_AuthorizeRetreat WRITE setPopupSelectingAttacks_AuthorizeRetreat NOTIFY popupSelectingAttacks_AuthorizeRetreatChanged)

    //SELECT ENERGY IN POKEMON
    Q_PROPERTY(bool selectEnergiesInPokemonVisible READ selectEnergiesInPokemonVisible WRITE setSelectEnergiesInPokemonVisible NOTIFY selectEnergiesInPokemonVisibleChanged)

    //MESSAGE
    Q_PROPERTY(bool messageVisible READ messageVisible WRITE setMessageVisible NOTIFY messageVisibleChanged)
    Q_PROPERTY(QString messageContent READ messageContent WRITE setMessageContent NOTIFY messageContentChanged)

    //COIN HEAD OR TAIL
    Q_PROPERTY(bool headOrTailVisible READ headOrTailVisible WRITE setHeadOrTailVisible NOTIFY headOrTailVisibleChanged)
    Q_PROPERTY(int headOrTailValue READ headOrTailValue WRITE setHeadOrTailValue NOTIFY headOrTailValueChanged)

public:
    explicit CtrlPopups(QObject *parent = nullptr);
    ~CtrlPopups();

    static void declareQML();
    bool install(QQmlApplicationEngine *pEngine);

    //SELECT CARD IN PACKET
    Q_INVOKABLE ModelPopupSelectCardInPacket* modelSelectCardInPacket();
    Q_INVOKABLE QList<int> displayBench(BenchArea* packet, unsigned short quantity = 1);
    Q_INVOKABLE QList<int> displayDeck(PacketDeck* packet, unsigned short quantity = 1);
    Q_INVOKABLE QList<int> displayHand(PacketHand* packet, unsigned short quantity = 1);
    bool selectCardInPacketVisible();
    void setSelectCardInPacketVisible(bool state);

    //SELECT ATTACK
    int displayAttacks(CardPokemon* card, bool authorizeRetreat);
    bool popupSelectingAttacks_Visible();
    void setPopupSelectingAttacks_Visible(bool state);
    CardPokemon* popupSelectingAttacks_Card();
    void setPopupSelectingAttacks_Card(CardPokemon* card);
    int popupSelectingAttacks_IndexAttack();
    void setPopupSelectingAttacks_IndexAttack(int index);
    bool popupSelectingAttacks_AuthorizeRetreat();
    void setPopupSelectingAttacks_AuthorizeRetreat(bool authorize);

    //SELECT ENERGY IN POKEMON
    Q_INVOKABLE ModelPopupSelectEnergyInPokemon* modelSelectEnergyInPokemon();
    QList<int> displayEnergiesForAPokemon(CardPokemon* pokemon, unsigned short quantity, AbstractCard::Enum_element element);
    bool selectEnergiesInPokemonVisible();
    void setSelectEnergiesInPokemonVisible(bool state);

    //MESSAGE
    void displayMessage(QString message);
    bool messageVisible();
    void setMessageVisible(bool visible);
    QString messageContent();
    void setMessageContent(QString message);

    //COIN HEAD OR TAIL
    void displayHeadOrTail(int value);
    bool headOrTailVisible();
    void setHeadOrTailVisible(bool visible);
    int headOrTailValue();
    void setHeadOrTailValue(int value);

    Q_INVOKABLE void selectionCardsFinished();

signals:
    //SELECT CARD IN PACKET
    void selectCardInPacketVisibleChanged();

    //SELECT ATTACK
    void popupSelectingAttacks_VisibleChanged();
    void popupSelectingAttacks_CardChanged();
    void popupSelectingAttacks_IndexAttackChanged();
    void popupSelectingAttacks_AuthorizeRetreatChanged();

    //SELECT ENERGY IN POKEMON
    void selectEnergiesInPokemonVisibleChanged();

    //MESSAGE
    void messageVisibleChanged();
    void messageContentChanged();

    //COIN HEAD OR TAIL
    bool headOrTailVisibleChanged();
    int headOrTailValueChanged();

    void selectionFinished();

private:
    //SELECT CARD IN PACKET
    ModelPopupSelectCardInPacket* m_modelSelectCardInPacket;
    bool m_selectCardInPacketVisible;

    //SELECT ATTACK
    bool m_popupSelectingAttacks_Visible;
    CardPokemon* m_popupSelectingAttacks_Card;
    int m_popupSelectingAttacks_IndexAttack;
    bool m_popupSelectingAttacks_AuthorizeRetreat;

    //SELECT ENERGY IN POKEMON
    ModelPopupSelectEnergyInPokemon* m_modelSelectEnergyInPokemon;
    bool m_selectEnergiesInPokemonVisible;

    //MESSAGE
    bool m_messageVisible;
    QString m_messageContent;

    //COIN HEAD OR TAIL
    bool m_headOrTailVisible;
    int m_headOrTailValue;


    QList<int> displayAbstractPacket(AbstractPacket* packet, unsigned short quantity);
};

#endif // CTRLPOPUPS_H

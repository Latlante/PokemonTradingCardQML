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
    Q_PROPERTY(bool selectCardInPacketVisible READ selectCardInPacketVisible WRITE setSelectCardInPacketVisible NOTIFY selectCardInPacketVisibleChanged)

    Q_PROPERTY(bool popupSelectingAttacks_Visible READ popupSelectingAttacks_Visible WRITE setPopupSelectingAttacks_Visible NOTIFY popupSelectingAttacks_VisibleChanged)
    Q_PROPERTY(CardPokemon* popupSelectingAttacks_Card READ popupSelectingAttacks_Card NOTIFY popupSelectingAttacks_CardChanged)
    Q_PROPERTY(int popupSelectingAttacks_IndexAttack READ popupSelectingAttacks_IndexAttack WRITE setPopupSelectingAttacks_IndexAttack NOTIFY popupSelectingAttacks_IndexAttackChanged)
    Q_PROPERTY(bool popupSelectingAttacks_AuthorizeRetreat READ popupSelectingAttacks_AuthorizeRetreat WRITE setPopupSelectingAttacks_AuthorizeRetreat NOTIFY popupSelectingAttacks_AuthorizeRetreatChanged)

    Q_PROPERTY(bool selectEnergiesInPokemonVisible READ selectEnergiesInPokemonVisible WRITE setSelectEnergiesInPokemonVisible NOTIFY selectEnergiesInPokemonVisibleChanged)

    Q_PROPERTY(bool messageVisible READ messageVisible WRITE setMessageVisible NOTIFY messageVisibleChanged)
    Q_PROPERTY(QString messageContent READ messageContent WRITE setMessageContent NOTIFY messageContentChanged)

public:
    explicit CtrlPopups(QObject *parent = nullptr);
    ~CtrlPopups();

    static void declareQML();
    bool install(QQmlApplicationEngine *pEngine);

    //SELECT CARD IN PACKET
    Q_INVOKABLE ModelPopupSelectCardInPacket* modelSelectCardInPacket();
    Q_INVOKABLE QList<int> displayBench(BenchArea* packet);
    Q_INVOKABLE QList<int> displayDeck(PacketDeck* packet);
    Q_INVOKABLE QList<int> displayHand(PacketHand* packet);
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


    Q_INVOKABLE void selectionCardsFinished();

signals:
    void selectCardInPacketVisibleChanged();

    void popupSelectingAttacks_VisibleChanged();
    void popupSelectingAttacks_CardChanged();
    void popupSelectingAttacks_IndexAttackChanged();
    void popupSelectingAttacks_AuthorizeRetreatChanged();

    void selectEnergiesInPokemonVisibleChanged();

    void messageVisibleChanged();
    void messageContentChanged();

    void selectionFinished();

private:
    ModelPopupSelectCardInPacket* m_modelSelectCardInPacket;
    bool m_selectCardInPacketVisible;

    bool m_popupSelectingAttacks_Visible;
    CardPokemon* m_popupSelectingAttacks_Card;
    int m_popupSelectingAttacks_IndexAttack;
    bool m_popupSelectingAttacks_AuthorizeRetreat;

    ModelPopupSelectEnergyInPokemon* m_modelSelectEnergyInPokemon;
    bool m_selectEnergiesInPokemonVisible;

    bool m_messageVisible;
    QString m_messageContent;

    QList<int> displayAbstractPacket(AbstractPacket* packet);
};

#endif // CTRLPOPUPS_H

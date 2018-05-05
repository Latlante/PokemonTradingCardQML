#ifndef CTRLPOPUPS_H
#define CTRLPOPUPS_H

#include <QObject>

class AbstractCard;
class CardPokemon;
class AbstractPacket;
class BenchArea;
class PacketDeck;
class PacketHand;
class ModelPopupSelectCardInPacket;
class QQmlEngine;
class QQmlApplicationEngine;

class CtrlPopups : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool popupSelectingAttacks_Visible READ popupSelectingAttacks_Visible WRITE setPopupSelectingAttacks_Visible NOTIFY popupSelectingAttacks_VisibleChanged)
    Q_PROPERTY(CardPokemon* popupSelectingAttacks_Card READ popupSelectingAttacks_Card NOTIFY popupSelectingAttacks_CardChanged)
    Q_PROPERTY(int popupSelectingAttacks_IndexAttack READ popupSelectingAttacks_IndexAttack WRITE setPopupSelectingAttacks_IndexAttack NOTIFY popupSelectingAttacks_IndexAttackChanged)

public:
    explicit CtrlPopups(QObject *parent = nullptr);
    ~CtrlPopups();

    static void declareQML();
    bool install(QQmlApplicationEngine *pEngine);

    bool visible();
    void setVisible(bool state);

    bool popupSelectingAttacks_Visible();
    void setPopupSelectingAttacks_Visible(bool state);
    CardPokemon* popupSelectingAttacks_Card();
    void setPopupSelectingAttacks_Card(CardPokemon* card);
    int popupSelectingAttacks_IndexAttack();
    void setPopupSelectingAttacks_IndexAttack(int index);


    Q_INVOKABLE ModelPopupSelectCardInPacket* model();
    Q_INVOKABLE QList<int> displayBench(BenchArea* packet);
    Q_INVOKABLE QList<int> displayDeck(PacketDeck* packet);
    Q_INVOKABLE QList<int> displayHand(PacketHand* packet);

    int displayAttacks(CardPokemon* card);

    Q_INVOKABLE void selectionCardsFinished();

signals:
    void visibleChanged();
    void popupSelectingAttacks_VisibleChanged();
    void popupSelectingAttacks_CardChanged();
    void popupSelectingAttacks_IndexAttackChanged();
    void selectionFinished();

private:
    ModelPopupSelectCardInPacket* m_modelPopups;
    bool m_visible;
    bool m_popupSelectingAttacks_Visible;
    CardPokemon* m_popupSelectingAttacks_Card;
    int m_popupSelectingAttacks_IndexAttack;

    QList<int> displayAbstractPacket(AbstractPacket* packet);
};

#endif // CTRLPOPUPS_H

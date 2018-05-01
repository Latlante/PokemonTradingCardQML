#ifndef CTRLGAMEBOARD_H
#define CTRLGAMEBOARD_H

#include <QObject>

#include "gamemanager.h"

class QQmlEngine;
class QQmlApplicationEngine;
class MyModel;

class FactoryMainPageLoader;
class Player;
class CtrlSelectingCards;
class ListPlayers;
class ModelPopupSelectCardInPacket;
class BenchArea;
class PacketDeck;

class CtrlGameBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Player* currentPlayer READ currentPlayer NOTIFY currentPlayerChanged)
    Q_PROPERTY(ConstantesQML::StepGame gameStatus READ gameStatus NOTIFY gameStatusChanged)

public:
    explicit CtrlGameBoard(CtrlSelectingCards& ctrlSelectCards, CtrlPopups& ctrlPopups, QObject *parent = nullptr);
    ~CtrlGameBoard();

    static void declareQML();

    bool install(QQmlApplicationEngine *pEngine);

    Player* currentPlayer();
    ConstantesQML::StepGame gameStatus();

    Q_INVOKABLE ListPlayers* newListPlayers();
    Q_INVOKABLE FactoryMainPageLoader* factory();
    Q_INVOKABLE void initGame();
    Q_INVOKABLE Player* playerAt(int index);

    Q_INVOKABLE void onClicked_ButtonOk_SelectPlayers(QStringList listOfPlayers);
    Q_INVOKABLE void displaySelectingCardsForNextPlayers();
    Q_INVOKABLE void onClicked_ButtonOk_SelectCards();
    Q_INVOKABLE void onClicked_ButtonReadyPreparation();
    Q_INVOKABLE void onClicked_ButtonAttack(int indexAttack);


signals:
    void nextPlayer();
    void currentPlayerChanged();
    void gameStatusChanged();

private slots:
    void onListsComplete_CtrlSelectingCards();

private:
    GameManager* m_gameManager;
    FactoryMainPageLoader* m_factoryMainPageLoader;
    CtrlSelectingCards& m_ctrlSelectingCards;

};

#endif // CTRLGAMEBOARD_H

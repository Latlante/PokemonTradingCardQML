#ifndef CTRLGAMEBOARD_H
#define CTRLGAMEBOARD_H

#include <QObject>
class QQmlEngine;
class QQmlApplicationEngine;
class MyModel;

class FactoryMainPageLoader;
class GameManager;
class Player;
class CtrlSelectingCards;
class ListPlayers;
class BenchArea;
class PacketDeck;

class CtrlGameBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Player* currentPlayer READ currentPlayer NOTIFY currentPlayerChanged)
public:
    explicit CtrlGameBoard(CtrlSelectingCards& ctrlSelectCards, QObject *parent = nullptr);
    ~CtrlGameBoard();

    static void declareQML();

    bool install(QQmlApplicationEngine *pEngine);

    Player* currentPlayer();

    Q_INVOKABLE ListPlayers* newListPlayers();
    Q_INVOKABLE FactoryMainPageLoader* factory();
    Q_INVOKABLE void initGame(QStringList listOfPlayers);
    Q_INVOKABLE Player* createPlayer(const QString& name);
    Q_INVOKABLE Player* playerAt(int index);

    Q_INVOKABLE void onClicked_ButtonOk_SelectPlayers(QStringList listOfPlayers);
    Q_INVOKABLE void displaySelectingCardsForNextPlayers();
    Q_INVOKABLE void onClicked_ButtonOk_SelectCards();
    Q_INVOKABLE void onClicked_ButtonAttack(int indexAttack);

signals:
    void nextPlayer();
    void currentPlayerChanged();

private slots:
    void onListsComplete_CtrlSelectingCards();

private:
    GameManager* m_gameManager;
    FactoryMainPageLoader* m_factoryMainPageLoader;
    CtrlSelectingCards& m_ctrlSelectingCards;

};

#endif // CTRLGAMEBOARD_H

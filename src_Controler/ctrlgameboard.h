#ifndef CTRLGAMEBOARD_H
#define CTRLGAMEBOARD_H

#include <QObject>
class QQmlEngine;
class QQmlApplicationEngine;
class MyModel;

class FactoryMainPageLoader;
class GameManager;
class Player;
class ListPlayers;
class BenchArea;
class PacketDeck;

class CtrlGameBoard : public QObject
{
    Q_OBJECT
public:
    explicit CtrlGameBoard(QObject *parent = nullptr);
    ~CtrlGameBoard();

    static void declareQML();

    bool install(QQmlApplicationEngine *pEngine);

    Q_INVOKABLE ListPlayers* newListPlayers();
    Q_INVOKABLE FactoryMainPageLoader* factory();
    Q_INVOKABLE void initGame(QStringList listOfPlayers);
    Q_INVOKABLE Player* createPlayer(const QString& name);
    Q_INVOKABLE BenchArea* benchArea_P1();
    Q_INVOKABLE PacketDeck* deck_P1();
    Q_INVOKABLE Player* playerAt(int index);

signals:

private:
    GameManager* m_gameManager;
    FactoryMainPageLoader* m_factoryMainPageLoader;

};

#endif // CTRLGAMEBOARD_H

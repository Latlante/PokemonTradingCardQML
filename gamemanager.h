#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "player.h"

#include "common/constantesqml.h"

class AbstractCard;
class CtrlPopups;

class GameManager : public QObject
{
	Q_OBJECT
	
public:
    GameManager(CtrlPopups &ctrlPopups, QObject *parent = NULL);
	~GameManager();

    static GameManager* createInstance(CtrlPopups &ctrlPopups);
    static void deleteInstance();
    static GameManager* instance();
	
	void initGame();
    Player* addNewPlayer(QString name, QList<AbstractCard*> listCards);
    Player* currentPlayer();
    Player* playerAttacked();
    Player* playerAt(int index);
    ConstantesQML::StepGame gameStatus();
    void setGameStatus(ConstantesQML::StepGame step);
    void startGame();
    void drawFirstCards();
    void selectFirstPlayer();
	void nextPlayer();
    void attack(Player* playAttacking, unsigned short index, Player* playAttacked);
	void endOfTurn();
    Player *gameIsFinished();

    unsigned short headOrTail();

signals:
    void indexCurrentPlayerChanged();
    void gameStatusChanged();
    void replacePokemonFighter(Player*);

private slots:
    void onEndOfTurn_Player();

private:
    static const int m_NUMBER_FIRST_CARDS;
    static const int m_NUMBER_REWARDS;
    static GameManager *m_instance;
    CtrlPopups& m_ctrlPopups;
	QList<Player*> m_listPlayers;
    short m_indexCurrentPlayer;
    Player* m_playerAttacking;
    Player* m_playerAttacked;
    ConstantesQML::StepGame m_gameStatus;
	
	bool m_gameIsReady;

    void setIndexCurrentPlayer(int index);
    Player* ennemyOf(Player* play);

    void checkPokemonPoisoned();
    void checkPokemonDead();
    void checkStatusPokemonForNewRound();


};

#endif // GAMEMANAGER_H

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "player.h"

class AbstractCard;

class GameManager : public QObject
{
	Q_OBJECT
	
public:
	GameManager(QObject *parent = NULL);
	~GameManager();

    static GameManager* createInstance();
    static void deleteInstance();
    static GameManager* instance();
	
	void initGame();
	QList<AbstractCard*> chooseCards(const QString& name);
    Player* addNewPlayer(QString name, QList<AbstractCard*> listCards);
    Player* currentPlayer();
    Player* playerAttacked();
    Player* playerAt(int index);
    void startGame();
    void drawFirstCards();
	int selectFirstPlayer();
	void nextPlayer();
    void attack(Player* playAttacking, unsigned short index, Player* playAttacked);
	void endOfTurn();
	bool gameIsFinished();


private slots:
    void onEndOfTurn_Player();

private:
    static const int m_NUMBER_FIRST_CARDS;
    static const int m_NUMBER_REWARDS;
    static GameManager *m_instance;
	QList<Player*> m_listPlayers;
	unsigned short m_indexCurrentPlayer;
	
	bool m_gameIsReady;


};

#endif // GAMEMANAGER_H

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
    void selectFirstPlayer();
	void nextPlayer();
    void attack(Player* playAttacking, unsigned short index, Player* playAttacked);
	void endOfTurn();
    Player *gameIsFinished();

signals:
    void indexCurrentPlayerChanged();

private slots:
    void onEndOfTurn_Player();

private:
    static const int m_NUMBER_FIRST_CARDS;
    static const int m_NUMBER_REWARDS;
    static GameManager *m_instance;
	QList<Player*> m_listPlayers;
    short m_indexCurrentPlayer;
    Player* m_playerAttacking;
    Player* m_playerAttacked;
	
	bool m_gameIsReady;

    void setIndexCurrentPlayer(int index);
    Player* ennemyOf(Player* play);

    void checkPokemonPoisoned();
    void checkPokemonDead();
    void checkStatusPokemonForNewRound();


};

#endif // GAMEMANAGER_H

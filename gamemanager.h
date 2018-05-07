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
#ifdef TESTS_UNITAIRES
    GameManager(QObject *parent = NULL);
    static GameManager* createInstance();
#else
    GameManager(CtrlPopups &ctrlPopups, QObject *parent = NULL);
    static GameManager* createInstance(CtrlPopups &ctrlPopups);
#endif
	~GameManager();

    static void deleteInstance();
    static GameManager* instance();
	
    //Accesseurs
    Player* currentPlayer();
    Player* playerAttacked();
    Player* playerAt(int index);
    ConstantesQML::StepGame gameStatus();
    void setGameStatus(ConstantesQML::StepGame step);

    //Preparation de la partie
    void initGame();
    Player* addNewPlayer(QString name, QList<AbstractCard*> listCards);
    void startGame();
    void selectFirstPlayer();
	void nextPlayer();
    void attack(Player* playAttacking, unsigned short index, Player* playAttacked);
	void endOfTurn();
    Player *gameIsFinished();

    QList<int> displayBench(BenchArea* bench);
    QList<int> displayEnergiesForAPokemon(CardPokemon* pokemon);
    int displayAttacks(CardPokemon* card, bool blockRetreat = false);

#ifdef TESTS_UNITAIRES
    void setForcedValueHeadOrTail(bool forced, unsigned short value = 0);
#endif
    unsigned short headOrTail();


signals:
    void indexCurrentPlayerChanged();
    void gameStatusChanged();
    void replacePokemonFighter(Player*);

private slots:
    void onEndOfTurn_Player();

private:
#ifdef TESTS_UNITAIRES
    bool m_forcedValueHeadOrTail;
    unsigned short m_nextValueHeadOrTail;
#else
    CtrlPopups& m_ctrlPopups;
#endif

    static const int m_NUMBER_FIRST_CARDS;
    static const int m_NUMBER_REWARDS;
    static GameManager *m_instance;
	QList<Player*> m_listPlayers;
    short m_indexCurrentPlayer;
    Player* m_playerAttacking;
    Player* m_playerAttacked;
    ConstantesQML::StepGame m_gameStatus;
	
	bool m_gameIsReady;

    void setIndexCurrentPlayer(int index);
    Player* ennemyOf(Player* play);

    bool checkHandOfEachPlayer();
    void drawFirstCards(Player *play);
    void checkPokemonPoisoned();
    void checkPokemonDead();
    void checkStatusPokemonForNewRound();


};

#endif // GAMEMANAGER_H

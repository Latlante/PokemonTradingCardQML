#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include <QDebug>
#include <QObject>

#include "gamemanager.h"
#include "player.h"
#include "src_Cards/cardpokemon.h"
#include "src_Packets/bencharea.h"
#include "src_Packets/fightarea.h"

class AbstractAction
{
public:
	enum Enum_typeOfAction
	{
        Action_None = 0,
        Action_ChangeEnemyStatus = 1,                       //Status to apply
        Action_ChangeEnemyStatus_Random = 2,                //Status to apply
        Action_RemoveEnergyAttached = 3,                    //Number of energy
        Action_Healing = 4,                                 //Quantity of heal
        Action_ProtectedAgainstDamage = 5,
        Action_MoreDamageByEnergy = 6,                      //Quantity of damage per energy
        Action_ReplicateOneAttackFromEnemy = 7,
        Action_MoreDamageOnEnemyOrHimSelf = 8,              //Quantity of damage
        Action_PoisonedCustom = 9,
        Action_RandomDamageToHimself = 10,
        Action_DamageMultipliedByDoubleHeadOrTail = 11,     //Quantity of damage
        Action_DamageMultipliedByTripleHeadOrTail = 12,     //Quantity of damage
        Action_HurtEveryPokemonOnOwnBench = 13,
        Action_SwapPokemonBetweenFigthAndBench = 14,
        Action_Destruction = 15,                            //Quantity of damage for each pokemon en Bench
        Action_MoreDamageByEnemyDamage = 16,
        Action_Suicide = 17,
        Action_HurtHimself_Random = 18,
        Action_CompleteProtectionByPayingOneEnergy = 19,	//Type of energy
        Action_RemoveAllEnergiesAttached = 20,
        Action_RemoveOneEnergyOnEnemy = 21,                 //Type of energy
        Action_ReplicateLastAttackToEnemy = 22,
        Action_HurtHimself = 23,                            //Quantity of damage
        Action_UniqueAttack = 24,
        Action_AttackIfEnemyIsSleeping = 25,                //Quantity of damage
        Action_FullHealingByPayingOneEnergy = 26,           //Type of energy
        Action_AttackLessDamageOnHimself = 27,              //Orignal damage
        Action_MoreDamageByOwnDamage = 28,                  //Quantity of damage
        Action_BlockOneEnemyAttackForOneTurn = 29,
        Action_ChangeWeaknessOfEnemy = 30,
        Action_ChangeResistanceOfHimself = 31,
        Action_DamageOfHalfEnemyLifeLeft = 32,
        Action_DamageOnlyIfEnemyIsSpleeping = 33,            //Quantity of damage
        Action_ProtectedAgainstDamageRandom = 34,
        Action_EnemyDieIfYouDieInNextTurn = 35,
        Action_ChangeEnemyStatusOnHeadOrEnemyIsConfused = 36,//Status to apply
        Action_CanAttack_Random = 37,                       //Quantity of damage
        Action_NoDamageOnThreshold = 38,                    //Limit of damage
        Action_EnemyCanAttackOnNextTurn_Random = 39,

        ActionTrainer_FakeProfessorChen = 2003,
        ActionTrainer_TotalGuerison = 2012,
        ActionTrainer_ProfessorChen = 2018,
        ActionTrainer_SuperPotion = 2020,
        ActionTrainer_Leo = 2021,
        ActionTrainer_Potion = 2024
    };

    enum Enum_ElementsToCheck
    {
        CheckGameManager = 0,
        CheckPlayerAttacked,
        CheckPlayerAttacking,
        CheckPokemonAttacked,
        CheckPokemonAttacking,
        CheckBenchPlayerAttacked,
        CheckBenchPlayerAttacking
    };

    AbstractAction();
    virtual ~AbstractAction();
	
    virtual Enum_typeOfAction type() = 0;
    virtual QList<AbstractAction::Enum_ElementsToCheck> elementToCheck() = 0;
    void executeAction();

#ifdef TESTS_UNITAIRES
    QList<unsigned short> listCoins();
#endif


protected:
    virtual void action() = 0;

    unsigned short headOrTail();

    GameManager* gameManager();
    Player* playerAttacked();
    Player* playerAttacking();
    CardPokemon* pokemonAttacked();
    CardPokemon* pokemonAttacking();
    BenchArea* benchPlayerAttacked();
    BenchArea* benchPlayerAttacking();

private:
    GameManager* m_gameManager;
    Player* m_playerAttacked;
    Player* m_playerAttacking;
    CardPokemon* m_pokemonAttacked;
    CardPokemon* m_pokemonAttacking;
    BenchArea* m_benchPlayerAttacked;
    BenchArea* m_benchPlayerAttacking;

#ifdef TESTS_UNITAIRES
    QList<unsigned short> m_listCoins;
#endif

    bool checkGameManager();
    bool checkPlayerAttacked();
    bool checkPlayerAttacking();
    bool checkPokemonAttacked();
    bool checkPokemonAttacking();
    bool checkBenchPlayerAttacked();
    bool checkBenchPlayerAttacking();
};

#endif // ABSTRACTACTION_H

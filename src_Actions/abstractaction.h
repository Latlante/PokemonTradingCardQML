#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include <QObject>

class AbstractAction
{
public:
	enum Enum_typeOfAction
	{
        Action_None = 0,
        Action_ChangeEnemyStatus = 1,
        Action_ChangeEnemyStatus_Random = 2,
        Action_RemoveOneEnergyAttached = 3,
        Action_Healing = 4,
        Action_ProtectedAgainstDamage = 5,
        Action_MoreDamageByEnergy = 6,
        Action_ReplicateOneAttackToEnemy = 7,
        Action_MoreDamageOnEnemyOrHimSelf = 8,
        Action_PoisonedCustom = 9,
        Action_RandomDamageToHimself = 10,
        Action_DamageMultipliedByDoubleHeadOrTail = 11,
        Action_DamageMultipliedByTripleHeadOrTail = 12,
        Action_HurtEveryPokemonOnOwnBench = 13,
        Action_SwapPokemonBetweenFigthAndBench = 14,
        Action_Destruction = 15,
        Action_MoreDamageByEnemyDamage = 16,
        Action_Suicide = 17,
        Action_HurtHimself_Random = 18,
        Action_CompleteProtectionByPayingOneEnergy = 19,	//Type d'energie
        Action_RemoveAllEnergiesAttached = 20,
        Action_RemoveOneEnergyOnEnemy = 21,                 //Type d'energie
        Action_ReplicateLastAttackToEnemy = 22,
        Action_HurtHimself = 23,                            //Quantity of damage
        Action_UniqueAttack = 24,
        Action_AttackIfEnemyIsSleeping = 25,                //Quantity of damage
        Action_FullHealingByPayingOneEnergy = 26,           //Type d'energie
        Action_AttackLessDamageOnHimself = 27,              //Orignal damage
        Action_MoreDamageByOwnDamage = 28,                  //Quantity of damage
        Action_BlockOneEnemyAttackForOneTurn = 29,
        Action_ChangeWeaknessOfEnemy = 30,
        Action_ChangeResistanceOfHimself = 31,
        Action_DamageOfHalfEnemyLifeLeft = 32
    };

    AbstractAction();
    virtual ~AbstractAction();
	
    virtual Enum_typeOfAction type() = 0;
    virtual void executeAction() = 0;

    unsigned short id();
	const QString name();
	void setName(const QString& name);

private:
};

#endif // ABSTRACTACTION_H

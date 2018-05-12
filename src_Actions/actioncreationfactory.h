#ifndef ACTIONCREATIONFACTORY_H
#define ACTIONCREATIONFACTORY_H

#include "src_Actions/abstractaction.h"
#include "src_Cards/cardpokemon.h"

class ActionChangeWeaknessOfEnemy;
class ActionChangeResistanceOfHimself;

class ActionReplicateOneAttackFromEnemy;
class ActionReplicateLastDamageToEnemy;
class ActionUniqueAttack_Random;
class ActionAttackOnlyIfEnemyIsSleeping;
class ActionBlockOneEnemyAttackForOneTurn;
class ActionEnemyCanAttackOnNextTurn_Random;

class ActionMoreDamageByEnergy;
class ActionDamageMultipliedByHeadOrTail;
class ActionMoreDamageByEnemyDamage;
class ActionMoreDamageByOwnDamage;
class ActionAttackLessDamageOnHimself;
class ActionDamageOfHalfEnemyLifeLeft;
class ActionHurtHimself;
class ActionMoreDamageOrHurtHimSelf;
class ActionMoreDamageByEnergyOnEnemy;

class ActionRemoveEnergyAttached;
class ActionRemoveOneEnergyOnEnemy;

class ActionHealing;

class ActionProtectedAgainstDamage;
class ActionProtectedAgainstDamageRandom;
class ActionCompleteProtectionByPayingOneEnergy;
class ActionNoDamageOnThreshold;

class ActionChangeEnemyStatus;
class ActionChangeEnemyStatusRandom;
class ActionEnemyPoisoned;

class ActionHurtEveryPokemonOnOwnBench;
class ActionDieAndHurtEveryPokemonOnEachBench;
class ActionSwapPokemonBetweenFigthAndBench;

class ActionTrainer_FakeProfessorChen;
class ActionTrainer_Leo;
class ActionTrainer_Potion;
class ActionTrainer_ProfessorChen;
class ActionTrainer_SuperPotion;
class ActionTrainer_TotalGuerison;

class ActionCreationFactory
{
public:
    ActionCreationFactory();

    static AbstractAction* createAction(AbstractAction::Enum_typeOfAction idAction, QVariant arg1 = QVariant(), QVariant arg2 = QVariant());

    //GENERAL
    static ActionChangeWeaknessOfEnemy* createActionChangeWeaknessOfEnemy(AbstractCard::Enum_element element);
    static ActionChangeResistanceOfHimself* createActionChangeResistanceOfHimself(AbstractCard::Enum_element element);

    //ATTAQUES
    static ActionReplicateOneAttackFromEnemy* createActionReplicateOneAttackFromEnemy();
    static ActionReplicateLastDamageToEnemy* createActionReplicateLastDamageToEnemy();
    static ActionUniqueAttack_Random* createActionUniqueAttack_Random(unsigned short index);
    static ActionAttackOnlyIfEnemyIsSleeping* createActionAttackOnlyIfEnemyIsSleeping(unsigned short damage);
    static ActionBlockOneEnemyAttackForOneTurn* createActionBlockOneEnemyAttackForOneTurn();
    static ActionEnemyCanAttackOnNextTurn_Random* createActionEnemyCanAttackOnNextTurn_Random();


    //GESTION DES DEGATS
    static ActionMoreDamageByEnergy* createActionMoreDamageByEnergy(unsigned short damagePerEnergy, unsigned short indexOfAttack);
    static ActionDamageMultipliedByHeadOrTail* createActionDamageMultipliedByHeadOrTail(unsigned short damagePerHead, unsigned short numberOfCoins);
    static ActionMoreDamageByEnemyDamage* createActionMoreDamageByEnemyDamage(unsigned short damagePerMarquer);
    static ActionMoreDamageByOwnDamage* createActionMoreDamageByOwnDamage(unsigned short damage);
    static ActionAttackLessDamageOnHimself* createActionAttackLessDamageOnHimself(unsigned short originalDamage, unsigned short damagePerMarquer);
    static ActionDamageOfHalfEnemyLifeLeft* createActionDamageOfHalfEnemyLifeLeft();
    static ActionHurtHimself* createActionHurtHimself(unsigned short damage);
    static ActionMoreDamageOrHurtHimSelf* createActionMoreDamageOrHurtHimSelf(unsigned short damageOnHead, unsigned short damageOnTail);
    static ActionMoreDamageByEnergyOnEnemy* createActionMoreDamageByEnergyOnEnemy(unsigned short damagePerEnergy);

    //ENERGIES
    static ActionRemoveEnergyAttached* createActionRemoveEnergyAttached(unsigned short numberOfEnergies, AbstractCard::Enum_element elementToRemove);
    static ActionRemoveOneEnergyOnEnemy* createActionRemoveOneEnergyOnEnemy(unsigned short numberOfEnergies, AbstractCard::Enum_element elementToRemove);

    //SOIN
    static ActionHealing* createActionHealing(unsigned short pv, AbstractCard::Enum_element energyToPay);

    //PROTECTION
    static ActionProtectedAgainstDamage* createActionProtectedAgainstDamage();
    static ActionProtectedAgainstDamageRandom* createActionProtectedAgainstDamageRandom();
    static ActionCompleteProtectionByPayingOneEnergy* createActionCompleteProtectionByPayingOneEnergy();
    static ActionNoDamageOnThreshold* createActionNoDamageOnThreshold(unsigned short damage);

    //STATUS
    static ActionChangeEnemyStatus* createActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status);
    static ActionChangeEnemyStatusRandom* createActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon statusOnHead, CardPokemon::Enum_statusOfPokemon statusOnTail);
    static ActionEnemyPoisoned* createActionEnemyPoisoned(unsigned short damage);

    //BANC
    static ActionHurtEveryPokemonOnOwnBench* createActionHurtEveryPokemonOnOwnBench(unsigned short damage);
    static ActionDieAndHurtEveryPokemonOnEachBench* createActionDieAndHurtEveryPokemonOnEachBench(unsigned short damage);
    static ActionSwapPokemonBetweenFigthAndBench* createActionSwapPokemonBetweenFigthAndBench();

    //ACTIONS TRAINERS
    static ActionTrainer_FakeProfessorChen* createActionTrainer_FakeProfessorChen();
    static ActionTrainer_Leo* createActionTrainer_Leo();
    static ActionTrainer_Potion* createActionTrainer_Potion();
    static ActionTrainer_ProfessorChen* createActionTrainer_ProfessorChen();
    static ActionTrainer_SuperPotion* createActionTrainer_SuperPotion();
    static ActionTrainer_TotalGuerison* createActionTrainer_TotalGuerison();
};

#endif // ACTIONCREATIONFACTORY_H

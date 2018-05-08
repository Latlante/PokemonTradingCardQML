#ifndef ACTIONCREATIONFACTORY_H
#define ACTIONCREATIONFACTORY_H

#include "src_Actions/abstractaction.h"
#include "src_Cards/cardpokemon.h"

class ActionChangeEnemyStatus;
class ActionChangeEnemyStatusRandom;
class ActionCompleteProtectionByPayingOneEnergy;
class ActionDamageMultipliedByHeadOrTail;
class ActionEnemyPoisoned;
class ActionHealing;
class ActionHurtEveryPokemonOnOwnBench;
class ActionHurtHimself;
class ActionMoreDamageByEnemyDamage;
class ActionMoreDamageByEnergy;
class ActionMoreDamageOrHurtHimSelf;
class ActionProtectedAgainstDamage;
class ActionProtectedAgainstDamageRandom;
class ActionRemoveEnergyAttached;
class ActionReplicateOneAttackFromEnemy;
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

    //ATTAQUES
    static ActionReplicateOneAttackFromEnemy* createActionReplicateOneAttackFromEnemy();

    //GESTION DES DEGATS
    static ActionMoreDamageByEnergy* createActionMoreDamageByEnergy(unsigned short damagePerEnergy, unsigned short indexOfAttack);
    static ActionDamageMultipliedByHeadOrTail* createActionDamageMultipliedByHeadOrTail(unsigned short damagePerHead, unsigned short numberOfCoins);
    static ActionMoreDamageByEnemyDamage* createActionMoreDamageByEnemyDamage(unsigned short damagePerMarquer);
    static ActionHurtHimself* createActionHurtHimself(unsigned short damage);
    static ActionMoreDamageOrHurtHimSelf* createActionMoreDamageOrHurtHimSelf(unsigned short damageOnHead, unsigned short damageOnTail);

    //ENERGIES
    static ActionRemoveEnergyAttached* createActionRemoveEnergyAttached(unsigned short numberOfEnergies, AbstractCard::Enum_element elementToRemove);

    //SOIN
    static ActionHealing* createActionHealing(unsigned short pv, AbstractCard::Enum_element energyToPay);

    //PROTECTION
    static ActionProtectedAgainstDamage* createActionProtectedAgainstDamage();
    static ActionProtectedAgainstDamageRandom* createActionProtectedAgainstDamageRandom();
    static ActionCompleteProtectionByPayingOneEnergy* createActionCompleteProtectionByPayingOneEnergy();

    //STATUS
    static ActionChangeEnemyStatus* createActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status);
    static ActionChangeEnemyStatusRandom* createActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon statusOnHead, CardPokemon::Enum_statusOfPokemon statusOnTail);
    static ActionEnemyPoisoned* createActionEnemyPoisoned(unsigned short damage);

    //BANC
    static ActionHurtEveryPokemonOnOwnBench* createActionHurtEveryPokemonOnOwnBench(unsigned short damage);
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

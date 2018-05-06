#ifndef ACTIONCREATIONFACTORY_H
#define ACTIONCREATIONFACTORY_H

#include "src_Actions/abstractaction.h"
#include "src_Cards/cardpokemon.h"

class ActionChangeEnemyStatus;
class ActionChangeEnemyStatusRandom;
class ActionDamageMultipliedByDoubleHeadOrTail;
class ActionDamageMultipliedByTripleHeadOrTail;
class ActionHealing;
class ActionMoreDamageByEnergy;
class ActionMoreDamageOnEnemyOrHimself;
class ActionPoisonedCustom;
class ActionProtectedAgainstDamage;
class ActionRandomDamageToHimself;
class ActionRemoveEnergyAttached;
class ActionReplicateOneAttackFromEnemy;

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

    static AbstractAction* createAction(AbstractAction::Enum_typeOfAction idAction, QVariant arg);

    //ACTIONS POKEMON
    static ActionChangeEnemyStatus* createActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status);
    static ActionChangeEnemyStatusRandom* createActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon status);
    static ActionDamageMultipliedByDoubleHeadOrTail* createActionDamageMultipliedByDoubleHeadOrTail(unsigned short damagePerHead);
    static ActionDamageMultipliedByTripleHeadOrTail* createActionDamageMultipliedByTripleHeadOrTail(unsigned short damagePerHead);
    static ActionHealing* createActionHealing(unsigned short pv);
    static ActionMoreDamageByEnergy* createActionMoreDamageByEnergy(unsigned short damagePerEnergy);
    static ActionMoreDamageOnEnemyOrHimself* createActionMoreDamageOnEnemyOrHimself(unsigned short damage);
    static ActionPoisonedCustom* createActionPoisonedCustom(unsigned short damage);
    static ActionProtectedAgainstDamage* createActionProtectedAgainstDamage();
    static ActionRandomDamageToHimself* createActionRandomDamageToHimself(unsigned short damage);
    static ActionRemoveEnergyAttached* createActionRemoveEnergyAttached(unsigned short numberOfEnergies);
    static ActionReplicateOneAttackFromEnemy* createActionReplicateOneAttackFromEnemy();

    //ACTIONS TRAINERS
    static ActionTrainer_FakeProfessorChen* createActionTrainer_FakeProfessorChen();
    static ActionTrainer_Leo* createActionTrainer_Leo();
    static ActionTrainer_Potion* createActionTrainer_Potion();
    static ActionTrainer_ProfessorChen* createActionTrainer_ProfessorChen();
    static ActionTrainer_SuperPotion* createActionTrainer_SuperPotion();
    static ActionTrainer_TotalGuerison* createActionTrainer_TotalGuerison();
};

#endif // ACTIONCREATIONFACTORY_H

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
class ActionProtectedAgainstDamage;
class ActionRemoveEnergyAttached;

class ActionCreationFactory
{
public:
    ActionCreationFactory();

    static AbstractAction* createAction(AbstractAction::Enum_typeOfAction idAction, QVariant arg);

    static ActionChangeEnemyStatus* createActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status);
    static ActionChangeEnemyStatusRandom* createActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon status);
    static ActionDamageMultipliedByDoubleHeadOrTail* createActionDamageMultipliedByDoubleHeadOrTail(unsigned short damagePerHead);
    static ActionDamageMultipliedByTripleHeadOrTail* createActionDamageMultipliedByTripleHeadOrTail(unsigned short damagePerHead);
    static ActionHealing* createActionHealing(unsigned short pv);
    static ActionMoreDamageByEnergy* createActionMoreDamageByEnergy(unsigned short damagePerEnergy);
    static ActionMoreDamageOnEnemyOrHimself* createActionMoreDamageOnEnemyOrHimself(unsigned short damage);
    static ActionProtectedAgainstDamage* createActionProtectedAgainstDamage();
    static ActionRemoveEnergyAttached* createActionRemoveEnergyAttached(unsigned short numberOfEnergies);
};

#endif // ACTIONCREATIONFACTORY_H

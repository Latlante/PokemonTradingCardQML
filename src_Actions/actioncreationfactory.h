#ifndef ACTIONCREATIONFACTORY_H
#define ACTIONCREATIONFACTORY_H

#include "src_Actions/abstractaction.h"
#include "src_Cards/cardpokemon.h"

class ActionChangeEnemyStatus;
class ActionChangeEnemyStatusRandom;
class ActionHealing;
class ActionMoreDamageByEnergy;
class ActionProtectedAgainstDamage;
class ActionRemoveEnergyAttached;

class ActionCreationFactory
{
public:
    ActionCreationFactory();

    static AbstractAction* createAction(AbstractAction::Enum_typeOfAction idAction, QVariant arg);

    static ActionChangeEnemyStatus* createActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status);
    static ActionChangeEnemyStatusRandom* createActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon status);
    static ActionHealing* createActionHealing(unsigned short pv);
    static ActionMoreDamageByEnergy* createActionMoreDamageByEnergy(unsigned short damagePerEnergy);
    static ActionProtectedAgainstDamage* createActionProtectedAgainstDamage();
    static ActionRemoveEnergyAttached* createActionRemoveEnergyAttached(unsigned short numberOfEnergies);
};

#endif // ACTIONCREATIONFACTORY_H

#include "actioncreationfactory.h"

#include <QVariant>

#include "src_Actions/actionchangeenemystatus.h"
#include "src_Actions/actionchangeenemystatusrandom.h"
#include "src_Actions/actionhealing.h"
#include "src_Actions/actionmoredamagebyenergy.h"
#include "src_Actions/actionmoredamageonenemyorhimself.h"
#include "src_Actions/actionprotectedagainstdamage.h"
#include "src_Actions/actionremoveenergyattached.h"

ActionCreationFactory::ActionCreationFactory()
{

}

AbstractAction* ActionCreationFactory::createAction(AbstractAction::Enum_typeOfAction idAction, QVariant arg)
{
    bool ok;
    int argInt = 0;
    AbstractAction* actionToReturn = NULL;

    switch(idAction)
    {
    case AbstractAction::Action_ChangeEnemyStatus:
        {
            argInt = arg.toInt(&ok);
            if(ok)
                actionToReturn = createActionChangeEnemyStatus(static_cast<CardPokemon::Enum_statusOfPokemon>(argInt));
        }
        break;
    case AbstractAction::Action_ChangeEnemyStatus_Random:
        {
            argInt = arg.toInt(&ok);
            if(ok)
                actionToReturn = createActionChangeEnemyStatusRandom(static_cast<CardPokemon::Enum_statusOfPokemon>(argInt));
        }
        break;
    case AbstractAction::Action_Healing:
        {
            argInt = arg.toInt(&ok);
            if(ok)
                actionToReturn = createActionHealing(argInt);
        }
        break;
    case AbstractAction::Action_MoreDamageByEnergy:
        {
            argInt = arg.toInt(&ok);
            if(ok)
                actionToReturn = createActionMoreDamageByEnergy(argInt);
        }
        break;
    case AbstractAction::Action_MoreDamageOnEnemyOrHimSelf:
        {
        argInt = arg.toInt(&ok);
        if(ok)
            actionToReturn = createActionMoreDamageOnEnemyOrHimself(argInt);
        }
        break;
    case AbstractAction::Action_ProtectedAgainstDamage:
        {
            actionToReturn = createActionProtectedAgainstDamage();
        }
        break;
    case AbstractAction::Action_RemoveOneEnergyAttached:
        {
            argInt = arg.toInt(&ok);
            if(ok)
                actionToReturn = createActionRemoveEnergyAttached(argInt);
        }
        break;
    default:
        qWarning() << __PRETTY_FUNCTION__ << idAction << " is not ready yet";
        break;
    }

    return actionToReturn;
}

ActionChangeEnemyStatus* ActionCreationFactory::createActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status)
{
    return new ActionChangeEnemyStatus(status);
}

ActionChangeEnemyStatusRandom* ActionCreationFactory::createActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon status)
{
    return new ActionChangeEnemyStatusRandom(status);
}

ActionHealing* ActionCreationFactory::createActionHealing(unsigned short pv)
{
    return new ActionHealing(pv);
}

ActionMoreDamageByEnergy* ActionCreationFactory::createActionMoreDamageByEnergy(unsigned short damagePerEnergy)
{
    return new ActionMoreDamageByEnergy(damagePerEnergy);
}

ActionMoreDamageOnEnemyOrHimself* ActionCreationFactory::createActionMoreDamageOnEnemyOrHimself(unsigned short damage)
{
    return new ActionMoreDamageOnEnemyOrHimself();
}

ActionProtectedAgainstDamage* ActionCreationFactory::createActionProtectedAgainstDamage()
{
    return new ActionProtectedAgainstDamage();
}

ActionRemoveEnergyAttached* ActionCreationFactory::createActionRemoveEnergyAttached(unsigned short numberOfEnergies)
{
    return new ActionRemoveEnergyAttached(numberOfEnergies);
}

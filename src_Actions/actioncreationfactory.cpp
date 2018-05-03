#include "actioncreationfactory.h"

#include <QVariant>

#include "src_Actions/actionchangeenemystatus.h"
#include "src_Actions/actionchangeenemystatusrandom.h"
#include "src_Actions/actiondamagemultipliedbydoubleheadortail.h"
#include "src_Actions/actiondamagemultipliedbytripleheadortail.h"
#include "src_Actions/actionhealing.h"
#include "src_Actions/actionmoredamagebyenergy.h"
#include "src_Actions/actionmoredamageonenemyorhimself.h"
#include "src_Actions/actionprotectedagainstdamage.h"
#include "src_Actions/actionremoveenergyattached.h"

#include "src_Actions/actiontrainer_fakeprofessorchen.h"
#include "src_Actions/actiontrainer_leo.h"
#include "src_Actions/actiontrainer_potion.h"
#include "src_Actions/actiontrainer_professorchen.h"
#include "src_Actions/actiontrainer_superpotion.h"
#include "src_Actions/actiontrainer_totalguerison.h"

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
    //ACTIONS POKEMON
    case AbstractAction::Action_None:
        break;
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
    case AbstractAction::Action_DamageMultipliedByDoubleHeadOrTail:
        {
            argInt = arg.toInt(&ok);
            if(ok)
                actionToReturn = createActionDamageMultipliedByDoubleHeadOrTail(argInt);
        }
        break;
    case AbstractAction::Action_DamageMultipliedByTripleHeadOrTail:
        {
            argInt = arg.toInt(&ok);
            if(ok)
                actionToReturn = createActionDamageMultipliedByTripleHeadOrTail(argInt);
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
    //ACTIONS TRAINERS
    case AbstractAction::ActionTrainer_FakeProfessorChen:
        actionToReturn = createActionTrainer_FakeProfessorChen();
        break;
    case AbstractAction::ActionTrainer_Leo:
        actionToReturn = createActionTrainer_Leo();
        break;
    case AbstractAction::ActionTrainer_Potion:
        actionToReturn = createActionTrainer_Potion();
        break;
    case AbstractAction::ActionTrainer_ProfessorChen:
        actionToReturn = createActionTrainer_ProfessorChen();
        break;
    case AbstractAction::ActionTrainer_SuperPotion:
        actionToReturn = createActionTrainer_SuperPotion();
        break;
    case AbstractAction::ActionTrainer_TotalGuerison:
        actionToReturn = createActionTrainer_TotalGuerison();
        break;
    default:
        qWarning() << __PRETTY_FUNCTION__ << idAction << " is not ready yet";
        break;
    }

    return actionToReturn;
}

//ACTIONS POKEMON
ActionChangeEnemyStatus* ActionCreationFactory::createActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status)
{
    return new ActionChangeEnemyStatus(status);
}

ActionChangeEnemyStatusRandom* ActionCreationFactory::createActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon status)
{
    return new ActionChangeEnemyStatusRandom(status);
}

ActionDamageMultipliedByDoubleHeadOrTail* ActionCreationFactory::createActionDamageMultipliedByDoubleHeadOrTail(unsigned short damagePerHead)
{
    return new ActionDamageMultipliedByDoubleHeadOrTail(damagePerHead);
}

ActionDamageMultipliedByTripleHeadOrTail* ActionCreationFactory::createActionDamageMultipliedByTripleHeadOrTail(unsigned short damagePerHead)
{
    return new ActionDamageMultipliedByTripleHeadOrTail(damagePerHead);
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
    return new ActionMoreDamageOnEnemyOrHimself(damage);
}

ActionProtectedAgainstDamage* ActionCreationFactory::createActionProtectedAgainstDamage()
{
    return new ActionProtectedAgainstDamage();
}

ActionRemoveEnergyAttached* ActionCreationFactory::createActionRemoveEnergyAttached(unsigned short numberOfEnergies)
{
    return new ActionRemoveEnergyAttached(numberOfEnergies);
}

//ACTIONS TRAINERS
ActionTrainer_FakeProfessorChen* ActionCreationFactory::createActionTrainer_FakeProfessorChen()
{
    return new ActionTrainer_FakeProfessorChen();
}

ActionTrainer_Leo* ActionCreationFactory::createActionTrainer_Leo()
{
    return new ActionTrainer_Leo();
}

ActionTrainer_Potion* ActionCreationFactory::createActionTrainer_Potion()
{
    return new ActionTrainer_Potion();
}

ActionTrainer_ProfessorChen* ActionCreationFactory::createActionTrainer_ProfessorChen()
{
    return new ActionTrainer_ProfessorChen();
}

ActionTrainer_SuperPotion* ActionCreationFactory::createActionTrainer_SuperPotion()
{
    return new ActionTrainer_SuperPotion();
}

ActionTrainer_TotalGuerison* ActionCreationFactory::createActionTrainer_TotalGuerison()
{
    return new ActionTrainer_TotalGuerison();
}

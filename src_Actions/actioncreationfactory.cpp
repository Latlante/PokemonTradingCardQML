#include "actioncreationfactory.h"

#include <QVariant>

#include "src_Actions/attacks/actionchangeweaknessofenemy.h"
#include "src_Actions/attacks/actionchangeresistanceofhimself.h"

#include "src_Actions/actionreplicateoneattackfromenemy.h"
#include "src_Actions/attacks/actionreplicatelastdamagetoenemy.h"
#include "src_Actions/attacks/actionuniqueattack_random.h"
#include "src_Actions/attacks/actionattackonlyifenemyissleeping.h"
#include "src_Actions/attacks/actionblockoneenemyattackforoneturn.h"
#include "src_Actions/attacks/actionenemycanattackonnextturn_random.h"

#include "src_Actions/actionmoredamagebyenergy.h"
#include "src_Actions/actiondamagemultipliedbyheadortail.h"
#include "src_Actions/actionmoredamagebyenemydamage.h"
#include "src_Actions/actionhurthimself.h"
#include "src_Actions/actionmoredamageorhurthimself.h"

#include "src_Actions/actionremoveenergyattached.h"
#include "src_Actions/actionremoveoneenergyonenemy.h"

#include "src_Actions/actionhealing.h"

#include "src_Actions/actionprotectedagainstdamage.h"
#include "src_Actions/actionprotectedagainstdamagerandom.h"
#include "src_Actions/actioncompleteprotectionbypayingoneenergy.h"
#include "src_Actions/actionnodamageonthreshold.h"

#include "src_Actions/actionchangeenemystatus.h"
#include "src_Actions/actionchangeenemystatusrandom.h"
#include "src_Actions/actionenemypoisoned.h"

#include "src_Actions/actionhurteverypokemononownbench.h"
#include "src_Actions/actiondieandhurteverypokemononeachbench.h"
#include "src_Actions/actionswappokemonbetweenfigthandbench.h"

#include "src_Actions/actiontrainer_fakeprofessorchen.h"
#include "src_Actions/actiontrainer_leo.h"
#include "src_Actions/actiontrainer_potion.h"
#include "src_Actions/actiontrainer_professorchen.h"
#include "src_Actions/actiontrainer_superpotion.h"
#include "src_Actions/actiontrainer_totalguerison.h"

ActionCreationFactory::ActionCreationFactory()
{

}

AbstractAction* ActionCreationFactory::createAction(AbstractAction::Enum_typeOfAction idAction, QVariant arg1, QVariant arg2)
{
    bool ok;
    int argInt1 = 0;
    int argInt2 = 0;
    AbstractAction* actionToReturn = nullptr;

    switch(idAction)
    {
    //GENERAL
    case AbstractAction::Action_None:
        break;
    case AbstractAction::Action_ChangeWeaknessOfEnemy:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionChangeWeaknessOfEnemy(static_cast<AbstractCard::Enum_element>(argInt1));
        }
        break;
    case AbstractAction::Action_ChangeResistanceOfHimself:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionChangeResistanceOfHimself(static_cast<AbstractCard::Enum_element>(argInt1));
        }
        break;


    //ATTAQUES
    case AbstractAction::Action_ReplicateOneAttackFromEnemy:
        {
            actionToReturn = createActionReplicateOneAttackFromEnemy();
        }
        break;
    case AbstractAction::Action_ReplicateLastDamageToEnemy:
        {
            actionToReturn = createActionReplicateLastDamageToEnemy();
        }
        break;
    case AbstractAction::Action_UniqueAttack_Random:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionUniqueAttack_Random(argInt1);
        }
        break;
    case AbstractAction::Action_AttackOnlyIfEnemyIsSleeping:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionUniqueAttack_Random(argInt1);
        }
        break;
    case AbstractAction::Action_BlockOneEnemyAttackForOneTurn:
        {
            actionToReturn = createActionBlockOneEnemyAttackForOneTurn();
        }
        break;
    case AbstractAction::Action_EnemyCanAttackOnNextTurn_Random:
        {
            actionToReturn = createActionEnemyCanAttackOnNextTurn_Random();
        }
        break;


    //GESTION DES DEGATS
    case AbstractAction::Action_MoreDamageByEnergy:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                argInt2 = arg2.toInt(&ok);
            if(ok)
                actionToReturn = createActionMoreDamageByEnergy(argInt1, argInt2);
        }
        break;
    case AbstractAction::Action_DamageMultipliedByHeadOrTail:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                argInt2 = arg2.toInt(&ok);
            if(ok)
                actionToReturn = createActionDamageMultipliedByHeadOrTail(argInt1, argInt2);
        }
        break;
    case AbstractAction::Action_MoreDamageByEnemyDamage:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionMoreDamageByEnemyDamage(argInt1);
        }
        break;
    case AbstractAction::Action_HurtHimself:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionHurtHimself(argInt1);
        }
        break;
    case AbstractAction::Action_MoreDamageOrHurtHimSelf:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                argInt2 = arg2.toInt(&ok);
            if(ok)
                actionToReturn = createActionMoreDamageOrHurtHimSelf(argInt1, argInt2);
        }
        break;

    //ENERGIES
    case AbstractAction::Action_RemoveEnergyAttached:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                argInt2 = arg2.toInt(&ok);
            if(ok)
                actionToReturn = createActionRemoveEnergyAttached(argInt1, static_cast<AbstractCard::Enum_element>(argInt2));
        }
        break;
    case AbstractAction::Action_RemoveOneEnergyOnEnemy:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                argInt2 = arg2.toInt(&ok);
            if(ok)
                actionToReturn = createActionRemoveEnergyAttached(argInt1, static_cast<AbstractCard::Enum_element>(argInt2));
        }
        break;

    //SOIN
    case AbstractAction::Action_Healing:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                argInt2 = arg2.toInt(&ok);
            if(ok)
                actionToReturn = createActionHealing(argInt1, static_cast<AbstractCard::Enum_element>(argInt2));
        }
        break;

    //PROTECTION
    case AbstractAction::Action_ProtectedAgainstDamage:
        {
            actionToReturn = createActionProtectedAgainstDamage();
        }
        break;
    case AbstractAction::Action_ProtectedAgainstDamageRandom:
        {
            actionToReturn = createActionProtectedAgainstDamageRandom();
        }
        break;
    case AbstractAction::Action_CompleteProtectionByPayingOneEnergy:
        {
            actionToReturn = createActionCompleteProtectionByPayingOneEnergy();
        }
        break;
    case AbstractAction::Action_NoDamageOnThreshold:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionNoDamageOnThreshold(argInt1);
        }
        break;

    //STATUS
    case AbstractAction::Action_ChangeEnemyStatus:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionChangeEnemyStatus(static_cast<CardPokemon::Enum_statusOfPokemon>(argInt1));
        }
        break;
    case AbstractAction::Action_ChangeEnemyStatus_Random:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                argInt2 = arg2.toInt(&ok);
            if(ok)
                actionToReturn = createActionChangeEnemyStatusRandom(static_cast<CardPokemon::Enum_statusOfPokemon>(argInt1), static_cast<CardPokemon::Enum_statusOfPokemon>(argInt2));
        }
        break;
    case AbstractAction::Action_EnemyPoisoned:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionEnemyPoisoned(argInt1);
        }
        break;

    //BANC
    case AbstractAction::Action_HurtEveryPokemonOnOwnBench:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionHurtEveryPokemonOnOwnBench(argInt1);
        }
        break;
    case AbstractAction::Action_DieAndHurtEveryPokemonOnEachBench:
        {
            argInt1 = arg1.toInt(&ok);
            if(ok)
                actionToReturn = createActionDieAndHurtEveryPokemonOnEachBench(argInt1);
        }
        break;
    case AbstractAction::Action_SwapPokemonBetweenFigthAndBench:
        {
            actionToReturn = createActionSwapPokemonBetweenFigthAndBench();
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

//GENERAL
ActionChangeWeaknessOfEnemy* ActionCreationFactory::createActionChangeWeaknessOfEnemy(AbstractCard::Enum_element element)
{
    return new ActionChangeWeaknessOfEnemy(element);
}

ActionChangeResistanceOfHimself* ActionCreationFactory::createActionChangeResistanceOfHimself(AbstractCard::Enum_element element)
{
    return new ActionChangeResistanceOfHimself(element);
}

//ATTAQUES
ActionReplicateOneAttackFromEnemy* ActionCreationFactory::createActionReplicateOneAttackFromEnemy()
{
    return new ActionReplicateOneAttackFromEnemy();
}

ActionReplicateLastDamageToEnemy* ActionCreationFactory::createActionReplicateLastDamageToEnemy()
{
    return new ActionReplicateLastDamageToEnemy();
}

ActionUniqueAttack_Random* ActionCreationFactory::createActionUniqueAttack_Random(unsigned short index)
{
    return new ActionUniqueAttack_Random(index);
}

ActionAttackOnlyIfEnemyIsSleeping* ActionCreationFactory::createActionAttackOnlyIfEnemyIsSleeping(unsigned short damage)
{
    return new ActionAttackOnlyIfEnemyIsSleeping(damage);
}

ActionBlockOneEnemyAttackForOneTurn* ActionCreationFactory::createActionBlockOneEnemyAttackForOneTurn()
{
    return new ActionBlockOneEnemyAttackForOneTurn();
}

ActionEnemyCanAttackOnNextTurn_Random* ActionCreationFactory::createActionEnemyCanAttackOnNextTurn_Random()
{
    return new ActionEnemyCanAttackOnNextTurn_Random();
}

//GESTION DES DEGATS
ActionMoreDamageByEnergy* ActionCreationFactory::createActionMoreDamageByEnergy(unsigned short damagePerEnergy, unsigned short indexOfAttack)
{
    return new ActionMoreDamageByEnergy(damagePerEnergy, indexOfAttack);
}

ActionDamageMultipliedByHeadOrTail* ActionCreationFactory::createActionDamageMultipliedByHeadOrTail(unsigned short damagePerHead, unsigned short numberOfCoins)
{
    return new ActionDamageMultipliedByHeadOrTail(damagePerHead, numberOfCoins);
}

ActionMoreDamageByEnemyDamage* ActionCreationFactory::createActionMoreDamageByEnemyDamage(unsigned short damagePerMarquer)
{
    return new ActionMoreDamageByEnemyDamage(damagePerMarquer);
}

ActionHurtHimself* ActionCreationFactory::createActionHurtHimself(unsigned short damage)
{
    return new ActionHurtHimself(damage);
}

ActionMoreDamageOrHurtHimSelf* ActionCreationFactory::createActionMoreDamageOrHurtHimSelf(unsigned short damageOnHead, unsigned short damageOnTail)
{
    return new ActionMoreDamageOrHurtHimSelf(damageOnHead, damageOnTail);
}

//ENERGIES
ActionRemoveEnergyAttached* ActionCreationFactory::createActionRemoveEnergyAttached(unsigned short numberOfEnergies, AbstractCard::Enum_element elementToRemove)
{
    return new ActionRemoveEnergyAttached(numberOfEnergies, elementToRemove);
}

ActionRemoveOneEnergyOnEnemy* ActionCreationFactory::createActionRemoveOneEnergyOnEnemy(unsigned short numberOfEnergies, AbstractCard::Enum_element elementToRemove)
{
    return new ActionRemoveOneEnergyOnEnemy(numberOfEnergies, elementToRemove);
}

//SOIN
ActionHealing* ActionCreationFactory::createActionHealing(unsigned short pv, AbstractCard::Enum_element energyToPay)
{
    return new ActionHealing(pv, energyToPay);
}

//PROTECTION
ActionProtectedAgainstDamage* ActionCreationFactory::createActionProtectedAgainstDamage()
{
    return new ActionProtectedAgainstDamage();
}

ActionProtectedAgainstDamageRandom* ActionCreationFactory::createActionProtectedAgainstDamageRandom()
{
    return new ActionProtectedAgainstDamageRandom();
}

ActionCompleteProtectionByPayingOneEnergy* ActionCreationFactory::createActionCompleteProtectionByPayingOneEnergy()
{
    return new ActionCompleteProtectionByPayingOneEnergy();
}

ActionNoDamageOnThreshold* ActionCreationFactory::createActionNoDamageOnThreshold(unsigned short damage)
{
    return new ActionNoDamageOnThreshold(damage);
}

//STATUS
ActionChangeEnemyStatus* ActionCreationFactory::createActionChangeEnemyStatus(CardPokemon::Enum_statusOfPokemon status)
{
    return new ActionChangeEnemyStatus(status);
}

ActionChangeEnemyStatusRandom* ActionCreationFactory::createActionChangeEnemyStatusRandom(CardPokemon::Enum_statusOfPokemon statusOnHead, CardPokemon::Enum_statusOfPokemon statusOnTail)
{
    return new ActionChangeEnemyStatusRandom(statusOnHead, statusOnTail);
}

ActionEnemyPoisoned* ActionCreationFactory::createActionEnemyPoisoned(unsigned short damage)
{
    return new ActionEnemyPoisoned(damage);
}

//BANC
ActionHurtEveryPokemonOnOwnBench* ActionCreationFactory::createActionHurtEveryPokemonOnOwnBench(unsigned short damage)
{
    return new ActionHurtEveryPokemonOnOwnBench(damage);
}

ActionDieAndHurtEveryPokemonOnEachBench* ActionCreationFactory::createActionDieAndHurtEveryPokemonOnEachBench(unsigned short damage)
{
    return new ActionDieAndHurtEveryPokemonOnEachBench(damage);
}

ActionSwapPokemonBetweenFigthAndBench* ActionCreationFactory::createActionSwapPokemonBetweenFigthAndBench()
{
    return new ActionSwapPokemonBetweenFigthAndBench();
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

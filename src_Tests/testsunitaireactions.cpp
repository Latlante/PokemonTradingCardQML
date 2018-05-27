#include "testsunitaireactions.h"

#include "common/database.h"
#include "src_Actions/actioncreationfactory.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"
#include "src_Models/modellistenergies.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packethand.h"

const QString TestsUnitaireActions::m_pokAttacking_Name = "pok fighter";
const AbstractCard::Enum_element TestsUnitaireActions::m_pokAttacking_Element = AbstractCard::Element_Fire;
const unsigned short TestsUnitaireActions::m_pokAttacking_MaxLife = 200;
const unsigned short TestsUnitaireActions::m_pokAttacking_Life = 100;
const unsigned short TestsUnitaireActions::m_pokAttacking_AttDamage = 60;
const unsigned short TestsUnitaireActions::m_pokAttacking_AttQuantityOfEnergies = 3;
const unsigned short TestsUnitaireActions::m_pokAttacking_numberOfEnergiesAttached = 5;

const unsigned short TestsUnitaireActions::m_pokAttacked_Life = 300;
const unsigned short TestsUnitaireActions::m_pokAttacked_AttDamage = 20;
const AbstractAction::Enum_typeOfAction TestsUnitaireActions::m_pokAttacked_TypeOfAction = AbstractAction::Action_DamageMultipliedByHeadOrTail;
const unsigned short TestsUnitaireActions::m_pokAttacked_ActionDamage = 10;
const unsigned short TestsUnitaireActions::m_pokAttacked_ActionNumberOfCoins = 2;
const unsigned short TestsUnitaireActions::m_pokAttacked_AttQuantityOfEnergies = 1;
const unsigned short TestsUnitaireActions::m_pokAttacked_numberOfEnergiesAttached = 3;

TestsUnitaireActions::TestsUnitaireActions() :
    TestsUnitaires(),
    m_pokemonAttacking(nullptr),
    m_pokemonAttacked(nullptr),
    m_manager(nullptr)
{
#ifdef TESTS_UNITAIRES
    qDebug() << "********************************************";
    qDebug() << "*** Démarrage des tests unitaire actions ***";
    qDebug() << "********************************************";

    //Création de la zone de combat
    createGameManager();

    //Tests
        //GENERAL
    checkActionChangeWeaknessOfEnemy();
    checkActionChangeResistanceOfHimself();
    checkActionEnemyDieIfYouDieInNextTurn();

        //ATTAQUES
    checkActionReplicateOneAttackFromEnemy();
    checkActionReplicateLastDamageToEnemy();
    checkActionUniqueAttack_Random();
    checkActionAttackOnlyIfEnemyIsSpleeping();
    checkActionBlockOneEnemyAttackForOneTurn();
    checkActionEnemyCanAttackOnNextTurn_Random();

        //GESTION DES DEGATS
    checkActionMoreDamageByEnergy();
    checkActionDamageMultipliedByHeadOrTail();
    checkActionMoreDamageByEnemyDamage();
    checkActionMoreDamageByOwnDamage();
    checkActionAttackLessDamageOnHimself();
    checkActionDamageOfHalfEnemyLifeLeft();
    checkActionMoreDamageOrHurtHimSelf();
    checkActionMoreDamageByEnergyOnEnemy();

        //ENERGIES
    checkActionRemoveOneEnergyAttached();
    checkActionRemoveOneEnergyOnEnemy();

        //SOIN
    checkActionHealing();

        //PROTECTION
    //checkActionProtectedAgainstDamage();
    //checkActionProtectedAgainstDamageRandom();
    //checkActionCompleteProtectionByPayingOneEnergy();
    //checkActionNoDamageOnThreshold();
    //checkActionCompleteProtectionRandom();

        //STATUS
    checkActionChangeEnemyStatus();
    checkActionChangeEnemyStatusRandom();
    checkActionEnemyPoisoned();

        //BANC
    checkActionHurtEveryPokemonOnOwnBench();
    checkActionDieAndHurtEveryPokemonOnEachBench();
    checkActionSwapPokemonBetweenFigthAndBench();

    //Nettoyage
    deletePokemonToFight();

#endif
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
/******************************************************
 ***                  TESTS UNITAIRES               ***
 *****************************************************/
#ifdef TESTS_UNITAIRES
//GENERAL
void TestsUnitaireActions::checkActionChangeWeaknessOfEnemy()
{
    qDebug() << __PRETTY_FUNCTION__ << "Not tested yet";
}

void TestsUnitaireActions::checkActionChangeResistanceOfHimself()
{
    qDebug() << __PRETTY_FUNCTION__ << "Not tested yet";
}

void TestsUnitaireActions::checkActionEnemyDieIfYouDieInNextTurn()
{
    qDebug() << __PRETTY_FUNCTION__ << "Not tested yet";
}

//ATTAQUES
void TestsUnitaireActions::checkActionReplicateOneAttackFromEnemy()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_ReplicateOneAttackFromEnemy;
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: Attaque de base avant la copie
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
            //Vérification des dégats de base
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

            //Vérification de la nouvelle attaque
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].damage, m_pokAttacked_AttDamage);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), m_pokAttacked_TypeOfAction);

    //CAS N°2: Attaque après la copie
        //Attaque
    m_manager->setForcedValueHeadOrTail(true, 1);
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);
    m_manager->setForcedValueHeadOrTail(false);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage-m_pokAttacked_AttDamage-(m_pokAttacked_ActionNumberOfCoins*m_pokAttacked_ActionDamage));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);


    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionReplicateLastDamageToEnemy()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_ReplicateLastDamageToEnemy;
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: L'ennemie attaque en premier
    m_manager->nextPlayer();
        //Attaque
    m_manager->setForcedValueHeadOrTail(true, 1);
    statusOfAttack = m_pokemonAttacked->tryToAttack(0, m_pokemonAttacking);

        //Tests
            //Vérification des dégats de base
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life-m_pokAttacked_AttDamage-(m_pokAttacked_ActionNumberOfCoins*m_pokAttacked_ActionDamage));
    COMPARE(m_pokemonAttacking->status(), CardPokemon::Status_Normal);

    //CAS N°2: Renvoi des dégats
    m_manager->nextPlayer();
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage-m_pokAttacked_AttDamage-(m_pokAttacked_ActionNumberOfCoins*m_pokAttacked_ActionDamage));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);


    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionUniqueAttack_Random()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_UniqueAttack_Random;
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: Face = l'attaque fonctionne et ne sera pas bloquée
        //Attaque
    m_manager->setForcedValueHeadOrTail(true, 1);
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);
    COMPARE(m_pokemonAttacking->numberOfTurnAttackStillBlocks(0), 0);

    //CAS N°2: Pile = l'attaque fonctionne mais sera bloquée après ça
        //Attaque
    m_manager->setForcedValueHeadOrTail(true, 0);
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);
    COMPARE(m_pokemonAttacking->numberOfTurnAttackStillBlocks(0), -1);

    //CAS N°3: Impossible d'attaquer
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_AttackBlocked);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);
    COMPARE(m_pokemonAttacking->numberOfTurnAttackStillBlocks(0), -1);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionAttackOnlyIfEnemyIsSpleeping()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_AttackOnlyIfEnemyIsSleeping;
    int damage = 50;
    QVariant arg1Action = QVariant::fromValue(static_cast<int>(damage));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: Le pokémon attaqué ne dort pas
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°2: Le pokémon dort
    m_pokemonAttacked->setStatus(CardPokemon::Status_Slept);
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage)-damage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Slept);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionBlockOneEnemyAttackForOneTurn()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_BlockOneEnemyAttackForOneTurn;
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: On bloque l'attaque de l'ennemie
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°2: L'attaque est bloquée
    m_manager->nextPlayer();
        //Attaque
    statusOfAttack = m_pokemonAttacked->tryToAttack(0, m_pokemonAttacking);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_AttackBlocked);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionEnemyCanAttackOnNextTurn_Random()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_EnemyCanAttackOnNextTurn_Random;
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: On ne bloque pas l'attaque de l'ennemie
    m_manager->setForcedValueHeadOrTail(true, 0);
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°2: L'attaque n'est pas bloquée
    m_manager->nextPlayer();
        //Attaque
    statusOfAttack = m_pokemonAttacked->tryToAttack(0, m_pokemonAttacking);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life-m_pokAttacked_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°3: On bloque l'attaque de l'ennemie
    m_manager->nextPlayer();
    m_manager->setForcedValueHeadOrTail(true, 1);
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°4: L'attaque est bloquée
    m_manager->nextPlayer();
    m_manager->setForcedValueHeadOrTail(true, 0);
        //Attaque
    statusOfAttack = m_pokemonAttacked->tryToAttack(0, m_pokemonAttacking);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_AttackBlocked);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life-m_pokAttacked_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

//GESTION DES DEGATS
void TestsUnitaireActions::checkActionMoreDamageByEnergy()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_MoreDamageByEnergy;
    int quantityOfDamagePerEnergy = 10;
    int indexAttack = 0;
    QVariant arg1Action = QVariant::fromValue(static_cast<int>(quantityOfDamagePerEnergy));
    QVariant arg2Action = QVariant::fromValue(static_cast<int>(indexAttack));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action, arg2Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage-(quantityOfDamagePerEnergy*(m_pokAttacking_numberOfEnergiesAttached-m_pokAttacking_AttQuantityOfEnergies)));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionDamageMultipliedByHeadOrTail()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_DamageMultipliedByHeadOrTail;
    int quantityOfDamagePerHead = 10;
    int numberOfCoin = 2;
    QVariant arg1Action = QVariant::fromValue(static_cast<int>(quantityOfDamagePerHead));
    QVariant arg2Action = QVariant::fromValue(static_cast<int>(numberOfCoin));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action, arg2Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1
        //Init du random (2 piles)
    m_manager->setForcedValueHeadOrTail(true, 0);

        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°2
        //Init du random (2 faces)
    m_manager->setForcedValueHeadOrTail(true, 1);

        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage)-(quantityOfDamagePerHead*numberOfCoin));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionMoreDamageByEnemyDamage()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_MoreDamageByEnemyDamage;
    int quantityOfDamagePerMarquer = 10;
    QVariant arg1Action = QVariant::fromValue(static_cast<int>(quantityOfDamagePerMarquer));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: Pokémon attaqué a sa vie maximum
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°2: Pokémon attaqué a 50 de dégats
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(3*m_pokAttacking_AttDamage));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionMoreDamageByOwnDamage()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_MoreDamageByOwnDamage;
    int quantityOfDamagePerMarquer = 10;
    QVariant arg1Action = QVariant::fromValue(static_cast<int>(quantityOfDamagePerMarquer));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: Pokémon attaquant a 100 de dégats
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage-(m_pokAttacking_MaxLife-m_pokAttacking_Life));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°2: Pokémon attaquant a sa vie maximum
    m_pokemonAttacking->restoreLife(m_pokAttacking_MaxLife);
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage)-(m_pokAttacking_MaxLife-m_pokAttacking_Life));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionAttackLessDamageOnHimself()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_AttackLessDamageOnHimself;
    int originalDamage = 50;
    int quantityOfDamagePerMarquer = 10;
    QVariant arg1Action = QVariant::fromValue(static_cast<int>(originalDamage));
    QVariant arg2Action = QVariant::fromValue(static_cast<int>(quantityOfDamagePerMarquer));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action, arg2Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: Pokémon attaquant a 100 de dégats
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°2: Pokémon attaquant a sa vie maximum
    m_pokemonAttacking->restoreLife(m_pokAttacking_MaxLife);
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage)-originalDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionDamageOfHalfEnemyLifeLeft()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_DamageOfHalfEnemyLifeLeft;
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage-((m_pokAttacked_Life-m_pokAttacking_AttDamage)/2));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionMoreDamageOrHurtHimSelf()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_MoreDamageOrHurtHimSelf;
    int quantityOfDamage = 10;
    QVariant argAction = QVariant::fromValue(static_cast<int>(quantityOfDamage));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, argAction, argAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: PILE
        //Attaque
    m_manager->setForcedValueHeadOrTail(true, 0);
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life-quantityOfDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°2: FACE
        //Attaque
    m_manager->setForcedValueHeadOrTail(true, 1);
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage)-quantityOfDamage);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life-quantityOfDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionMoreDamageByEnergyOnEnemy()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_MoreDamageByEnergyOnEnemy;
    int quantityOfDamagePerEnergy = 10;
    QVariant arg1Action = QVariant::fromValue(static_cast<int>(quantityOfDamagePerEnergy));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage-(quantityOfDamagePerEnergy*m_pokAttacked_numberOfEnergiesAttached));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

//ENERGIES
void TestsUnitaireActions::checkActionRemoveOneEnergyAttached()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_RemoveEnergyAttached;
    int numberOfEnergyToRemoved = 1;
    QVariant arg1Action = QVariant::fromValue(numberOfEnergyToRemoved);
    QVariant arg2Action = QVariant::fromValue(static_cast<int>(m_pokAttacking_Element));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action, arg2Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);
    COMPARE(m_pokemonAttacking->countEnergies(), m_pokAttacking_numberOfEnergiesAttached-numberOfEnergyToRemoved);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionRemoveOneEnergyOnEnemy()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_RemoveOneEnergyOnEnemy;
    int numberOfEnergyToRemoved = 1;
    QVariant arg1Action = QVariant::fromValue(numberOfEnergyToRemoved);
    QVariant arg2Action = QVariant::fromValue(static_cast<int>(m_pokAttacking_Element));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action, arg2Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);
    COMPARE(m_pokemonAttacked->countEnergies(), m_pokAttacked_numberOfEnergiesAttached-numberOfEnergyToRemoved);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

//SOIN
void TestsUnitaireActions::checkActionHealing()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_Healing;
    int quantityOfHeal = 20;
    AbstractCard::Enum_element elementToPay = AbstractCard::Element_None;
    QVariant arg1Action = QVariant::fromValue(quantityOfHeal);
    QVariant arg2Action = QVariant::fromValue(static_cast<int>(elementToPay));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action, arg2Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life+quantityOfHeal);
    COMPARE(m_pokemonAttacking->countEnergies(), m_pokAttacking_numberOfEnergiesAttached);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

//PROTECTION
void TestsUnitaireActions::checkActionProtectedAgainstDamage()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_ProtectedAgainstDamage;
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: Première attaque
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);
    COMPARE(m_pokemonAttacking->isProtectedAgainstDamageForTheNextTurn(), true);

    //CAS N°2: Riposte
    m_manager->nextPlayer();
        //Attaque
    m_manager->setForcedValueHeadOrTail(true, 1);
    m_pokemonAttacking->setStatus(CardPokemon::Status_Slept);
    statusOfAttack = m_pokemonAttacked->tryToAttack(0, m_pokemonAttacking);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Slept);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionProtectedAgainstDamageRandom()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_ProtectedAgainstDamageRandom;
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: FACE = Protégé
    m_manager->setForcedValueHeadOrTail(true, 1);
        //Attaque
    m_pokemonAttacking->setStatus(CardPokemon::Status_Slept);
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Slept);
    COMPARE(m_pokemonAttacking->isProtectedAgainstDamageForTheNextTurn(), true);

    //CAS N°2: Riposte
    m_manager->nextPlayer();
        //Attaque
    statusOfAttack = m_pokemonAttacked->tryToAttack(0, m_pokemonAttacking);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°3: PILE = Aucune protection
    m_manager->nextPlayer();
    m_manager->setForcedValueHeadOrTail(true, 0);
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage));
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Slept);
    COMPARE(m_pokemonAttacking->isProtectedAgainstDamageForTheNextTurn(), false);

    //CAS N°4: Riposte
    m_manager->nextPlayer();
        //Attaque
    statusOfAttack = m_pokemonAttacked->tryToAttack(0, m_pokemonAttacking);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life-m_pokAttacked_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionCompleteProtectionByPayingOneEnergy()
{
    qDebug() << __PRETTY_FUNCTION__ << "Not tested yet";
}

void TestsUnitaireActions::checkActionNoDamageOnThreshold()
{
    qDebug() << __PRETTY_FUNCTION__ << "Not tested yet";
}

void TestsUnitaireActions::checkActionCompleteProtectionRandom()
{
    qDebug() << __PRETTY_FUNCTION__ << "Not tested yet";
}

//STATUS
void TestsUnitaireActions::checkActionChangeEnemyStatus()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_ChangeEnemyStatus;
    CardPokemon::Enum_statusOfPokemon statusAction = CardPokemon::Status_Paralyzed;
    QVariant argAction = QVariant::fromValue(static_cast<int>(statusAction));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, argAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), statusAction);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionChangeEnemyStatusRandom()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_ChangeEnemyStatus_Random;
    CardPokemon::Enum_statusOfPokemon statusActionHead = CardPokemon::Status_Paralyzed;
    CardPokemon::Enum_statusOfPokemon statusActionTail = CardPokemon::Status_None;
    QVariant arg1Action = QVariant::fromValue(static_cast<int>(statusActionHead));
    QVariant arg2Action = QVariant::fromValue(static_cast<int>(statusActionTail));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, arg1Action, arg2Action);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1
        //Init du random (PILE)
    m_manager->setForcedValueHeadOrTail(true, 0);

        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°2
        //Init du random (FACE)
    m_manager->setForcedValueHeadOrTail(true, 1);

        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage));
    COMPARE(m_pokemonAttacked->status(), statusActionHead);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionEnemyPoisoned()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_EnemyPoisoned;
    int quantityOfDamagePerRound = 20;
    QVariant argAction = QVariant::fromValue(static_cast<int>(quantityOfDamagePerRound));
    CardPokemon::Enum_StatusOfAttack statusOfAttack;

    //Création
    setActionOnPokemonAttacking(enumAction, argAction);

    //CAS GENERAL
    COMPARE(m_pokemonAttacking->listAttacks().count(), 1);
    Q_ASSERT(m_pokemonAttacking->listAttacks()[0].action != nullptr);
    COMPARE(m_pokemonAttacking->listAttacks()[0].action->type(), enumAction);

    //CAS N°1: Avant l'empoisonnement
        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Poisoned);

    //CAS N°2: Après l'empoisonnement
    m_manager->endOfTurn();

        //Tests
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage-quantityOfDamagePerRound);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Poisoned);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}


//BANC
void TestsUnitaireActions::checkActionHurtEveryPokemonOnOwnBench()
{
    qDebug() << __PRETTY_FUNCTION__ << "Not tested yet";
}

void TestsUnitaireActions::checkActionDieAndHurtEveryPokemonOnEachBench()
{
    qDebug() << __PRETTY_FUNCTION__ << "Not tested yet";
}

void TestsUnitaireActions::checkActionSwapPokemonBetweenFigthAndBench()
{
    qDebug() << __PRETTY_FUNCTION__ << "Not tested yet";
}



/******************************************************
 ***        CREATION DE LA ZONE DE COMBAT           ***
 *****************************************************/
void TestsUnitaireActions::createGameManager()
{
    //Informations
    Database db;
    QStringList listNamePlayers = QStringList() << "Alice" << "Corentin";
    QList<QList<int> > listCardsId;
    listCardsId.append(QList<int>() << 1005 << 1005 << 1005 << 1005 << 1005 << 1005 << 4 << 5 << 6 << 37 << 38 << 126 << 1010 << 1005 << 1005 << 1005 << 2024);
    listCardsId.append(QList<int>() << 1014 << 1014 << 1014 << 1014 << 1014 << 1014 << 7 << 8 << 9 << 86 << 87 << 113 << 1010 << 1014 << 1014 << 1014 << 2021);

    //Création
    m_manager = GameManager::createInstance();
    for(int i=0;i<listNamePlayers.count();++i)
    {
        QList<AbstractCard*> listAbCards;
        foreach(int id, listCardsId[i])
            listAbCards.append(db.cardById(id));

        m_manager->addNewPlayer(listNamePlayers[i], listAbCards);
    }

    m_manager->initGame();

    //Affiliation des pokémons aux zones de combat
    m_pokemonAttacking = createCustomPokemonAttacking();
    m_pokemonAttacking->setOwner(m_manager->currentPlayer());
    m_pokemonAttacked = createCustomPokemonAttacked();
    m_pokemonAttacked->setOwner(m_manager->playerAttacked());
    m_manager->currentPlayer()->fight()->addNewCard(m_pokemonAttacking);
    m_manager->playerAttacked()->fight()->addNewCard(m_pokemonAttacked);
}

CardPokemon* TestsUnitaireActions::createCustomPokemonAttacking()
{
    //Informations
    CardPokemon* cardPokemonToReturn = nullptr;
    const unsigned short pokemonId = 1;

    //Création du pokémon attaquant
    QList<AttackData> listAttacks = QList<AttackData>() << newAttackPokemonAttacking();
    cardPokemonToReturn = new CardPokemon(pokemonId,
                                          m_pokAttacking_Name,
                                          m_pokAttacking_Element,
                                          m_pokAttacking_MaxLife,
                                          listAttacks,
                                          CardPokemon::Element_None,
                                          CardPokemon::WeaknessResistance_Coef2,
                                          CardPokemon::Element_None,
                                          CardPokemon::WeaknessResistance_Coef2);

    cardPokemonToReturn->takeDamage(m_pokAttacking_MaxLife-m_pokAttacking_Life);

    //Association des énergies
    for(int i=0;i<m_pokAttacking_numberOfEnergiesAttached;++i)
    {
        CardEnergy* energy = new CardEnergy(1000+static_cast<int>(m_pokAttacking_Element), "Plante", m_pokAttacking_Element);
        cardPokemonToReturn->addEnergy(energy);
    }

    return cardPokemonToReturn;
}

void TestsUnitaireActions::setActionOnPokemonAttacking(AbstractAction::Enum_typeOfAction action, QVariant arg1, QVariant arg2)
{
    if(m_pokemonAttacking != nullptr)
    {
        AttackData attData = m_pokemonAttacking->listAttacks()[0];
        AbstractAction* actionAttack = attData.action;

        if(actionAttack != nullptr)
        {
            delete actionAttack;
            actionAttack = nullptr;
        }

        actionAttack = ActionCreationFactory::createAction(action, arg1, arg2);
        attData.action = actionAttack;
        m_pokemonAttacking->setAttacks(0, attData);
    }
}

AttackData TestsUnitaireActions::newAttackPokemonAttacking()
{
    //Informations
    const QString attack1Name = "attaque test";
    const QString attack1Description = "attaque description";

    //Création
    QMap<AbstractCard::Enum_element, unsigned short> costEnergies;
    costEnergies.insert(m_pokAttacking_Element, m_pokAttacking_AttQuantityOfEnergies);

    AttackData attack1;
    attack1.name = attack1Name;
    attack1.description = attack1Description;
    attack1.damage = m_pokAttacking_AttDamage;
    attack1.costEnergies = costEnergies;
    attack1.numberOfTurnAttackStillBlocks = 0;
    attack1.action = ActionCreationFactory::createAction(AbstractAction::Action_None);

    return attack1;
}

CardPokemon* TestsUnitaireActions::createCustomPokemonAttacked()
{
    //Informations
    CardPokemon* cardPokemonToReturn = nullptr;
    const unsigned short pokemonId = 2;
    const QString pokemonName = "pok attaqué";
    const AbstractCard::Enum_element pokemonElement = AbstractCard::Element_Fire;
    const QString attack1Name = "attaque test";
    const QString attack1Description = "attaque principale";
    const AbstractCard::Enum_element attack1CostEnergiesElement = AbstractCard::Element_Normal;
    const unsigned short attack1CostEnergiesQuantity = 0;   //Pour ne pas utiliser d'énergies

    //Création
    QMap<AbstractCard::Enum_element, unsigned short> costEnergies;
    costEnergies.insert(attack1CostEnergiesElement, attack1CostEnergiesQuantity);

    //Création du pokémon attaqué
    QList<AttackData> listAttacks;
    AttackData attack1;
    attack1.name = attack1Name;
    attack1.description = attack1Description;
    attack1.damage = m_pokAttacked_AttDamage;
    attack1.costEnergies = costEnergies;
    attack1.numberOfTurnAttackStillBlocks = 0;
    attack1.action = ActionCreationFactory::createAction(m_pokAttacked_TypeOfAction,
                                                         QVariant(m_pokAttacked_ActionDamage),
                                                         QVariant(m_pokAttacked_ActionNumberOfCoins));
    listAttacks.append(attack1);

    cardPokemonToReturn = new CardPokemon(pokemonId,
                                          pokemonName,
                                          pokemonElement,
                                          m_pokAttacked_Life,
                                          listAttacks,
                                          CardPokemon::Element_None,
                                          CardPokemon::WeaknessResistance_Coef2,
                                          CardPokemon::Element_None,
                                          CardPokemon::WeaknessResistance_Coef2);

    //Association des énergies
    for(int i=0;i<m_pokAttacked_numberOfEnergiesAttached;++i)
    {
        CardEnergy* energy = new CardEnergy(1000+static_cast<int>(pokemonElement), "Feu", pokemonElement);
        cardPokemonToReturn->addEnergy(energy);
    }

    return cardPokemonToReturn;
}

void TestsUnitaireActions::resetPokemons()
{
    m_manager->setForcedValueHeadOrTail(false);
    m_manager->selectFirstPlayer();

    if(m_pokemonAttacking != nullptr)
    {
        m_pokemonAttacking->restoreLife(m_pokAttacking_MaxLife);
        m_pokemonAttacking->takeDamage(m_pokAttacking_MaxLife-m_pokAttacking_Life);
        m_pokemonAttacking->setStatus(CardPokemon::Status_Normal);
        m_pokemonAttacking->setNumberOfTurnAttackStillBlocks(0, 0);
        m_pokemonAttacking->resetLastDamageReceived();

        while(m_pokemonAttacking->countEnergies() > m_pokAttacking_numberOfEnergiesAttached)
        {
            m_pokemonAttacking->moveEnergiesInTrash({m_pokemonAttacking->modelListOfEnergies()->energy(0)});
        }

        while(m_pokemonAttacking->countEnergies() < m_pokAttacking_numberOfEnergiesAttached)
        {
            CardEnergy* energy = new CardEnergy(1000+static_cast<int>(m_pokAttacking_Element), "Plante", m_pokAttacking_Element);
            m_pokemonAttacking->addEnergy(energy);
        }

        m_pokemonAttacking->replaceOneAttack(m_pokemonAttacking->lastIndexOfAttackUsed(), newAttackPokemonAttacking());

        //delete m_pokemonAttacking;
        //m_pokemonAttacking = createCustomPokemonAttacking();

    }

    if(m_pokemonAttacked != nullptr)
    {
        m_pokemonAttacked->restoreLife(m_pokAttacked_Life);
        //m_pokemonAttacked->takeDamage(m_pokAttacking_MaxLife-m_pokAttacking_Life);
        m_pokemonAttacked->setStatus(CardPokemon::Status_Normal);
        m_pokemonAttacked->setNumberOfTurnAttackStillBlocks(0, 0);
        m_pokemonAttacked->resetLastDamageReceived();
    }
}

void TestsUnitaireActions::deletePokemonToFight()
{
    if(m_pokemonAttacking != nullptr)
    {
        delete m_pokemonAttacking;
        m_pokemonAttacking = nullptr;
    }

    if(m_pokemonAttacked != nullptr)
    {
        delete m_pokemonAttacked;
        m_pokemonAttacked = nullptr;
    }
}
#endif

#ifndef TESTSUNITAIREACTIONS_H
#define TESTSUNITAIREACTIONS_H

#include "testsunitaires.h"

#include "src_Actions/abstractaction.h"
class GameManager;
class CardPokemon;

class TestsUnitaireActions : public TestsUnitaires
{
    Q_OBJECT
public:
    TestsUnitaireActions();

private:
    CardPokemon* m_pokemonAttacking;
    CardPokemon* m_pokemonAttacked;
    GameManager* m_manager;

    static const QString m_pokAttacking_Name;
    static const AbstractCard::Enum_element m_pokAttacking_Element;
    static const unsigned short m_pokAttacking_MaxLife;
    static const unsigned short m_pokAttacking_Life;
    static const AbstractCard::Enum_element m_pokAttacking_AttElement;
    static const unsigned short m_pokAttacking_AttDamage;
    static const unsigned short m_pokAttacking_AttQuantityOfEnergies;
    static const unsigned short m_pokAttacking_numberOfEnergiesAttached;

    static const unsigned short m_pokAttacked_Life;
    static const unsigned short m_pokAttacked_AttDamage;
    static const AbstractAction::Enum_typeOfAction m_pokAttacked_TypeOfAction;
    static const unsigned short m_pokAttacked_ActionDamage;
    static const unsigned short m_pokAttacked_ActionNumberOfCoins;

#ifdef TESTS_UNITAIRES
    //TESTS UNITAIRES
        //GENENRAL
    void checkActionChangeWeaknessOfEnemy();
    void checkActionChangeResistanceOfHimself();
    void checkActionEnemyDieIfYouDieInNextTurn();

        //ATTAQUES
    void checkActionReplicateOneAttackFromEnemy();
    void checkActionReplicateLastDamageToEnemy();
    void checkActionUniqueAttack_Random();

        //GESTION DES DEGATS
    void checkActionMoreDamageByEnergy();
    void checkActionDamageMultipliedByHeadOrTail();
    void checkActionMoreDamageOrHurtHimSelf();


        //ENERGIES
    void checkActionRemoveOneEnergyAttached();


        //SOIN
    void checkActionHealing();


        //PROTECTION
    void checkActionProtectedAgainstDamage();

        //STATUS
    void checkActionChangeEnemyStatus();
    void checkActionChangeEnemyStatusRandom();
    void checkActionEnemyPoisoned();

    void checkActionHurtEveryPokemonOnOwnBench();
    void checkActionSwapPokemonBetweenFigthAndBench();
    void checkActionDestruction();
    void checkActionMoreDamageByEnemyDamage();
    void checkActionSuicide();
    void checkActionHurtHimself_Random();
    void checkActionCompleteProtectionByPayingOneEnergy();
    void checkActionRemoveAllEnergiesAttached();
    void checkActionRemoveOneEnergyOnEnemy();
    void checkActionHurtHimself();
    void checkActionAttackIfEnemyIsSleeping();
    void checkActionFullHealingByPayingOneEnergy();
    void checkActionAttackLessDamageOnHimself();
    void checkActionMoreDamageByOwnDamage();
    void checkActionBlockOneEnemyAttackForOneTurn();
    void checkActionDamageOfHalfEnemyLifeLeft();
    void checkActionDamageOnlyIfEnemyIsSpleeping();
    void checkActionProtectedAgainstDamageRandom();
    void checkActionChangeEnemyStatusOnHeadOrEnemyIsConfused();
    void checkActionCanAttack_Random();
    void checkActionNoDamageOnThreshold();
    void checkActionEnemyCanAttackOnNextTurn_Random();

    //CREATION DE LA ZONE DE COMBAT
    void createGameManager();
    CardPokemon *createCustomPokemonAttacking();
    void setActionOnPokemonAttacking(AbstractAction::Enum_typeOfAction action, QVariant arg1 = QVariant(), QVariant arg2 = QVariant());
    AttackData newAttackPokemonAttacking();
    CardPokemon *createCustomPokemonAttacked();
    void resetPokemons();

    void deletePokemonToFight();
#endif
};

#endif // TESTSUNITAIREACTIONS_H

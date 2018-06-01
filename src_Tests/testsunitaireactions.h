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
    static const unsigned short m_pokAttacked_Att2Damage;
    static const AbstractAction::Enum_typeOfAction m_pokAttacked_TypeOfAction;
    static const unsigned short m_pokAttacked_ActionDamage;
    static const unsigned short m_pokAttacked_ActionNumberOfCoins;
    static const unsigned short m_pokAttacked_AttQuantityOfEnergies;
    static const unsigned short m_pokAttacked_numberOfEnergiesAttached;

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
    void checkActionAttackOnlyIfEnemyIsSpleeping();
    void checkActionBlockOneEnemyAttackForOneTurn();
    void checkActionEnemyCanAttackOnNextTurn_Random();

        //GESTION DES DEGATS
    void checkActionMoreDamageByEnergy();
    void checkActionDamageMultipliedByHeadOrTail();
    void checkActionMoreDamageByEnemyDamage();
    void checkActionMoreDamageByOwnDamage();
    void checkActionAttackLessDamageOnHimself();
    void checkActionDamageOfHalfEnemyLifeLeft();
    void checkActionMoreDamageOrHurtHimSelf();
    void checkActionMoreDamageByEnergyOnEnemy();

        //ENERGIES
    void checkActionRemoveOneEnergyAttached();
    void checkActionRemoveOneEnergyOnEnemy();

        //SOIN
    void checkActionHealing();

        //PROTECTION
    void checkActionProtectedAgainstDamage();
    void checkActionProtectedAgainstDamageRandom();
    void checkActionCompleteProtectionByPayingOneEnergy();
    void checkActionNoDamageOnThreshold();
    void checkActionCompleteProtectionRandom();

        //STATUS
    void checkActionChangeEnemyStatus();
    void checkActionChangeEnemyStatusRandom();
    void checkActionEnemyPoisoned();

        //BANC
    void checkActionHurtEveryPokemonOnOwnBench();
    void checkActionDieAndHurtEveryPokemonOnEachBench();
    void checkActionSwapPokemonBetweenFigthAndBench();



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

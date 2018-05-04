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

    //TESTS UNITAIRES
    void checkActionChangeEnemyStatus();
    void checkActionChangeEnemyStatusRandom();
    void checkActionRemoveOneEnergyAttached();
    void checkActionHealing();
    void checkActionProtectedAgainstDamage();
    void checkActionMoreDamageByEnergy();
    void checkActionReplicateOneAttackFromEnemy();
    void checkActionMoreDamageOnEnemyOrHimSelf();
    void checkActionPoisonedCustom();
    void checkActionRandomDamageToHimself();
    void checkActionDamageMultipliedByDoubleHeadOrTail();
    void checkActionDamageMultipliedByTripleHeadOrTail();
    void checkActionHurtEveryPokemonOnOwnBench();
    void checkActionSwapPokemonBetweenFigthAndBench();
    void checkActionDestruction();
    void checkActionMoreDamageByEnemyDamage();
    void checkActionSuicide();
    void checkActionHurtHimself_Random();
    void checkActionCompleteProtectionByPayingOneEnergy();
    void checkActionRemoveAllEnergiesAttached();
    void checkActionRemoveOneEnergyOnEnemy();
    void checkActionReplicateLastAttackToEnemy();
    void checkActionHurtHimself();
    void checkActionUniqueAttack();
    void checkActionAttackIfEnemyIsSleeping();
    void checkActionFullHealingByPayingOneEnergy();
    void checkActionAttackLessDamageOnHimself();
    void checkActionMoreDamageByOwnDamage();
    void checkActionBlockOneEnemyAttackForOneTurn();
    void checkActionChangeWeaknessOfEnemy();
    void checkActionChangeResistanceOfHimself();
    void checkActionDamageOfHalfEnemyLifeLeft();
    void checkActionDamageOnlyIfEnemyIsSpleeping();
    void checkActionProtectedAgainstDamageRandom();
    void checkActionEnemyDieIfYouDieInNextTurn();
    void checkActionChangeEnemyStatusOnHeadOrEnemyIsConfused();
    void checkActionCanAttack_Random();
    void checkActionNoDamageOnThreshold();
    void checkActionEnemyCanAttackOnNextTurn_Random();

    //CREATION DE LA ZONE DE COMBAT
    void createGameManager();
    CardPokemon *createCustomPokemonAttacking();
    void setActionOnPokemonAttacking(AbstractAction::Enum_typeOfAction action, QVariant arg = QVariant());
    CardPokemon *createCustomPokemonAttacked();
    void resetPokemons();
    void deletePokemonToFight();
};

#endif // TESTSUNITAIREACTIONS_H

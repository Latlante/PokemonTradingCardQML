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

    //TESTS UNITAIRES
    void checkActionChangeEnemyStatus();
    void checkActionChangeEnemyStatusRandom();
    void checkActionRemoveOneEnergyAttached();
    void checkActionHealing();

    //CREATION DE LA ZONE DE COMBAT
    void createGameManager();
    CardPokemon *createCustomPokemonAttacking();
    void setActionOnPokemonAttacking(AbstractAction::Enum_typeOfAction action, QVariant arg);
    CardPokemon *createCustomPokemonAttacked();
    void resetPokemons();
    void deletePokemonToFight();
};

#endif // TESTSUNITAIREACTIONS_H

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

    void checkActionChangeEnemyStatus();


    void createGameManager();
    CardPokemon *createCustomPokemonToFight(AbstractAction::Enum_typeOfAction action, QVariant arg);
    void deletePokemonToFight();
};

#endif // TESTSUNITAIREACTIONS_H

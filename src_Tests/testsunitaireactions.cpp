#include "testsunitaireactions.h"

#include "src_Actions/actioncreationfactory.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"

TestsUnitaireActions::TestsUnitaireActions() :
    TestsUnitaires(),
    m_pokemonAttacking(nullptr),
    m_pokemonAttacked(nullptr)
{
    qDebug() << "********************************************";
    qDebug() << "*** Démarrage des tests unitaire actions ***";
    qDebug() << "********************************************";

    checkActionChangeEnemyStatus();
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
void TestsUnitaireActions::checkActionChangeEnemyStatus()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_ChangeEnemyStatus;
    CardPokemon::Enum_statusOfPokemon statusAction = CardPokemon::Status_Paralyzed;
    QVariant argAction = QVariant::fromValue(static_cast<int>(statusAction));

    //Création
    createPokemonToFight(enumAction, argAction);

    //Attaque
    m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

    //Tests
    COMPARE(m_pokemonAttacked->lifeLeft(), 50);
    COMPARE(m_pokemonAttacked->status(), statusAction);

    qDebug() << __PRETTY_FUNCTION__ << "OK";

    //Nettoyage
    deletePokemonToFight();
}



void TestsUnitaireActions::createPokemonToFight(AbstractAction::Enum_typeOfAction action, QVariant arg)
{
    //Informations
    const unsigned short pokemonId = 1;
    const QString pokemonName = "pokemon test";
    const AbstractCard::Enum_element pokemonElement = AbstractCard::Element_Fire;
    const unsigned short pokemonLife = 100;
    const QString attack1Name = "attaque test";
    const QString attack1Description = "attaque principale";
    const unsigned short attack1Damage = 50;
    const AbstractCard::Enum_element attack1CostEnergiesElement = AbstractCard::Element_Grass;
    const unsigned short attack1CostEnergiesQuantity = 0;   //Pour ne pas utiliser d'énergies

    //Création
    QMap<AbstractCard::Enum_element, unsigned short> costEnergies;
    costEnergies.insert(attack1CostEnergiesElement, attack1CostEnergiesQuantity);

    //Création du pokémon attaquant
    if(m_pokemonAttacking == nullptr)
    {
        QList<AttackData> listAttacks;
        AttackData attack1;
        attack1.name = attack1Name;
        attack1.description = attack1Description;
        attack1.damage = attack1Damage;
        attack1.costEnergies = costEnergies;
        attack1.action = ActionCreationFactory::createAction(action, arg);
        listAttacks.append(attack1);

        m_pokemonAttacking = new CardPokemon(pokemonId,
                                             pokemonName,
                                             pokemonElement,
                                             pokemonLife,
                                             listAttacks);
    }

    //Création du pokémon attaqué
    if(m_pokemonAttacked == nullptr)
    {
        QList<AttackData> listAttacks;
        AttackData attack1;
        attack1.name = attack1Name;
        attack1.description = attack1Description;
        attack1.damage = attack1Damage;
        attack1.costEnergies = costEnergies;
        //Pas d'action pour le pokémon attaqué
        listAttacks.append(attack1);

        m_pokemonAttacked = new CardPokemon(pokemonId,
                                            pokemonName,
                                            pokemonElement,
                                            pokemonLife,
                                            listAttacks);
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

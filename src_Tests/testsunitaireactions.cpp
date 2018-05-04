#include "testsunitaireactions.h"

#include "common/database.h"
#include "src_Actions/actioncreationfactory.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packethand.h"

const QString TestsUnitaireActions::m_pokAttacking_Name = "pok fighter";
const AbstractCard::Enum_element TestsUnitaireActions::m_pokAttacking_Element = AbstractCard::Element_Fire;
const unsigned short TestsUnitaireActions::m_pokAttacking_MaxLife = 200;
const unsigned short TestsUnitaireActions::m_pokAttacking_Life = 100;
const AbstractCard::Enum_element TestsUnitaireActions::m_pokAttacking_AttElement = AbstractCard::Element_Grass;
const unsigned short TestsUnitaireActions::m_pokAttacking_AttDamage = 30;
const unsigned short TestsUnitaireActions::m_pokAttacking_AttQuantityOfEnergies = 3;
const unsigned short TestsUnitaireActions::m_pokAttacking_numberOfEnergiesAttached = 3;

const unsigned short TestsUnitaireActions::m_pokAttacked_Life = 100;

TestsUnitaireActions::TestsUnitaireActions() :
    TestsUnitaires(),
    m_pokemonAttacking(nullptr),
    m_pokemonAttacked(nullptr),
    m_manager(nullptr)
{
    qDebug() << "********************************************";
    qDebug() << "*** Démarrage des tests unitaire actions ***";
    qDebug() << "********************************************";

    //Création de la zone de combat
    createGameManager();

    //Tests
    checkActionChangeEnemyStatus();
    checkActionChangeEnemyStatusRandom();
    checkActionRemoveOneEnergyAttached();

    //Nettoyage
    deletePokemonToFight();
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
/******************************************************
 ***                  TESTS UNITAIRES               ***
 *****************************************************/
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
        //Init du random (PILE)
    m_manager->setNextValueHeadOrTail(0);

        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-m_pokAttacking_AttDamage);
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);

    //CAS N°2
        //Init du random (FACE)
    m_manager->setNextValueHeadOrTail(1);

        //Attaque
    statusOfAttack = m_pokemonAttacking->tryToAttack(0, m_pokemonAttacked);

        //Tests
    COMPARE(statusOfAttack, CardPokemon::Attack_OK);
    COMPARE(m_pokemonAttacked->lifeLeft(), m_pokAttacked_Life-(2*m_pokAttacking_AttDamage));
    COMPARE(m_pokemonAttacked->status(), statusAction);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionRemoveOneEnergyAttached()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_RemoveEnergyAttached;
    int numberOfEnergyToRemoved = 1;
    QVariant argAction = QVariant::fromValue(static_cast<int>(numberOfEnergyToRemoved));
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
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);
    COMPARE(m_pokemonAttacking->countEnergies(), m_pokAttacking_numberOfEnergiesAttached-numberOfEnergyToRemoved);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
}

void TestsUnitaireActions::checkActionHealing()
{
    //Informations
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_Healing;
    int quantityOfHeal = 20;
    QVariant argAction = QVariant::fromValue(static_cast<int>(quantityOfHeal));
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
    COMPARE(m_pokemonAttacked->status(), CardPokemon::Status_Normal);
    COMPARE(m_pokemonAttacking->lifeLeft(), m_pokAttacking_Life+quantityOfHeal);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
    resetPokemons();
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
    m_pokemonAttacked = createCustomPokemonAttacked();
    m_manager->currentPlayer()->fight()->addNewCard(m_pokemonAttacking);
    m_manager->playerAttacked()->fight()->addNewCard(m_pokemonAttacked);
}

CardPokemon* TestsUnitaireActions::createCustomPokemonAttacking()
{
    //Informations
    CardPokemon* cardPokemonToReturn = nullptr;
    const unsigned short pokemonId = 1;
    const QString attack1Name = "attaque test";
    const QString attack1Description = "attaque description";

    //Création
    QMap<AbstractCard::Enum_element, unsigned short> costEnergies;
    costEnergies.insert(m_pokAttacking_AttElement, m_pokAttacking_AttQuantityOfEnergies);

    //Création du pokémon attaquant
    QList<AttackData> listAttacks;
    AttackData attack1;
    attack1.name = attack1Name;
    attack1.description = attack1Description;
    attack1.damage = m_pokAttacking_AttDamage;
    attack1.costEnergies = costEnergies;
    attack1.action = ActionCreationFactory::createAction(AbstractAction::Action_None, QVariant());
    listAttacks.append(attack1);

    cardPokemonToReturn = new CardPokemon(pokemonId,
                                         m_pokAttacking_Name,
                                         m_pokAttacking_Element,
                                         m_pokAttacking_MaxLife,
                                         listAttacks);

    //Association des énergies
    for(int i=0;i<m_pokAttacking_numberOfEnergiesAttached;++i)
    {
        CardEnergy* energy = new CardEnergy(1000+static_cast<int>(m_pokAttacking_AttElement), "Plante", m_pokAttacking_AttElement);
        cardPokemonToReturn->addEnergy(energy);
    }

    return cardPokemonToReturn;
}

void TestsUnitaireActions::setActionOnPokemonAttacking(AbstractAction::Enum_typeOfAction action, QVariant arg)
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

        actionAttack = ActionCreationFactory::createAction(action, arg);
        attData.action = actionAttack;
        m_pokemonAttacking->setAttacks(0, attData);
    }
}

CardPokemon* TestsUnitaireActions::createCustomPokemonAttacked()
{
    //Informations
    CardPokemon* cardPokemonToReturn = nullptr;
    const unsigned short pokemonId = 2;
    const QString pokemonName = "pok attaqué";
    const AbstractCard::Enum_element pokemonElement = AbstractCard::Element_Fire;
    const unsigned short pokemonLife = 100;
    const QString attack1Name = "attaque test";
    const QString attack1Description = "attaque principale";
    const unsigned short attack1Damage = 0;
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
    attack1.damage = attack1Damage;
    attack1.costEnergies = costEnergies;
    listAttacks.append(attack1);

    cardPokemonToReturn = new CardPokemon(pokemonId,
                                         pokemonName,
                                         pokemonElement,
                                         pokemonLife,
                                         listAttacks);

    return cardPokemonToReturn;
}

void TestsUnitaireActions::resetPokemons()
{
    if(m_pokemonAttacking != nullptr)
    {
        m_pokemonAttacked->restoreLife(m_pokAttacking_MaxLife);
        m_pokemonAttacked->takeDamage(m_pokAttacking_MaxLife-m_pokAttacking_Life);
        m_pokemonAttacked->setStatus(CardPokemon::Status_Normal);

        while(m_pokemonAttacking->countEnergies() > m_pokAttacking_numberOfEnergiesAttached)
        {
            m_pokemonAttacking->removeEnergy(0);
        }

        while(m_pokemonAttacking->countEnergies() < m_pokAttacking_numberOfEnergiesAttached)
        {
            CardEnergy* energy = new CardEnergy(1000+static_cast<int>(m_pokAttacking_AttElement), "Plante", m_pokAttacking_AttElement);
            m_pokemonAttacking->addEnergy(energy);
        }

    }

    if(m_pokemonAttacked != nullptr)
    {
        m_pokemonAttacked->restoreLife(m_pokAttacked_Life);
        //m_pokemonAttacked->takeDamage(m_pokAttacking_MaxLife-m_pokAttacking_Life);
        m_pokemonAttacked->setStatus(CardPokemon::Status_Normal);
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

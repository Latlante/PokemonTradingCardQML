#include "testsunitaireactions.h"

#include "common/database.h"
#include "src_Actions/actioncreationfactory.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packethand.h"

TestsUnitaireActions::TestsUnitaireActions() :
    TestsUnitaires(),
    m_pokemonAttacking(nullptr),
    m_pokemonAttacked(nullptr),
    m_manager(nullptr)
{
    qDebug() << "********************************************";
    qDebug() << "*** Démarrage des tests unitaire actions ***";
    qDebug() << "********************************************";

    createGameManager();

    checkActionChangeEnemyStatus();
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
void TestsUnitaireActions::checkActionChangeEnemyStatus()
{
    //Informations
    CardPokemon* pokAttacking = nullptr;
    CardPokemon* pokAttacked = nullptr;
    AbstractAction::Enum_typeOfAction enumAction = AbstractAction::Action_ChangeEnemyStatus;
    CardPokemon::Enum_statusOfPokemon statusAction = CardPokemon::Status_Paralyzed;
    QVariant argAction = QVariant::fromValue(static_cast<int>(statusAction));
    bool attackOk = false;

    //Création
    pokAttacking = createCustomPokemonToFight(enumAction, argAction);
    AbstractCard* abCard = m_manager->playerAttacked()->hand()->card(0);

    if(abCard->type() == AbstractCard::TypeOfCard_Pokemon)
        pokAttacked = static_cast<CardPokemon*>(abCard);
    else
        COMPARE("La carte selectionnee dans la main n'est pas un pokemon", "");

    //Transfert dans la zone de combat
    m_manager->currentPlayer()->fight()->addNewCard(pokAttacking);
    m_manager->playerAttacked()->moveCardFromHandToFight(0);


    //Attaque
    attackOk = pokAttacking->tryToAttack(0, pokAttacked);

    //Tests
    COMPARE(attackOk, true);
    COMPARE(pokAttacked->lifeLeft(), 10);
    COMPARE(pokAttacked->status(), statusAction);

    qDebug() << __PRETTY_FUNCTION__ << "OK";

    //Nettoyage
    deletePokemonToFight();
}

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

}

CardPokemon* TestsUnitaireActions::createCustomPokemonToFight(AbstractAction::Enum_typeOfAction action, QVariant arg)
{
    //Informations
    CardPokemon* cardPokemonToReturn = nullptr;
    const unsigned short pokemonId = 1;
    const QString pokemonName = "pokemon test";
    const AbstractCard::Enum_element pokemonElement = AbstractCard::Element_Fire;
    const unsigned short pokemonLife = 100;
    const QString attack1Name = "attaque test";
    const QString attack1Description = "attaque principale";
    const unsigned short attack1Damage = 30;
    const AbstractCard::Enum_element attack1CostEnergiesElement = AbstractCard::Element_Grass;
    const unsigned short attack1CostEnergiesQuantity = 0;   //Pour ne pas utiliser d'énergies

    //Création
    QMap<AbstractCard::Enum_element, unsigned short> costEnergies;
    costEnergies.insert(attack1CostEnergiesElement, attack1CostEnergiesQuantity);

    //Création du pokémon attaquant
    QList<AttackData> listAttacks;
    AttackData attack1;
    attack1.name = attack1Name;
    attack1.description = attack1Description;
    attack1.damage = attack1Damage;
    attack1.costEnergies = costEnergies;
    attack1.action = ActionCreationFactory::createAction(action, arg);
    listAttacks.append(attack1);

    cardPokemonToReturn = new CardPokemon(pokemonId,
                                         pokemonName,
                                         pokemonElement,
                                         pokemonLife,
                                         listAttacks);


    //Création du pokémon attaqué
    /*if(m_pokemonAttacked == nullptr)
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
    }*/

    return cardPokemonToReturn;
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

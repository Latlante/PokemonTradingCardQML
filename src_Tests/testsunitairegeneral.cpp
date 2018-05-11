#include "testsunitairegeneral.h"

#include "src_Cards/abstractcard.h"
#include "src_Cards/cardaction.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"
#include "src_Models/modellistenergies.h"

#include "common/database.h"
#include "utils.h"

TestsUnitaireGeneral::TestsUnitaireGeneral() :
    TestsUnitaires()
{
    qDebug() << "*********************************************";
    qDebug() << "*** Démarrage des tests unitaire generaux ***";
    qDebug() << "*********************************************";

    checkStructCardPokemonByCreatingACustomOne();
    checkStructCardPokemonByCreatingASpecificOne();
    checkStructCardEnergyByCreatingACustomOne();
    checkStructCardEnergyByCreatingASpecificOne();
    checkModelListEnergiesCountEnergies();
    checkModelListEnergiesHasEnoughEnergies();
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
void TestsUnitaireGeneral::checkStructCardPokemonByCreatingACustomOne()
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
    const unsigned short attack1CostEnergiesQuantity = 3;
    const unsigned short costRetreat = 2;

    //Création
    QMap<AbstractCard::Enum_element, unsigned short> costEnergies;
    costEnergies.insert(attack1CostEnergiesElement, attack1CostEnergiesQuantity);

    QList<AttackData> listAttacks;
    AttackData attack1;
    attack1.name = attack1Name;
    attack1.description = attack1Description;
    attack1.damage = attack1Damage;
    attack1.costEnergies = costEnergies;
    listAttacks.append(attack1);

    CardPokemon* customPokemon = new CardPokemon(pokemonId,
                                                 pokemonName,
                                                 pokemonElement,
                                                 pokemonLife,
                                                 listAttacks,
                                                 CardPokemon::Element_None,
                                                 CardPokemon::WeaknessResistance_NoCoef,
                                                 CardPokemon::Element_None,
                                                 CardPokemon::WeaknessResistance_NoCoef,
                                                 -1,
                                                 costRetreat);

    //Tests
    COMPARE(customPokemon->id(), pokemonId);
    COMPARE(customPokemon->name(), pokemonName);
    COMPARE(customPokemon->type(), AbstractCard::TypeOfCard_Pokemon);
    COMPARE(customPokemon->element(), pokemonElement);
    COMPARE(customPokemon->lifeTotal(), pokemonLife);
    COMPARE(customPokemon->lifeLeft(), pokemonLife);
    COMPARE(customPokemon->status(), CardPokemon::Status_Normal);
    COMPARE(customPokemon->isBase(), true);
    COMPARE(customPokemon->costRetreat(), costRetreat);

    QList<AttackData> listAttacksFromCard = customPokemon->listAttacks();
    COMPARE(listAttacksFromCard.count(), 1);
    COMPARE(listAttacksFromCard[0].name, attack1Name);
    COMPARE(listAttacksFromCard[0].description, attack1Description);
    COMPARE(listAttacksFromCard[0].damage, attack1Damage);
    Q_ASSERT(listAttacksFromCard[0].costEnergies == costEnergies);

    qDebug() << __PRETTY_FUNCTION__ << "OK";

    //Nettoyage
    if(customPokemon != NULL)
    {
        delete customPokemon;
        customPokemon = NULL;
    }
}

void TestsUnitaireGeneral::checkStructCardPokemonByCreatingASpecificOne()
{
    //Informations
    const unsigned short pokemonId = 10;
    const QString pokemonName = "Chenipan";
    const AbstractCard::Enum_element pokemonElement = AbstractCard::Element_Grass;
    const unsigned short pokemonLife = 40;
    const QString attack1Name = "Sécrétion";
    const QString attack1Description = "Lancez une pièce. Si c'est face, le Pokémon Défenseur est maintenant Paralysé.";
    const unsigned short attack1Damage = 10;
    const AbstractCard::Enum_element attack1CostEnergiesElement = AbstractCard::Element_Grass;
    const unsigned short attack1CostEnergiesQuantity = 1;
    const unsigned short costRetreat = 1;

    //Création
    Database db;
    QMap<AbstractCard::Enum_element, unsigned short> costEnergies;
    costEnergies.insert(attack1CostEnergiesElement, attack1CostEnergiesQuantity);

    AbstractCard* customCard = db.cardById(pokemonId);
    CardPokemon* customPokemon = NULL;
    if (customCard != NULL)
    {
        customPokemon = static_cast<CardPokemon*>(customCard);

        if(customPokemon != NULL)
        {
            //Tests
            COMPARE(customPokemon->id(), pokemonId);
            COMPARE(customPokemon->name(), pokemonName);
            COMPARE(customPokemon->type(), AbstractCard::TypeOfCard_Pokemon);
            COMPARE(customPokemon->element(), pokemonElement);
            COMPARE(customPokemon->lifeTotal(), pokemonLife);
            COMPARE(customPokemon->lifeLeft(), pokemonLife);
            COMPARE(customPokemon->status(), CardPokemon::Status_Normal);
            COMPARE(customPokemon->isBase(), true);
            COMPARE(customPokemon->costRetreat(), costRetreat);

            QList<AttackData> listAttacksFromCard = customPokemon->listAttacks();
            COMPARE(listAttacksFromCard.count(), 1);
            COMPARE(listAttacksFromCard[0].name, attack1Name);
            COMPARE(listAttacksFromCard[0].description, attack1Description);
            COMPARE(listAttacksFromCard[0].damage, attack1Damage);
            Q_ASSERT(listAttacksFromCard[0].costEnergies == costEnergies);

            qDebug() << __PRETTY_FUNCTION__ << "OK";

            //Nettoyage
            if(customPokemon != NULL)
            {
                delete customPokemon;
                customPokemon = NULL;
            }
        }
        else
            Q_ASSERT(false);
    }
    else
        Q_ASSERT(false);
}

void TestsUnitaireGeneral::checkStructCardEnergyByCreatingACustomOne()
{
    //Informations
    const unsigned short energyId = 1001;
    const QString energyName = "energy Test";
    const AbstractCard::Enum_element energyElement = AbstractCard::Element_Water;
    const unsigned short energyQuantity = 3;

    //Création
    CardEnergy* customEnergy = new CardEnergy(energyId,
                                              energyName,
                                              energyElement,
                                              energyQuantity);

    //Tests
    COMPARE(customEnergy->id(), energyId);
    COMPARE(customEnergy->name(), energyName);
    COMPARE(customEnergy->type(), AbstractCard::TypeOfCard_Energy);
    COMPARE(customEnergy->element(), energyElement);
    COMPARE(customEnergy->quantity(), energyQuantity);

    qDebug() << __PRETTY_FUNCTION__ << "OK";

    //Nettoyage
    if(customEnergy != NULL)
    {
        delete customEnergy;
        customEnergy = NULL;
    }
}

void TestsUnitaireGeneral::checkStructCardEnergyByCreatingASpecificOne()
{
    //Informations
    const unsigned short energyId = 1003;
    const QString energyName = "Electric";
    const AbstractCard::Enum_element energyElement = AbstractCard::Element_Electric;
    const unsigned short energyQuantity = 1;

    //Création
    Database db;
    AbstractCard* customCard = db.cardById(energyId);
    CardEnergy* customEnergy = NULL;
    if (customCard != NULL)
    {
        customEnergy = static_cast<CardEnergy*>(customCard);

        if(customEnergy != NULL)
        {
            //Tests
            COMPARE(customEnergy->id(), energyId);
            COMPARE(customEnergy->name(), energyName);
            COMPARE(customEnergy->type(), AbstractCard::TypeOfCard_Energy);
            COMPARE(customEnergy->element(), energyElement);
            COMPARE(customEnergy->quantity(), energyQuantity);

            qDebug() << __PRETTY_FUNCTION__ << "OK";

            //Nettoyage
            if(customEnergy != NULL)
            {
                delete customEnergy;
                customEnergy = NULL;
            }
        }
        else
            Q_ASSERT(false);
    }
    else
        Q_ASSERT(false);


}

void TestsUnitaireGeneral::checkModelListEnergiesCountEnergies()
{
    //Informations
    QVector<int> listEnergiesId { 1003, 1005, 1010, 1014, 1014 };

    //Création
    ModelListEnergies* model = new ModelListEnergies();
    Database db;

    foreach(int energyId, listEnergiesId)
    {
        AbstractCard* customCard = db.cardById(energyId);
        CardEnergy* customEnergy = NULL;
        if (customCard != NULL)
        {
            customEnergy = static_cast<CardEnergy*>(customCard);

            if(customEnergy != NULL)
            {
                model->addEnergy(customEnergy);
            }
        }
    }

    //Tests
    COMPARE(model->countEnergies(), 6);
    COMPARE(model->countEnergies(AbstractCard::Element_Fire), 1);
    COMPARE(model->countEnergies(AbstractCard::Element_Electric), 1);
    COMPARE(model->countEnergies(AbstractCard::Element_Normal), 2);
    COMPARE(model->countEnergies(AbstractCard::Element_Water), 2);

    //Nettoyage
    delete model;

    qDebug() << __PRETTY_FUNCTION__ << "OK";
}

void TestsUnitaireGeneral::checkModelListEnergiesHasEnoughEnergies()
{
    //Informations
    QVector<int> listEnergiesId { 1005, 1005, 1010, 1012, 1014, 1014 };
    QMap<AbstractCard::Enum_element, unsigned short> mapCostEnergies;
    mapCostEnergies[AbstractCard::Element_Fire] = 1;
    mapCostEnergies[AbstractCard::Element_Normal] = 4;
    mapCostEnergies[AbstractCard::Element_Water] = 2;

    //Création
    ModelListEnergies* model = new ModelListEnergies();
    Database db;

    foreach(int energyId, listEnergiesId)
    {
        AbstractCard* customCard = db.cardById(energyId);
        CardEnergy* customEnergy = NULL;
        if (customCard != NULL)
        {
            customEnergy = static_cast<CardEnergy*>(customCard);

            if(customEnergy != NULL)
            {
                model->addEnergy(customEnergy);
            }
        }
    }

    //Tests
    COMPARE(model->hasEnoughEnergies(mapCostEnergies), true);

    qDebug() << __PRETTY_FUNCTION__ << "OK";

    //Nettoyage
    delete model;
}

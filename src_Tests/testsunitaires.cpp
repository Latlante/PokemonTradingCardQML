#include "testsunitaires.h"

#include <QDebug>

#include "src_Cards/abstractcard.h"
#include "src_Cards/cardaction.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"

#include "common/database.h"
#include "utils.h"

TestsUnitaires::TestsUnitaires(QObject *parent) : QObject(parent)
{
    qDebug() << "************************************";
    qDebug() << "*** Démarrage des tests unitaire ***";
    qDebug() << "************************************";

    checkStructCardPokemonByCreatingACustomOne();
    checkStructCardPokemonByCreatingASpecificOne();
    checkStructCardEnergyByCreatingACustomOne();
    checkStructCardEnergyByCreatingASpecificOne();
}

/*template<typename T>
void TestsUnitaires::COMPARE(T arg1, T arg2)
{
    if(arg1 != arg2)
        throw "FAILED" <<
}*/

void TestsUnitaires::checkStructCardPokemonByCreatingACustomOne()
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
                                                 listAttacks);

    //Tests
    COMPARE(customPokemon->id(), pokemonId);
    COMPARE(customPokemon->name(), pokemonName);
    COMPARE(customPokemon->type(), AbstractCard::TypeOfCard_Pokemon);
    COMPARE(customPokemon->element(), pokemonElement);
    COMPARE(customPokemon->lifeTotal(), pokemonLife);
    COMPARE(customPokemon->lifeLeft(), pokemonLife);
    COMPARE(customPokemon->status(), CardPokemon::Status_Normal);
    COMPARE(customPokemon->isBase(), true);

    QList<AttackData> listAttacksFromCard = customPokemon->listAttacks();
    COMPARE(listAttacksFromCard.count(), 1);
    COMPARE(listAttacksFromCard[0].name, attack1Name);
    COMPARE(listAttacksFromCard[0].description, attack1Description);
    COMPARE(listAttacksFromCard[0].damage, attack1Damage);
    Q_ASSERT(listAttacksFromCard[0].costEnergies == costEnergies);

    qDebug() << __PRETTY_FUNCTION__ << "OK";
}

void TestsUnitaires::checkStructCardPokemonByCreatingASpecificOne()
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

            QList<AttackData> listAttacksFromCard = customPokemon->listAttacks();
            COMPARE(listAttacksFromCard.count(), 1);
            COMPARE(listAttacksFromCard[0].name, attack1Name);
            COMPARE(listAttacksFromCard[0].description, attack1Description);
            COMPARE(listAttacksFromCard[0].damage, attack1Damage);
            Q_ASSERT(listAttacksFromCard[0].costEnergies == costEnergies);

            qDebug() << __PRETTY_FUNCTION__ << "OK";
        }
        else
            Q_ASSERT(false);
    }
    else
        Q_ASSERT(false);
}

void TestsUnitaires::checkStructCardEnergyByCreatingACustomOne()
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
}

void TestsUnitaires::checkStructCardEnergyByCreatingASpecificOne()
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
        }
        else
            Q_ASSERT(false);
    }
    else
        Q_ASSERT(false);
}

const char *TestsUnitaires::messageToDisplayInConsole(const char *nameVar, QVariant arg1, QVariant arg2)
{
    QString message = "ERROR: " + QString::fromUtf8(nameVar) + " => \"";

    switch(arg1.type())
    {
    case QVariant::Bool:
        message += (arg1.toBool() == true) ? "true" : "false";
        break;
    case QVariant::Int:
        message += QString::number(arg1.toInt());
        break;
    case QVariant::UInt:
        message += QString::number(arg1.toUInt());
        break;
    case QVariant::String:
        message += arg1.toString();
        break;
    default:
        qCritical() << "Type arg1 inconnue:" << arg1.type();
    }

    message += "\" - \"";

    switch(arg2.type())
    {
    case QVariant::Bool:
        message += (arg2.toBool() == true) ? "true" : "false";
        break;
    case QVariant::Int:
        message += QString::number(arg2.toInt());
        break;
    case QVariant::UInt:
        message += QString::number(arg2.toUInt());
        break;
    case QVariant::String:
        message += arg2.toString();
        break;
    default:
        qCritical() << "Type arg2 inconnue:" << arg2.type();
    }

    message += "\"";

    QByteArray messageArray = message.toUtf8();
    const char* messageChar = messageArray.constData();
    //char* test = messageArray.data();

    qCritical() << message;

    return "e";
}

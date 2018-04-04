#include "database.h"

#include <QFile>
#include <QVariant>
#include "src_Actions/actioncreationfactory.h"

const QString Database::m_PATH_DB_ENERGIES = "rcc/energies.db";
const QString Database::m_PATH_DB_POKEMON = "rcc/pokemon.db";

Database::Database(QObject *parent) : QObject(parent)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
QList<int> Database::listIdAllCardsPokemon()
{
    QList<int> listId;

    QFile fichier(m_PATH_DB_POKEMON);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray textFromFile = fichier.readAll();
    QString contenuGeneral = QString::fromLatin1(textFromFile);
    QStringList textSplitted = contenuGeneral.split("\n");

    foreach(QString line, textSplitted)
    {
        if(line.section(";", InfoDbPok_Useable, InfoDbPok_Useable) == "1")
        {
            listId.append(line.section(";", InfoDbPok_Id, InfoDbPok_Id).toInt());
        }
    }

    return listId;
}

QList<int> Database::listIdAllCardsEnergies()
{
    QList<int> listId;

    QFile fichier(m_PATH_DB_ENERGIES);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray textFromFile = fichier.readAll();
    QString contenuGeneral = QString::fromLatin1(textFromFile);
    QStringList textSplitted = contenuGeneral.split("\n");

    foreach(QString line, textSplitted)
    {
        listId.append(line.section(";", InfoDbNrj_Id, InfoDbNrj_Id).toInt());
    }

    return listId;
}

AbstractCard* Database::cardById(int id)
{
    AbstractCard* cardToReturn = NULL;
    QFile fichier("database/db.csv");
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray textFromFile = fichier.readAll();
    QString contenuGeneral = QString::fromLatin1(textFromFile);
    QStringList contenuParLigne = contenuGeneral.split("\n");

    int indexLine = -1;
    for(int i=0;i<contenuParLigne.count();++i)
    //foreach(QString ligne, contenuParLigne)
    {
        int idCard = contenuParLigne[i].section(";", 0, 0).toInt();

        if (idCard == id)
        {
            indexLine = i;
            break;
        }
    }


    if ((id >= INDEX_START_POKEMON) && (id < INDEX_START_ENERGIES))
    {
        cardToReturn = newCardPokemon(contenuParLigne[indexLine]);
    }
    else if ((id >= INDEX_START_ENERGIES) && (id < INDEX_START_ACTION))
    {
        cardToReturn = newCardEnergy(contenuParLigne[indexLine]);
    }

    return cardToReturn;
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
CardPokemon* Database::newCardPokemon(const QString& infoCsv)
{
    CardPokemon* cardPokemonToReturn = NULL;
    QStringList arguments = infoCsv.split(";");

    if(arguments[InfoDbPok_Useable] == "1")
    {
        QList<AttackData> listAttacks;
        int offset = InfoDbPok_Att1;
        for(int i=0;i<3;++i)
        {
            if(arguments[offset+InfoAtt_Name] != "")
            {
                AttackData attack;
                attack.name = arguments[offset+InfoAtt_Name];
                attack.description = arguments[offset+InfoAtt_Description];
                attack.damage = arguments[offset+InfoAtt_Damage].toInt();

                QMap<AbstractCard::Enum_element, unsigned short> listEnergies;
                for(int indexEnergies=0;indexEnergies<AbstractCard::Element_COUNT;++indexEnergies)
                {
                    int indexEnergy = static_cast<int>(InfoAtt_FirstEnergies)+indexEnergies;
                    QString cellContains = arguments[offset+indexEnergy];

                    if (cellContains != "")
                    {
                        listEnergies.insert(static_cast<AbstractCard::Enum_element>(indexEnergies), cellContains.toUShort());
                    }
                }

                attack.costEnergies = listEnergies;
                bool ok;
                int idAction = arguments[offset+InfoAtt_ActionType].toInt(&ok);
                attack.action = ActionCreationFactory::createAction(static_cast<AbstractAction::Enum_typeOfAction>(idAction), QVariant::fromValue(arguments[offset+InfoAtt_ActionArgument]));
                listAttacks.append(attack);
            }
            offset += InfoAtt_COUNT;
        }

        cardPokemonToReturn = new CardPokemon(arguments[InfoDbPok_Id].toInt(),
                                            arguments[InfoDbPok_Name],
                                            static_cast<AbstractCard::Enum_element>(arguments[InfoDbPok_Element].toInt()),
                                            arguments[InfoDbPok_Life].toUShort(),
                                            listAttacks,
                                            arguments[InfoDbPok_IdSubevolution] == "" ? -1 : arguments[InfoDbPok_IdSubevolution].toShort());
    }

    return cardPokemonToReturn;
}

CardEnergy* Database::newCardEnergy(const QString &infoCsv)
{
    QStringList arguments = infoCsv.split(";");

    return new CardEnergy(arguments[InfoDbNrj_Id].toInt(),
                          arguments[InfoDbNrj_Name],
                          static_cast<AbstractCard::Enum_element>(arguments[InfoDbNrj_Id].toInt()-INDEX_START_ENERGIES),
                          arguments[InfoDbNrj_Quantity].toUShort());
}

/*CardTrainer* Database::newCardTrainer(const QString &infoCsv)
{
    CardTrainer* cardTrainerToReturn = NULL;
    QStringList arguments = infoCsv.split(";");

    if(arguments[InfoDbTrainer_Useable] == "1")
    {
        int idAction = arguments[InfoDbTrainer_Type].toInt(&ok);

        cardTrainerToReturn = new CardTrainer(arguments[InfoDbTrainer_Id].toInt(),
                                              arguments[InfoDbTrainer_Name],
                                              arguments[InfoDbTrainer_Description],
                                              ActionCreationFactory::createAction(static_cast<AbstractAction::Enum_typeOfAction>(idAction), QVariant::fromValue(arguments[InfoDbTrainer_Argument]));
    }

    return cardTrainerToReturn;
}*/

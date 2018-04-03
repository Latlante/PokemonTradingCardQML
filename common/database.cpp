#include "database.h"

#include <QFile>
#include <QVariant>
#include "src_Actions/actioncreationfactory.h"

Database::Database(QObject *parent) : QObject(parent)
{

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

CardPokemon* Database::newCardPokemon(const QString& infoCsv)
{
    QStringList arguments = infoCsv.split(";");

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
                QString contenuCell = arguments[offset+indexEnergy];

                if (contenuCell != "")
                {
                    listEnergies.insert(static_cast<AbstractCard::Enum_element>(indexEnergies), contenuCell.toUShort());
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

    return new CardPokemon( arguments[InfoDbPok_Id].toInt(),
                            arguments[InfoDbPok_Name],
                            static_cast<AbstractCard::Enum_element>(arguments[InfoDbPok_Element].toInt()),
                            arguments[InfoDbPok_Life].toUShort(),
                            listAttacks,
                            arguments[InfoDbPok_IdSubevolution] == "" ? -1 : arguments[InfoDbPok_IdSubevolution].toShort());
}

CardEnergy* Database::newCardEnergy(const QString &infoCsv)
{
    QStringList arguments = infoCsv.split(";");

    return new CardEnergy(arguments[InfoDbNrj_Id].toInt(),
                          arguments[InfoDbNrj_Name],
                          static_cast<AbstractCard::Enum_element>(arguments[InfoDbNrj_Id].toInt()-INDEX_START_ENERGIES),
                          arguments[InfoDbNrj_Quantity].toUShort());
}

#include "dlgselectcards.h"
#include "ui_dlgselectcards.h"

#include "src_Cards/abstractcard.h"
#include "utils.h"
#include "common/database.h"

DlgSelectCards::DlgSelectCards(const QString &name, QObject *parent) :
    QObject(parent),
    m_name(name)
{

}

DlgSelectCards::~DlgSelectCards()
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
QList<AbstractCard*> DlgSelectCards::listOfSelectedCards()
{
    return QList<AbstractCard*>();
}

QList<AbstractCard*> DlgSelectCards::listOfRandomCards()
{
    QList<AbstractCard*> listCards;
    Database db;

    for(int i=0;i<6;++i)
    {
        int idPokemon = Utils::selectRandomCardsPokemon();
        listCards.append(db.cardById(idPokemon));
    }

    listCards.append((db.cardById(1008)));

    for(int i=0;i<6;++i)
    {
        int idEnergy = Utils::selectRandomCardsEnergy();
        listCards.append(db.cardById(idEnergy));
    }

    for(int i=0;i<20;++i)
    {
        int idPokemon = Utils::selectRandomCardsPokemon();
        listCards.append(db.cardById(idPokemon));
    }

    for(int i=0;i<20;++i)
    {
        int idEnergy = Utils::selectRandomCardsEnergy();
        listCards.append(db.cardById(idEnergy));
    }

    return listCards;
}

#include "modelselectingcards.h"
#include <QDebug>
#include <QtQml/qqml.h>
#include "common/database.h"
#include "src_Cards/abstractcard.h"
#include "src_Cards/cardaction.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"

ModelSelectingCards::ModelSelectingCards(QObject *parent) :
    QAbstractListModel(parent),
    m_listCardsSelected(QList<InfoCard>())
{
    initListCards();
}

ModelSelectingCards::~ModelSelectingCards()
{
    cleanListCards();
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void ModelSelectingCards::declareQML()
{
    qmlRegisterUncreatableType<ModelSelectingCards>("model", 1, 0, "ModelSelectingCards", "ModelSelectingCards error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
QList<InfoCard> ModelSelectingCards::listCardsSelected()
{
    return m_listCardsSelected;
}

void ModelSelectingCards::changeQuantityCard(int id, int quantity)
{
    InfoCard info = m_listCardsSelected[id];

    if(info.quantity != quantity)
    {
        info.quantity = quantity;
        m_listCardsSelected.replace(id, info);

        emit dataChanged(index(id, 0), index(id, 0));
    }
}

QVariant ModelSelectingCards::data(const QModelIndex &index, int role) const
{
    qDebug() << __PRETTY_FUNCTION__ << index << role;
    int iRow = index.row();
    if ((iRow < 0) || (iRow >= rowCount()))
    {
        qCritical() << __PRETTY_FUNCTION__ << "bad row num : " << iRow;
        return QVariant();
    }

    switch(role)
    {
    case SelCards_Name:         return m_listCardsSelected[iRow].card->name();
    case SelCards_ImageCard:    return m_listCardsSelected[iRow].card->image();
    case SelCards_Quantity:     return m_listCardsSelected[iRow].quantity;
    }

    return QVariant();
}

int ModelSelectingCards::rowCount(const QModelIndex &) const
{
    return m_listCardsSelected.count();
}

int ModelSelectingCards::rowCountById(int id) const
{
    return m_listCardsSelected[id].quantity;
}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
QHash<int, QByteArray> ModelSelectingCards::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SelCards_Name] = "name";
    roles[SelCards_ImageCard] = "imageCard";
    roles[SelCards_Quantity] = "quantity";

    return roles;
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
void ModelSelectingCards::initListCards()
{
    cleanListCards();

    Database db;

    //Pokemon
    QList<int> listId = db.listIdAllCardsPokemon();
    listId += db.listIdAllCardsEnergies();

    foreach(int id, listId)
    {
        AbstractCard* card = db.cardById(id);
        InfoCard info;
        info.card = card;
        info.quantity = 0;

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_listCardsSelected.append(info);
        endInsertRows();
    }
}

void ModelSelectingCards::cleanListCards()
{
    while(m_listCardsSelected.count() > 0)
    {
        beginRemoveRows(QModelIndex(), rowCount()-1, rowCount());
        InfoCard info = m_listCardsSelected.takeFirst();
        delete info.card;
        endRemoveRows();
    }
}

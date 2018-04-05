#include "modelselectingcards.h"
#include <QDebug>
#include <QtQml/qqml.h>
#include "common/database.h"
#include "src_Cards/abstractcard.h"
#include "src_Cards/cardaction.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"
#include "src_Packets/packetdeck.h"
#include "utils.h"

ModelSelectingCards::ModelSelectingCards(QObject *parent) :
    QAbstractListModel(parent),
    m_listCardsSelected(QList<InfoCard>()),
    m_lastPlayer(false)
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
int ModelSelectingCards::maxCards()
{
    return MAXCARDS_DECK;
}

QList<InfoCard> ModelSelectingCards::listCardsSelected()
{
    return m_listCardsSelected;
}

QString ModelSelectingCards::name()
{
    return m_name;
}

void ModelSelectingCards::setName(const QString &name)
{
    if(m_name != name)
    {
        m_name = name;
        emit nameChanged();
    }
}

bool ModelSelectingCards::isLastPlayer()
{
    return m_lastPlayer;
}

void ModelSelectingCards::setLastPlayer(bool lastPlayer)
{
    if(m_lastPlayer != lastPlayer)
    {
        m_lastPlayer = lastPlayer;
        emit lastPlayerChanged();
    }
}

void ModelSelectingCards::changeQuantityCard(int id, int quantity)
{
    if((id >= 0) && (id < m_listCardsSelected.count()))
    {
        InfoCard info = m_listCardsSelected[id];
        int delta = info.quantity - quantity;

        if((info.quantity != quantity) &&
            (quantity >= 0) &&
            (canAcceptXNewCards(delta) == true))
        {
            info.quantity = quantity;
            m_listCardsSelected.replace(id, info);

            emit dataChanged(index(id, 0), index(id, 0));
        }
    }
}

QVariant ModelSelectingCards::data(const QModelIndex &index, int role) const
{
    //qDebug() << __PRETTY_FUNCTION__ << index << role;
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

void ModelSelectingCards::clear()
{
    cleanListCards();
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

    qDebug() << __PRETTY_FUNCTION__ << "listCards:" << listId;

    foreach(int id, listId)
    {
        AbstractCard* card = db.cardById(id);

        if(card != NULL)
        {
            InfoCard info;
            info.card = card;
            info.quantity = 0;

            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            m_listCardsSelected.append(info);
            endInsertRows();
        }
    }
}

void ModelSelectingCards::cleanListCards()
{
    while(m_listCardsSelected.count() > 0)
    {
        beginRemoveRows(QModelIndex(), rowCount()-1, rowCount());
        InfoCard info = m_listCardsSelected.takeFirst();
        delete info.card;
        info.card = nullptr;
        endRemoveRows();
    }
}

int ModelSelectingCards::countTotalQuantity()
{
    int count = 0;

    foreach(InfoCard info, m_listCardsSelected)
        count += info.quantity;

    return count;
}

bool ModelSelectingCards::canAcceptXNewCards(int quantity)
{
    return (countTotalQuantity() + quantity) <= maxCards();
}

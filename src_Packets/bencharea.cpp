#include "bencharea.h"

#include <QDebug>
#include <QPixmap>
#include "src_Cards/cardpokemon.h"

BenchArea::BenchArea(QList<AbstractCard*> listCards) :
	AbstractPacket(listCards)
{
	
}

BenchArea::~BenchArea()
{
	
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void BenchArea::declareQML()
{
    qmlRegisterUncreatableType<BenchArea>("model", 1, 0, "BenchArea", "BenchArea error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
int BenchArea::maxCards()
{
    return MAXCARDS_BENCH;
}

bool BenchArea::addNewCard(AbstractCard* newCard)
{
    bool statusBack = false;

    if ((NULL != newCard) && (!isFull()))
    {
        m_listCards.append(newCard);

        connect(newCard, &AbstractCard::dataChanged, this, &AbstractPacket::updateAllData);

        emit dataChanged(index(AbstractPacket::rowCount()-1, 0), index(AbstractPacket::rowCount()-1, 0));
        emit countChanged();
        statusBack = true;
    }

    return statusBack;
}

AbstractCard* BenchArea::takeACard(int index)
{
    AbstractCard* card = NULL;

    if ((index >= 0) && (index < countCard()))
    {
        card = m_listCards.takeAt(index);

        emit dataChanged(index(AbstractPacket::rowCount()-1, 0), index(AbstractPacket::rowCount(), 0));
        emit countChanged();
    }

    return card;
}

QVariant BenchArea::data(const QModelIndex& index, int role) const
{
    //qDebug() << __PRETTY_FUNCTION__ << index << role;

    int iRow = index.row();
    if ((iRow < 0) || (iRow >= rowCount()))
    {
        qCritical() << __PRETTY_FUNCTION__ << "bad row num : " << iRow;
        return QVariant();
    }

    //Dans la liste
    if(iRow < AbstractPacket::rowCount())
    {
        switch(role)
        {
        case BenchRole_Card:        return m_listCards[iRow];
        case BenchRole_Name:        return m_listCards[iRow]->name();
        case BenchRole_ImageCard:   return m_listCards[iRow]->image();
        }
    }
    //Au delà
    else
    {
        switch(role)
        {
        case BenchRole_Card:        return nullptr;
        case BenchRole_Name:        return "";
        case BenchRole_ImageCard:   return AbstractCard::imageByDefault();
        }
    }

    return QVariant::Invalid;
}

int BenchArea::rowCount(const QModelIndex &) const
{
    return maxCards();
}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
QHash<int, QByteArray> BenchArea::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[BenchRole_Card] = "card";
    roles[BenchRole_Name] = "name";
    roles[BenchRole_ImageCard] = "imageCard";

    return roles;
}

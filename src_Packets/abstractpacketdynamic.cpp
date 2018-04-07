#include "abstractpacketdynamic.h"

#include "src_Cards/abstractcard.h"

AbstractPacketDynamic::AbstractPacketDynamic(QList<AbstractCard *> listCards) :
    AbstractPacket(listCards)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
int AbstractPacketDynamic::countCard() const
{
    return rowCount();
}

bool AbstractPacketDynamic::addNewCard(AbstractCard* newCard)
{
    //qDebug() << __PRETTY_FUNCTION__;
    bool statusBack = false;

    if ((NULL != newCard) && (!isFull()))
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_listCards.append(newCard);
        endInsertRows();

        connect(newCard, &AbstractCard::dataChanged, this, &AbstractPacketDynamic::updateAllData);

        //qDebug() << __PRETTY_FUNCTION__ << "Carte ajoutée";

        emit countChanged();
        statusBack = true;
    }

    return statusBack;
}

AbstractCard* AbstractPacketDynamic::takeACard(int indexCard)
{
    AbstractCard* card = NULL;

    if ((indexCard >= 0) && (indexCard < countCard()))
    {
        beginRemoveRows(QModelIndex(), indexCard, indexCard);
        card = m_listCards.takeAt(indexCard);
        endRemoveRows();

        emit countChanged();
    }

    return card;
}

bool AbstractPacketDynamic::removeFromPacket(AbstractCard *card)
{
    bool removeSuccess = false;

    int indexCard = m_listCards.indexOf(card);
    if(indexCard != -1)
    {
        beginRemoveRows(QModelIndex(), indexCard, indexCard);
        removeSuccess = m_listCards.removeOne(card);
        endRemoveRows();

        delete card;

        emit countChanged();
    }

    return removeSuccess;
}

int AbstractPacketDynamic::rowCount(const QModelIndex&) const
{
    return m_listCards.count();
}

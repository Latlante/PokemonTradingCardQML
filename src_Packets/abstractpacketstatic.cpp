#include "abstractpacketstatic.h"
#include "src_Cards/abstractcard.h"

AbstractPacketStatic::AbstractPacketStatic(QList<AbstractCard *> listCards) :
    AbstractPacket(listCards)
{

}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
int AbstractPacketStatic::countCard() const
{
    return m_listCards.count();
}

bool AbstractPacketStatic::addNewCard(AbstractCard* newCard)
{
    bool statusBack = false;

    if ((NULL != newCard) && (!isFull()))
    {
        m_listCards.append(newCard);

        connect(newCard, &AbstractCard::dataChanged, this, &AbstractPacketStatic::updateAllData);

        emit dataChanged(index(countCard()-1, 0), index(countCard()-1, 0));
        emit countChanged();
        statusBack = true;
    }

    return statusBack;
}

AbstractCard* AbstractPacketStatic::takeACard(int indexCard)
{
    AbstractCard* card = NULL;

    if ((indexCard >= 0) && (indexCard < countCard()))
    {
        card = m_listCards.takeAt(indexCard);

        emit dataChanged(index(countCard()-1, 0), index(countCard(), 0));
        emit countChanged();
    }

    return card;
}

bool AbstractPacketStatic::removeFromPacket(AbstractCard *card)
{
    bool removeSuccess = false;

    int indexCard = m_listCards.indexOf(card);
    if(indexCard != -1)
    {
        removeSuccess = m_listCards.removeOne(card);

        delete card;

        emit dataChanged(index(countCard()-1, 0), index(countCard(), 0));
        emit countChanged();
    }

    return removeSuccess;
}

int AbstractPacketStatic::rowCount(const QModelIndex&) const
{
    return maxCards();
}

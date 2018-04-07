#include "packethand.h"
#include <QDebug>

#include "src_Cards/abstractcard.h"

PacketHand::PacketHand(QList<AbstractCard*> listCards) :
    AbstractPacketDynamic(listCards)
{
	
}

PacketHand::~PacketHand()
{
	
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void PacketHand::declareQML()
{
    qmlRegisterUncreatableType<PacketHand>("model", 1, 0, "PacketHand", "PacketHand error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
int PacketHand::maxCards() const
{
    return MAXCARDS_HAND;
}

QVariant PacketHand::data(const QModelIndex &index, int role) const
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
    case HandRole_Card:         return QVariant::fromValue<AbstractCard*>(m_listCards[iRow]);
    case HandRole_Name:         return m_listCards[iRow]->name();
    case HandRole_ImageCard:    return m_listCards[iRow]->image();
    }

    return QVariant();
}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
QHash<int, QByteArray> PacketHand::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[HandRole_Card] = "card";
    roles[HandRole_Name] = "name";
    roles[HandRole_ImageCard] = "imageCard";

    return roles;
}

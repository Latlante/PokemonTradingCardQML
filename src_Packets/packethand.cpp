#include "packethand.h"
#include <QDebug>

#include "src_Cards/abstractcard.h"

PacketHand::PacketHand()
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
int PacketHand::maxCards()
{
    return -1;
}

QVariant PacketHand::data(const QModelIndex &index, int role) const
{
    int iRow = index.row();
    if ((iRow < 0) || (iRow >= rowCount()))
    {
        qCritical() << __PRETTY_FUNCTION__ << "bad row num : " << iRow;
        return QVariant();
    }

    switch(role)
    {
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
    roles[HandRole_Name] = "name";
    roles[HandRole_ImageCard] = "imageCard";

    return roles;
}

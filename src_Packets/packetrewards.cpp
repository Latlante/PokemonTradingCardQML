#include "packetrewards.h"

PacketRewards::PacketRewards(QList<AbstractCard*> listCards) :
	AbstractPacket(listCards)
{
	
}

PacketRewards::~PacketRewards()
{
	
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void PacketRewards::declareQML()
{
    qmlRegisterUncreatableType<PacketRewards>("model", 1, 0, "PacketRewards", "PacketRewards error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
int PacketRewards::maxCards()
{
    return MAXCARDS_REWARD;
}

QVariant PacketRewards::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

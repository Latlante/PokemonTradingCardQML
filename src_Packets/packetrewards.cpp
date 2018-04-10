#include "packetrewards.h"

PacketRewards::PacketRewards(QList<AbstractCard*> listCards) :
    AbstractPacketDynamic(listCards)
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
int PacketRewards::maxCards() const
{
    return MAXCARDS_REWARD;
}

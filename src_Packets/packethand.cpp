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


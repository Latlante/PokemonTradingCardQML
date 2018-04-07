#include "packettrash.h"

PacketTrash::PacketTrash(QList<AbstractCard*> listCards) :
    AbstractPacketDynamic(listCards)
{
	
}

PacketTrash::~PacketTrash()
{
	
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void PacketTrash::declareQML()
{
    qmlRegisterUncreatableType<PacketTrash>("model", 1, 0, "PacketTrash", "PacketTrash error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
int PacketTrash::maxCards() const
{
    return MAXCARDS_TRASH;
}

QVariant PacketTrash::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

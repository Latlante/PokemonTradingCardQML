#ifndef PACKETTRASH_H
#define PACKETTRASH_H

#include "abstractpacket.h"

class PacketTrash : public AbstractPacket
{
    Q_OBJECT

public:
    PacketTrash(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~PacketTrash();

    static void declareQML();
	
	int maxCards();

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:

};

#endif // PACKETTRASH_H

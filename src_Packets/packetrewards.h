#ifndef PACKETREWARDS_H
#define PACKETREWARDS_H

#include "abstractpacket.h"

class PacketRewards : public AbstractPacket
{
    Q_OBJECT

public:
    PacketRewards(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~PacketRewards();

    static void declareQML();
	
	int maxCards();

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:

};

#endif // PACKETREWARDS_H

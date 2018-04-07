#ifndef PACKETREWARDS_H
#define PACKETREWARDS_H

#include "abstractpacketdynamic.h"

class PacketRewards : public AbstractPacketDynamic
{
    Q_OBJECT

public:
    PacketRewards(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~PacketRewards();

    static void declareQML();
	
    int maxCards() const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:

};

#endif // PACKETREWARDS_H

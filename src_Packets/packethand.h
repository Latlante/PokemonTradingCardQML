#ifndef PACKETHAND_H
#define PACKETHAND_H

#include "abstractpacket.h"

class PacketHand : public AbstractPacket
{
    Q_OBJECT

public:
    enum Enum_HandRoleData
    {
        HandRole_Name = Qt::UserRole,
        HandRole_ImageCard
    };

    PacketHand();
    virtual ~PacketHand();

    static void declareQML();
	
	int maxCards();

    virtual QVariant data(const QModelIndex &index, int role) const override;

protected:
    QHash<int,QByteArray> roleNames() const override;

};

#endif // PACKETHAND_H

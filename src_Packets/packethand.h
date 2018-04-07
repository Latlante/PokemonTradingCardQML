#ifndef PACKETHAND_H
#define PACKETHAND_H

#include "abstractpacketdynamic.h"

class PacketHand : public AbstractPacketDynamic
{
    Q_OBJECT

public:
    enum Enum_HandRoleData
    {
        HandRole_Card = Qt::UserRole,
        HandRole_Name,
        HandRole_ImageCard
    };

    PacketHand(QList<AbstractCard *> listCards = QList<AbstractCard*>());
    virtual ~PacketHand();

    static void declareQML();
	
    int maxCards() const override;

    virtual QVariant data(const QModelIndex &index, int role) const override;

protected:
    QHash<int,QByteArray> roleNames() const override;

};

#endif // PACKETHAND_H

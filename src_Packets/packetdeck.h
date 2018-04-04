#ifndef PACKETDECK_H
#define PACKETDECK_H

#include "abstractpacket.h"

class AbsractCard;

class PacketDeck : public AbstractPacket
{
    Q_OBJECT

public:
    PacketDeck(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~PacketDeck();

    static void declareQML();
	
    static int maxCards();
	void mixCards();
    AbstractCard *drawCard();
    QList<AbstractCard *> drawCards(int count);

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // PACKETDECK_H

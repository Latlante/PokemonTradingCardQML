#ifndef ABSTRACTPACKETDYNAMIC_H
#define ABSTRACTPACKETDYNAMIC_H

#include "abstractpacket.h"

class AbstractCard;

class AbstractPacketDynamic : public AbstractPacket
{
    Q_OBJECT
public:
    explicit AbstractPacketDynamic(QList<AbstractCard*> listCards = QList<AbstractCard*>());

    //virtual int maxCards() const = 0;
    virtual int countCard() const override;
    virtual bool addNewCard(AbstractCard *newCard) override;
    virtual AbstractCard* takeACard(int indexCard) override;
    virtual bool removeFromPacket(AbstractCard* card) override;

    //virtual QVariant data(const QModelIndex &index, int role) const = 0;
    virtual int rowCount(const QModelIndex & = QModelIndex()) const override;

signals:

public slots:
};

#endif // ABSTRACTPACKETDYNAMIC_H

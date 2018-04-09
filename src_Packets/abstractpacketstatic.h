#ifndef ABSTRACTPACKETSTATIC_H
#define ABSTRACTPACKETSTATIC_H

#include "abstractpacket.h"

class AbstractCard;

class AbstractPacketStatic : public AbstractPacket
{
    Q_OBJECT
public:
    enum PacketStaticRole {
        PacStaticRole_Card = Qt::UserRole,
        PacStaticRole_IsCard,
        PacStaticRole_Name,
        PacStaticRole_ImageCard
    };

    explicit AbstractPacketStatic(QList<AbstractCard*> listCards = QList<AbstractCard*>());

    //virtual int maxCards() const = 0;
    virtual int countCard() const override;
    virtual bool addNewCard(AbstractCard *newCard) override;
    virtual AbstractCard* takeACard(int indexCard) override;
    virtual bool removeFromPacket(AbstractCard* card) override;

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual int rowCount(const QModelIndex & = QModelIndex()) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // ABSTRACTPACKETSTATIC_H

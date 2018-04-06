#ifndef BENCHAREA_H
#define BENCHAREA_H

#include "abstractpacket.h"

class BenchArea : public AbstractPacket
{
    Q_OBJECT

public:
    enum BenchRole {
        BenchRole_Card = Qt::UserRole,
        BenchRole_Name,
        BenchRole_ImageCard
    };
    BenchArea(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~BenchArea();

    static void declareQML();
	
    int maxCards();
    virtual bool addNewCard(AbstractCard* newCard) override;
    virtual AbstractCard* takeACard(int index) override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex & = QModelIndex()) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:

};

#endif // BENCHAREA_H

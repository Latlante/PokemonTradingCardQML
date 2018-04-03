#ifndef BENCHAREA_H
#define BENCHAREA_H

#include "abstractpacket.h"

class BenchArea : public AbstractPacket
{
    Q_OBJECT

public:
    enum BenchRole {
        BenchR_Image = Qt::UserRole + 1
    };
    BenchArea(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~BenchArea();

    static void declareQML();
	
	int maxCards();

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:

};

#endif // BENCHAREA_H

#ifndef ABSTRACTPACKET_H
#define ABSTRACTPACKET_H

#include <QAbstractListModel>
#include <QtQml/qqml.h>
#include "utils.h"

class AbstractCard;

class AbstractPacket : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int countCard READ countCard NOTIFY countChanged)

public:
	enum Enum_roleCard
	{
        Role_name = 0,
        Role_Attack1_Name,
        Role_Attack2_Name,
        Role_Attack3_Name,
	};

    AbstractPacket(QList<AbstractCard*> listCards = QList<AbstractCard*>());
    virtual ~AbstractPacket();
	
    static void declareQML();
	
    virtual int maxCards() const = 0;
    virtual int countCard() const = 0;
    virtual bool addNewCard(AbstractCard* newCard) = 0;
    virtual AbstractCard* takeACard(int indexCard) = 0;
    virtual bool removeFromPacket(AbstractCard* card) = 0;

    bool isFull();
    bool isEmpty();
    AbstractCard* card(int index);

    virtual QVariant data(const QModelIndex &index, int role) const = 0;
    virtual int rowCount(const QModelIndex& = QModelIndex()) const = 0;

signals:
    void countChanged();

	
protected:
	QList<AbstractCard*> m_listCards;

protected slots:
    void updateAllData();

};

#endif // ABSTRACTPACKET_H

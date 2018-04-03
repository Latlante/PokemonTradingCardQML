#ifndef ABSTRACTPACKET_H
#define ABSTRACTPACKET_H

#include <QAbstractListModel>
#include <QtQml/qqml.h>

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
	
    virtual int maxCards() = 0;
    int countCard() const;
    bool isFull();
    bool addNewCard(AbstractCard* newCard);
    AbstractCard* takeACard(int index);
    AbstractCard* card(int index);
    bool removeFromPacket(AbstractCard* card);
	
    //virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual int rowCount(const QModelIndex& = QModelIndex()) const override;

signals:
    void countChanged();

	
protected:
	QList<AbstractCard*> m_listCards;


    //QHash<int, QByteArray> roleNames() const override;

protected slots:
    void updateAllData();


	

};

#endif // ABSTRACTPACKET_H

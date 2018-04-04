#ifndef MODELSELECTINGCARDS_H
#define MODELSELECTINGCARDS_H

#include <QAbstractListModel>
#include <QVariant>

class AbstractCard;
class CardAction;
class CardEnergy;
class CardPokemon;

struct InfoCard
{
    AbstractCard* card;
    unsigned short quantity;
};

class ModelSelectingCards : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<InfoCard> listCardsSelected READ listCardsSelected NOTIFY listCardsSelectedChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

public:
    enum SelectingCardsRole
    {
        SelCards_Name = Qt::UserRole,
        SelCards_ImageCard,
        SelCards_Quantity
    };

    explicit ModelSelectingCards(QObject *parent = nullptr);
    ~ModelSelectingCards();

    static void declareQML();

    QList<InfoCard> listCardsSelected();
    QString name();
    void setName(const QString& name);

    void changeQuantityCard(int id, int quantity);

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual int rowCount(const QModelIndex & = QModelIndex()) const override;
    int rowCountById(int id) const;

signals:
    void listCardsSelectedChanged();
    void nameChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QString m_name;
    QList<InfoCard> m_listCardsSelected;
    //QHash<AbstractCard*, unsigned short> m_listCardsSelected;

    void initListCards();
    void cleanListCards();
    int countTotalQuantity();
    bool canAcceptXNewCards(int quantity);
};

#endif // MODELSELECTINGCARDS_H

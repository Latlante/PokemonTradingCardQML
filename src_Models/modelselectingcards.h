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

    void changeQuantityCard(int id, int quantity);

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual int rowCount(const QModelIndex & = QModelIndex()) const override;
    int rowCountById(int id) const;

signals:
    void listCardsSelectedChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<InfoCard> m_listCardsSelected;
    //QHash<AbstractCard*, unsigned short> m_listCardsSelected;

    void initListCards();
    void cleanListCards();
};

#endif // MODELSELECTINGCARDS_H

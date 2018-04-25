#ifndef MODELPOPUPSELECTCARDINPACKET_H
#define MODELPOPUPSELECTCARDINPACKET_H

#include <QAbstractListModel>

class AbstractCard;
class AbstractPacket;
class ModelListEnergies;

class ModelPopupSelectCardInPacket : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(unsigned short numberOfCardsSelected READ numberOfCardsSelected NOTIFY numberOfCardsSelectedChanged)
    Q_PROPERTY(bool isMaximumCardsSelected READ isMaximumCardsSelected NOTIFY numberOfCardsSelectedChanged)

public:
    struct SelectionCards
    {
        AbstractCard* card;
        bool selected;
    };

    enum SelectCardsRoles
    {
        SelectCardsRole_ImageCard = Qt::UserRole,
        SelectCardsRole_Selected
    };

    explicit ModelPopupSelectCardInPacket(QObject *parent = nullptr);

    static void declareQML();

    void addPacketFromAbstractPacket(AbstractPacket* packet);
    void addPacketFromModelListEnergies(ModelListEnergies* model);

    Q_INVOKABLE unsigned short numberOfCardsToSelect();
    void setNumberOfCardsToSelect(unsigned short numberToSelect);
    unsigned short numberOfCardsSelected();
    bool isMaximumCardsSelected();

    QList<int> listIndexCardsSelected();

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual int rowCount(const QModelIndex & = QModelIndex()) const override;

signals:
    void numberOfCardsSelectedChanged();
    void finished();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<SelectionCards> m_listCards;
    unsigned short m_numberOfCardsToSelect;

    void cleanPacket();

};

#endif // MODELPOPUPSELECTCARDINPACKET_H

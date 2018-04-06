#ifndef MODELLISTENERGIES_H
#define MODELLISTENERGIES_H

#include <QAbstractListModel>
#include <QVariant>

class CardEnergy;

class ModelListEnergies : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ListEnergiesRole
    {
        ListEnergiesRole_Icon = Qt::UserRole
    };

    explicit ModelListEnergies(QObject *parent = nullptr);

    void addEnergy(CardEnergy *energy);
    CardEnergy* takeEnergy(int index);
    void removeEnergy(int index);

    QList<CardEnergy*> listOfEnergies();

    static void declareQML();

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual int rowCount(const QModelIndex & = QModelIndex()) const override;

    ModelListEnergies& operator =(const ModelListEnergies& source);

signals:

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<CardEnergy*> m_listEnergies;
};

#endif // MODELLISTENERGIES_H

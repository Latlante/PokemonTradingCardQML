#ifndef MODELLISTENERGIES_H
#define MODELLISTENERGIES_H

#include <QAbstractListModel>
#include <QVariant>

#include "../src_Cards/cardenergy.h"

class ModelListEnergies : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ListEnergiesRole
    {
        ListEnergiesRole_Icon = Qt::UserRole
    };

    ModelListEnergies(QObject *parent = nullptr);
    ~ModelListEnergies();

    void addEnergy(CardEnergy *energy);
    CardEnergy* takeEnergy(int index);
    void removeEnergy(int index);

    QList<CardEnergy*> listOfEnergies();
    unsigned short countEnergies();
    unsigned short countEnergies(AbstractCard::Enum_element element);
    bool hasEnoughEnergies(QMap<AbstractCard::Enum_element, unsigned short> cost);

    static void declareQML();

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual int rowCount(const QModelIndex & = QModelIndex()) const override;

signals:

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<CardEnergy*> m_listEnergies;
};

#endif // MODELLISTENERGIES_H

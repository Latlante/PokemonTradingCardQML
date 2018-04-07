#include "modellistenergies.h"
#include <QtQml/qqml.h>

#include "src_Cards/cardenergy.h"

ModelListEnergies::ModelListEnergies(QObject *parent) :
    QAbstractListModel(parent)
{

}

ModelListEnergies::~ModelListEnergies()
{

}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void ModelListEnergies::declareQML()
{
    qmlRegisterUncreatableType<ModelListEnergies>("model", 1, 0, "ModelListEnergies", "ModelListEnergies error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
void ModelListEnergies::addEnergy(CardEnergy *energy)
{
    if(energy != nullptr)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_listEnergies.append(energy);
        endInsertRows();
    }
}

CardEnergy* ModelListEnergies::takeEnergy(int index)
{
    CardEnergy* energyToReturn = nullptr;

    if((index >= 0) && (index < rowCount()))
    {
        beginRemoveRows(QModelIndex(), index, index);
        energyToReturn = m_listEnergies.takeAt(index);
        endRemoveRows();
    }

    return energyToReturn;
}

void ModelListEnergies::removeEnergy(int index)
{
    if((index >= 0) && (index < rowCount()))
    {
        delete takeEnergy(index);
    }
}

QList<CardEnergy*> ModelListEnergies::listOfEnergies()
{
    return m_listEnergies;
}

QVariant ModelListEnergies::data(const QModelIndex &index, int role) const
{
    //qDebug() << __PRETTY_FUNCTION__ << index << role;
    int iRow = index.row();
    if ((iRow < 0) || (iRow >= rowCount()))
    {
        qCritical() << __PRETTY_FUNCTION__ << "bad row num : " << iRow;
        return QVariant();
    }

    switch(role)
    {
    case ListEnergiesRole_Icon:         return "energies/icones/" + QString::number(static_cast<int>(m_listEnergies[iRow]->element())) + ".png";
    }

    return QVariant();
}

int ModelListEnergies::rowCount(const QModelIndex &) const
{
    return m_listEnergies.count();
}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
QHash<int, QByteArray> ModelListEnergies::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ListEnergiesRole_Icon] = "icon";

    return roles;
}

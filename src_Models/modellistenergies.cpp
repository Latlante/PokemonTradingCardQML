#include "modellistenergies.h"
#include <QtQml/qqml.h>

ModelListEnergies::ModelListEnergies(QObject *parent) :
    QAbstractListModel(parent),
    m_listEnergies(QList<CardEnergy*>())
{

}

ModelListEnergies::~ModelListEnergies()
{
    while(m_listEnergies.count() > 0)
        delete m_listEnergies.takeFirst();
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

CardEnergy* ModelListEnergies::energy(int index)
{
    CardEnergy* energyToReturn = nullptr;

    if((index >= 0) && (index < rowCount()))
    {
        energyToReturn = m_listEnergies[index];
    }

    return energyToReturn;
}

QList<CardEnergy*> ModelListEnergies::takeAllEnergies()
{
    QList<CardEnergy*> listToReturn;

    for(int i=0;i<rowCount();++i)
        listToReturn.append(takeEnergy(i));

    return listToReturn;
}

unsigned short ModelListEnergies::countEnergies()
{
    int count = 0;

    foreach (CardEnergy* energy, m_listEnergies)
    {
        count += energy->quantity();
    }

    return count;
}

unsigned short ModelListEnergies::countEnergies(AbstractCard::Enum_element element)
{
    int count = 0;

    foreach (CardEnergy* energy, m_listEnergies)
    {
        if (energy->element() == element)
            count += energy->quantity();
    }

    return count;
}

bool ModelListEnergies::hasEnoughEnergies(QMap<AbstractCard::Enum_element, unsigned short> cost)
{
    bool statusBack = true;

    if (cost.count() > 0)
    {
        QMap<AbstractCard::Enum_element, unsigned short> mapEnergiesAssigned;

        //Création d'une copie des énergies assignées similaire au coût de l'attaque
        //pour faciliter le traitement
        foreach(CardEnergy* energy, m_listEnergies)
        {
            AbstractCard::Enum_element elementEnergy = energy->element();
            unsigned short quantity = mapEnergiesAssigned[elementEnergy];
            quantity += energy->quantity();
            mapEnergiesAssigned[elementEnergy] = quantity;
        }

        //On commence par retirer toutes les énergies nécessaires à l'exception des normales
        foreach (AbstractCard::Enum_element element, cost.keys())
        {
            if(element != AbstractCard::Element_Normal)
            {
                if (mapEnergiesAssigned.value(element) >= cost.value(element))
                {
                    unsigned short quantity = mapEnergiesAssigned[element];
                    quantity -= cost.value(element);
                    mapEnergiesAssigned[element] = quantity;
                }
                else
                {
                    statusBack = false;
                    break;
                }
            }
        }

        //Si l'attaque nécessite des énergies "normales", on regarde ce qu'il reste
        if((statusBack == true) && (cost.keys().contains(AbstractCard::Element_Normal)))
        {
            unsigned short countEnergiesLeft = 0;
            foreach (AbstractCard::Enum_element element, mapEnergiesAssigned.keys())
                countEnergiesLeft += mapEnergiesAssigned.value(element);

            if(countEnergiesLeft < cost.value(AbstractCard::Element_Normal))
                statusBack = false;
        }
    }

    return statusBack;
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

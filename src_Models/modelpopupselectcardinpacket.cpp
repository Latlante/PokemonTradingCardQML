#include "modelpopupselectcardinpacket.h"
#include <QtQml/qqml.h>

#include "src_Cards/abstractcard.h"
#include "src_Models/modellistenergies.h"
#include "src_Packets/abstractpacket.h"

ModelPopupSelectCardInPacket::ModelPopupSelectCardInPacket(QObject *parent) :
    QAbstractListModel(parent),
    m_listCards(QList<SelectionCards>()),
    m_numberOfCardsToSelect(1)
{

}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void ModelPopupSelectCardInPacket::declareQML()
{
    qmlRegisterUncreatableType<ModelPopupSelectCardInPacket>("model", 1, 0, "ModelPopupSelectCardInPacket", "ModelPopupSelectCardInPacket error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
void ModelPopupSelectCardInPacket::addPacketFromAbstractPacket(AbstractPacket *packet)
{
    if(packet != nullptr)
    {
        m_listCards.clear();

        for(int i=0;i<packet->countCard();++i)
        {
            SelectionCards selection;
            selection.card = packet->card(i);
            selection.selected = false;

            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            m_listCards.append(selection);
            endInsertRows();
        }
    }
}

void ModelPopupSelectCardInPacket::addPacketFromModelListEnergies(ModelListEnergies *model)
{
    if(model != nullptr)
    {
        m_listCards.clear();

        for(int i=0;i<model->rowCount();++i)
        {
            SelectionCards selection;
            selection.card = model->energy(i);
            selection.selected = false;

            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            m_listCards.append(selection);
            endInsertRows();
        }
    }
}

unsigned short ModelPopupSelectCardInPacket::numberOfCardsToSelect()
{
    return m_numberOfCardsToSelect;
}

void ModelPopupSelectCardInPacket::setNumberOfCardsToSelect(unsigned short numberToSelect)
{
    m_numberOfCardsToSelect = numberToSelect;
}

unsigned short ModelPopupSelectCardInPacket::numberOfCardsSelected()
{
    unsigned short countSelected = 0;

    foreach(SelectionCards selection, m_listCards)
    {
        countSelected += selection.selected ? 1 : 0;
    }

    return countSelected;
}

QVariant ModelPopupSelectCardInPacket::data(const QModelIndex &index, int role) const
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
    case SelectCardsRole_ImageCard:     return m_listCards[iRow].card->image();
    case SelectCardsRole_Selected:      return m_listCards[iRow].selected;
    }

    return QVariant();
}

bool ModelPopupSelectCardInPacket::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int iRow = index.row();
    if ((iRow < 0) || (iRow >= rowCount()))
    {
        qCritical() << __PRETTY_FUNCTION__ << "bad row num : " << iRow;
        return false;
    }

    switch(role)
    {
    //case SelectCardsRole_ImageCard:     return m_listCards[iRow].card->image();
    case SelectCardsRole_Selected:
        if(value.type() == QVariant::Bool)
        {
            bool isSelected = value.toBool();
            bool ignoreSelection = ((isSelected == true) && (isMaximumCardsSelected() == true));

            if(ignoreSelection == false)
            {
                SelectionCards selection = m_listCards[iRow];
                selection.selected = isSelected;
                m_listCards.replace(iRow, selection);
                emit dataChanged(index, index);
            }
        }
        else
            return false;
    }

    return true;
}

int ModelPopupSelectCardInPacket::rowCount(const QModelIndex &) const
{
    return m_listCards.count();
}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
QHash<int, QByteArray> ModelPopupSelectCardInPacket::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SelectCardsRole_ImageCard] = "imageCard";
    roles[SelectCardsRole_Selected] = "selected";

    return roles;
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
bool ModelPopupSelectCardInPacket::isMaximumCardsSelected()
{
    return numberOfCardsSelected() >= numberOfCardsToSelect();
}

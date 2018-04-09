#include "bencharea.h"

#include <QDebug>
#include <QPixmap>
#include <QVariant>
#include "src_Cards/abstractcard.h"
#include "src_Cards/cardpokemon.h"
#include "src_Models/modellistenergies.h"

BenchArea::BenchArea(QList<AbstractCard*> listCards) :
    AbstractPacketStatic(listCards)
{
	
}

BenchArea::~BenchArea()
{
	
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void BenchArea::declareQML()
{
    qmlRegisterUncreatableType<BenchArea>("model", 1, 0, "BenchArea", "BenchArea error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
int BenchArea::maxCards() const
{
    return MAXCARDS_BENCH;
}

ModelListEnergies* BenchArea::modelFromCardPokemon(int index)
{
    qDebug() << __PRETTY_FUNCTION__ << index;

    /*int iRow = index;
    int rowCountPacket = AbstractPacket::rowCount();
    if ((iRow < 0) || (iRow >= rowCountPacket))
    {
        qCritical() << __PRETTY_FUNCTION__ << "bad row num : " << iRow;
        return nullptr;
    }*/

    ModelListEnergies* modelToReturn = nullptr;

    if((index >= 0) && (index < countCard()))
    {
        CardPokemon* cardPok = dynamic_cast<CardPokemon*>(m_listCards[index]);

        if(cardPok != nullptr)
            modelToReturn = cardPok->modelListOfEnergies();
    }

    return modelToReturn;
}

//QVariant BenchArea::data(const QModelIndex& index, int role) const
//{
//    //qDebug() << __PRETTY_FUNCTION__ << index << role;

//    int iRow = index.row();
//    if ((iRow < 0) || (iRow >= rowCount()))
//    {
//        qCritical() << __PRETTY_FUNCTION__ << "bad row num : " << iRow;
//        return QVariant();
//    }

//    //Dans la liste
//    if(iRow < countCard())
//    {
//        CardPokemon* cardPok = dynamic_cast<CardPokemon*>(m_listCards[iRow]);

//        if(cardPok != nullptr)
//        {
//            switch(role)
//            {
//            case BenchRole_Card:            return QVariant::fromValue<AbstractCard*>(m_listCards[iRow]);
//            case BenchRole_IsCard:          return true;
//            case BenchRole_Name:            return m_listCards[iRow]->name();
//            case BenchRole_ImageCard:       return m_listCards[iRow]->image();
//            //case BenchRole_ModelEnergies:   return QVariant::fromValue<ModelListEnergies*>(cardPok->modelListOfEnergies());
//            }
//        }
//        else
//        {
//            return QVariant::Invalid;
//        }

//    }
//    //Au delà
//    else
//    {
//        switch(role)
//        {
//        case BenchRole_Card:            return QVariant();
//        case BenchRole_IsCard:          return false;
//        case BenchRole_Name:            return "";
//        case BenchRole_ImageCard:       return AbstractCard::imageByDefault();
//        //case BenchRole_ModelEnergies:   return QVariant();
//        }
//    }

//    return QVariant::Invalid;
//}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
QHash<int, QByteArray> BenchArea::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[BenchRole_Card] = "card";
    roles[BenchRole_IsCard] = "isCard";
    roles[BenchRole_Name] = "name";
    roles[BenchRole_ImageCard] = "imageCard";
    roles[BenchRole_ModelEnergies] = "modelEnergies";

    return roles;
}

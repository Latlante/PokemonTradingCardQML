#include "bencharea.h"

#include <QDebug>
#include <QPixmap>
#include "src_Cards/cardpokemon.h"

BenchArea::BenchArea(QList<AbstractCard*> listCards) :
	AbstractPacket(listCards)
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
int BenchArea::maxCards()
{
    return MAXCARDS_BENCH;
}

QVariant BenchArea::data(const QModelIndex& index, int role) const
{
    //qDebug() << __PRETTY_FUNCTION__ << index << role;

    int iRow = index.row();
    if ((iRow < 0) || (iRow >= rowCount()))
    {
        qCritical() << __PRETTY_FUNCTION__ << "bad row num : " << iRow;
        return QVariant();
    }

    if (Qt::DisplayRole == role)
    {
        AbstractCard* abCard = m_listCards[iRow];

        if (abCard != NULL)
        {
            if (abCard->type() == AbstractCard::TypeOfCard_Pokemon)
            {
                CardPokemon *cardPok = static_cast<CardPokemon*>(abCard);

                switch(iRow)
                {
                case 0: //Nom du pokemon
                    return cardPok->name();
                case 1: //Vie restante et total
                    return QString::number(cardPok->lifeLeft()) + "/" + QString::number(cardPok->lifeTotal());
                case 2: //Energies
                    return "Energies=" + QString::number(cardPok->countEnergies());
                default:
                    break;
                }

                /*QString messageToDisplay = cardPok->name();
                messageToDisplay += " (" + QString::number(cardPok->lifeLeft()) + "/" + QString::number(cardPok->lifeTotal()) + ")";
                messageToDisplay += " : Energies=" + QString::number(cardPok->countEnergies());

                return messageToDisplay;*/
            }
            else
            {
                return "Erreur de carte: La carte n'est pas du bon type:" + abCard->type();
            }
        }
        else
        {
            return "Erreur de carte: Card is NULL";
        }
    }
    else if (BenchR_Image == role)
    {
        AbstractCard* abCard = m_listCards[iRow];
        QString pathImage = "Images/cartes/" + QString::number(abCard->id()) + ".png";
        qDebug() << "PATH de l'image Bench:" << pathImage;
        return QPixmap(pathImage);
    }

    return QVariant::Invalid;
}

/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
QHash<int, QByteArray> BenchArea::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    roles[BenchR_Image] = "image";

    return roles;
}

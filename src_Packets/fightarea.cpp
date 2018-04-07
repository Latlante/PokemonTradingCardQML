#include "fightarea.h"

#include <QDebug>
#include "src_Cards/cardpokemon.h"
#include "utils.h"

FightArea::FightArea(QList<AbstractCard*> listCards) :
    AbstractPacketStatic(listCards)
{
	
}

FightArea::~FightArea()
{
	
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
int FightArea::maxCards() const
{
    return MAXCARDS_FIGHT;
}

CardPokemon* FightArea::pokemonFighting(int index)
{
    CardPokemon* pokemon = NULL;

    AbstractCard* abCard = card(index);

    if(abCard != NULL)
    {
        pokemon = static_cast<CardPokemon*>(abCard);
    }

    return pokemon;
}

QVariant FightArea::data(const QModelIndex& index, int role) const
{
    //qDebug() << __PRETTY_FUNCTION__ << index << role;

    /*int iRow = index.row();
    int iColumn = index.column();
    if ((iRow < 0) || (iRow >= rowCount()))
    {
        qCritical() << __PRETTY_FUNCTION__ << "bad column num : " << iRow;
        return QVariant();
    }

    if (Qt::DisplayRole == role)
    {
        AbstractCard* abCard = m_listCards[index.column()];

        if (abCard != NULL)
        {
            if (abCard->type() == AbstractCard::TypeOfCard_Pokemon)
            {
                CardPokemon *cardPok = static_cast<CardPokemon*>(abCard);

                switch(iRow)
                {
                case 0: //Nom du pokemon - Vie restante et total
                    return cardPok->name() + " - " + QString::number(cardPok->lifeLeft()) + "/" + QString::number(cardPok->lifeTotal()) + " - " + QString::number(cardPok->status());
                case 1: //Energies
                    return "Energies=" + QString::number(cardPok->countEnergies());
                case 2: //Attaque 1
                    if(cardPok->listAttacks().count() >= 1)
                        return cardPok->listAttacks()[0].name + " - " + QString::number(cardPok->listAttacks()[0].damage) + " " + cardPok->listAttacks()[0].description;
                    else
                        return QVariant();
                case 3: //Attaque 2
                    if(cardPok->listAttacks().count() >= 2)
                        return cardPok->listAttacks()[1].name + " - " + QString::number(cardPok->listAttacks()[1].damage) + " " + cardPok->listAttacks()[1].description;
                    else
                        return QVariant();
                case 4: //Attaque 3
                    if(cardPok->listAttacks().count() >= 3)
                        return cardPok->listAttacks()[2].name + " - " + QString::number(cardPok->listAttacks()[2].damage) + " " + cardPok->listAttacks()[2].description;
                    else
                        return QVariant();

                default:
                    break;
                }

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
    }*/

    return QVariant::Invalid;
}

/************************************************************
*****			FONCTIONS SLOTS PRIVEES					*****
************************************************************/


/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/


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

/************************************************************
*****			FONCTIONS SLOTS PRIVEES					*****
************************************************************/


/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/


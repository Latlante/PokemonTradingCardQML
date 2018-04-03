#include "cardpokemon.h"

#include <QDebug>
#include <QUrl>
#include "src_Actions/abstractaction.h"
#include "cardenergy.h"

CardPokemon::CardPokemon(unsigned short id, 
			const QString& name, 
			AbstractCard::Enum_element element,
			unsigned short lifeTotal,
			QList<AttackData> listAttacks,
			short evolutionFrom) :
    AbstractCard(id, name),
	m_element(element),
	m_lifeTotal(lifeTotal),
	m_lifeLeft(lifeTotal),
	m_status(Status_Normal),
	m_listAttacks(listAttacks),
	m_listEnergies(QList<CardEnergy*>()),
	m_evolutionFrom(evolutionFrom)
{
	
}
				
CardPokemon::~CardPokemon()
{
	
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractCard::Enum_typeOfCard CardPokemon::type()
{
    return AbstractCard::TypeOfCard_Pokemon;
}

QUrl CardPokemon::image()
{
    const QString path = "Images/cartes/pokemon/" + QString::number(id()) + ".png";
    qDebug() << __PRETTY_FUNCTION__ << "path image:" << path;

    //return QPixmap(path);
    return QUrl::fromLocalFile(path);
}

AbstractCard::Enum_element CardPokemon::element()
{
    return m_element;
}

unsigned short CardPokemon::lifeTotal()
{
	return m_lifeTotal;
}

unsigned short CardPokemon::lifeLeft()
{
	return m_lifeLeft;
}

CardPokemon::Enum_statusOfPokemon CardPokemon::status()
{
	return m_status;
}

void CardPokemon::setStatus(Enum_statusOfPokemon status)
{
    if(m_status != status)
    {
        m_status = status;
        emit statusChanged();
        emit dataChanged();
    }
}

QList<AttackData> CardPokemon::listAttacks()
{
	return m_listAttacks;
}

void CardPokemon::addEnergy(CardEnergy *energy)
{
    m_listEnergies.append(energy);
    emit listEnergiesChanged();
    emit dataChanged();
}

unsigned short CardPokemon::countEnergies()
{
    int count = 0;

    foreach (CardEnergy* energy, m_listEnergies)
    {
        count += energy->quantity();
    }

    return count;
}

unsigned short CardPokemon::countEnergies(Enum_element element)
{
	int count = 0;
	
	foreach (CardEnergy* energy, m_listEnergies)
	{
        if (energy->element() == element)
            count += energy->quantity();
	}
	
	return count;
}

bool CardPokemon::tryToAttack(int indexAttack, CardPokemon* enemy)
{
	bool statusBack = false;
	
	if ((0 > indexAttack) || (m_listAttacks.count() <= indexAttack))
        throw "CardPokemon::attack() => index incohérent (" + QString::number(indexAttack) + ")";
	
	if (true == hasEnoughEnergies(indexAttack))
	{
		if (true == canAttackFromStatus())
		{
			AttackData attack = m_listAttacks[indexAttack];
            enemy->takeDamage(attack.damage);

            if(attack.action != NULL)
                attack.action->executeAction();
			
			statusBack = true;
		}
        else
        {
            qDebug() << name() << " est dans un état empechant d'attaquer";
        }
	}
    else
    {
        qDebug() << name() << " n'as pas asser d'énergie";
    }
	
	return statusBack;
}

void CardPokemon::takeDamage(unsigned short damage)
{
	if (damage > m_lifeLeft)
	{
        setLifeLeft(0);
	}
	else
	{
        setLifeLeft(lifeLeft() - damage);
	}
}

bool CardPokemon::canAttackFromStatus()
{
	return Status_Normal == m_status;
}

bool CardPokemon::hasEnoughEnergies(AttackData attack)
{
	bool statusBack = true;
	
	if (0 < attack.costEnergies.count())
	{
        foreach (Enum_element indexElement, attack.costEnergies.keys())
		{

            if (countEnergies(indexElement) < attack.costEnergies.value(indexElement))
				statusBack = false;
		}
	}
		
	return statusBack;
}

bool CardPokemon::hasEnoughEnergies(int indexAttack)
{
	bool statusBack = false;
	
	if ((0 <= indexAttack) && (m_listAttacks.count() > indexAttack))
	{
		statusBack = hasEnoughEnergies(m_listAttacks[indexAttack]);
	}
	
	return statusBack;
}

bool CardPokemon::isBase()
{
	return -1 == m_evolutionFrom;
}

bool CardPokemon::isSubEvolutionOf(CardPokemon* evolution)
{
    return m_id == evolution->m_evolutionFrom;
}

bool CardPokemon::isEvolutionOf(CardPokemon* evolution)
{
    return m_evolutionFrom == evolution->m_id;
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
void CardPokemon::setLifeLeft(unsigned short life)
{
    if(m_lifeLeft != life)
    {
        m_lifeLeft = life;
        emit lifeLeftChanged();
        emit dataChanged();
    }
}

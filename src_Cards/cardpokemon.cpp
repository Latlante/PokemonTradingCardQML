#include "cardpokemon.h"

#include <QDebug>
#include <QtQml/qqml.h>
#include <QUrl>
#include "src_Actions/abstractaction.h"
#include "cardenergy.h"
#include "src_Models/modellistenergies.h"

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
    //m_listEnergies(QList<CardEnergy*>()),
    m_modelListEnergies(new ModelListEnergies()),
	m_evolutionFrom(evolutionFrom)
{
	
}

CardPokemon::CardPokemon(const CardPokemon &card)
{
    *this = card;
}
				
CardPokemon::~CardPokemon()
{
    delete m_modelListEnergies;
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void CardPokemon::declareQML()
{
    qmlRegisterUncreatableType<CardPokemon>("model", 1, 0, "CardPokemon", "CardPokemon error");
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
    const QString path = "pokemon/cards/" + QString::number(id()) + ".png";
    //qDebug() << __PRETTY_FUNCTION__ << "path image:" << path;

    //return QPixmap(path);
    //return QUrl::fromLocalFile(path);
    return path;
}

AbstractCard* CardPokemon::clone()
{
    return new CardPokemon(*this);
}

AbstractCard::Enum_element CardPokemon::element()
{
    return m_element;
}

QString CardPokemon::elementFormatString()
{
    return elementToString(element());
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

QString CardPokemon::statusFormatString()
{
    return statusToString(status());
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

int CardPokemon::attacksCount()
{
    return m_listAttacks.count();
}

QString CardPokemon::attackName(int index)
{
    QString nameToReturn = "";

    if((index >= 0) && (index < attacksCount()))
        nameToReturn = m_listAttacks[index].name;

    return nameToReturn;
}

QString CardPokemon::attackDescription(int index)
{
    QString descriptionToReturn = "";

    if((index >= 0) && (index < attacksCount()))
        descriptionToReturn = m_listAttacks[index].description;

    return descriptionToReturn;
}

unsigned short CardPokemon::attackDamage(int index)
{
    unsigned short damageToReturn = 0;

    if((index >= 0) && (index < attacksCount()))
        damageToReturn = m_listAttacks[index].damage;

    return damageToReturn;
}

void CardPokemon::addEnergy(CardEnergy *energy)
{
    m_modelListEnergies->addEnergy(energy);
}

CardEnergy* CardPokemon::takeEnergy(int index)
{
    return m_modelListEnergies->takeEnergy(index);
}

void CardPokemon::removeEnergy(int index)
{
    m_modelListEnergies->removeEnergy(index);
}

unsigned short CardPokemon::countEnergies()
{
    int count = 0;

    foreach (CardEnergy* energy, m_modelListEnergies->listOfEnergies())
    {
        count += energy->quantity();
    }

    return count;
}

unsigned short CardPokemon::countEnergies(Enum_element element)
{
	int count = 0;
	
    foreach (CardEnergy* energy, m_modelListEnergies->listOfEnergies())
	{
        if (energy->element() == element)
            count += energy->quantity();
	}
	
	return count;
}

ModelListEnergies* CardPokemon::modelListOfEnergies()
{
    return m_modelListEnergies;
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

CardPokemon& CardPokemon::operator =(const CardPokemon& source)
{
    m_id = source.m_id;
    m_name = source.m_name;
    m_element = source.m_element;
    m_lifeTotal = source.m_lifeTotal;
    m_lifeLeft = source.m_lifeLeft;
    m_status = source.m_status;
    m_listAttacks = source.m_listAttacks;
    m_modelListEnergies = source.m_modelListEnergies;
    m_evolutionFrom = source.m_evolutionFrom;

    return *this;
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
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

QString CardPokemon::statusToString(Enum_statusOfPokemon status)
{
    switch(status)
    {
    case Status_Confused:   return "Confus";
    case Status_Normal:     return "";
    case Status_Paralyzed:  return "Paralysé";
    case Status_Poisoned:   return "Empoisonné";
    case Status_Slept:      return "Endormi";
    }

    return "Erreur de conversion de status";
}

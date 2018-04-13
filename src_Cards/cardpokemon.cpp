#include "cardpokemon.h"

#include <QDebug>
#include <QtQml/qqml.h>
#include <QUrl>
#include "../src_Actions/abstractaction.h"
#include "cardenergy.h"
#include "../src_Models/modellistenergies.h"
#include "utils.h"

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
    m_invincibleOnNextTurn(false),
	m_listAttacks(listAttacks),
    m_modelListEnergies(new ModelListEnergies()),
	m_evolutionFrom(evolutionFrom)
{
	
}

CardPokemon::CardPokemon(const CardPokemon &card) :
    m_status(Status_Normal),
    m_invincibleOnNextTurn(false),
    m_modelListEnergies(new ModelListEnergies())
{
    *this = card;
}
				
CardPokemon::~CardPokemon()
{
    //delete m_modelListEnergies;
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

bool CardPokemon::isDied()
{
    return lifeLeft() <= 0;
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

bool CardPokemon::isInvincibleForTheNextTurn()
{
    return m_invincibleOnNextTurn;
}

void CardPokemon::setInvincibleForTheNextTurn(bool status)
{
    m_invincibleOnNextTurn = status;
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
    return m_modelListEnergies->countEnergies();
}

unsigned short CardPokemon::countEnergies(Enum_element element)
{
    return m_modelListEnergies->countEnergies(element);
}

ModelListEnergies* CardPokemon::modelListOfEnergies()
{
    return m_modelListEnergies;
}

QList<CardEnergy*> CardPokemon::takeAllEnergies()
{
    return m_modelListEnergies->takeAllEnergies();
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
        qDebug() << name() << " n'as pas assez d'énergie";
    }
	
	return statusBack;
}

void CardPokemon::takeDamage(unsigned short damage)
{
    if(isInvincibleForTheNextTurn())
    {
        setInvincibleForTheNextTurn(false);
    }
    else
    {
        if (damage > lifeLeft())
        {
            setLifeLeft(0);
        }
        else
        {
            setLifeLeft(lifeLeft() - damage);
        }
    }
}

void CardPokemon::restoreLife(unsigned short life)
{
    setLifeLeft(lifeLeft() + life);
}

bool CardPokemon::canAttackFromStatus()
{
    bool canAttack = true;

    switch(status())
    {
    case Status_Confused:
        if(Utils::headOrTail() == 0)    //Si pile
            takeDamage(DAMAGE_WHEN_CONFUSED);
        break;
    case Status_Normal:
    case Status_Poisoned:
        break;
    default:    //Paralysé ou endormi
        canAttack = false;
    }

    return canAttack;
}

bool CardPokemon::hasEnoughEnergies(AttackData attack)
{
    return m_modelListEnergies->hasEnoughEnergies(attack.costEnergies);
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
    m_lifeLeft = m_lifeTotal;
    m_listAttacks = source.m_listAttacks;
    //m_modelListEnergies = source.m_modelListEnergies;     //Pas besoin
    m_evolutionFrom = source.m_evolutionFrom;

    return *this;
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
void CardPokemon::setLifeLeft(unsigned short life)
{
    if(life > lifeTotal())
        life = lifeTotal();

    if(m_lifeLeft != life)
    {
        qDebug() << __PRETTY_FUNCTION__ << life;

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

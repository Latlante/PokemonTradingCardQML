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
    m_damage(0),
    m_status(Status_Normal),
    m_invincibleOnNextTurn(false),
	m_listAttacks(listAttacks),
    m_modelListEnergies(new ModelListEnergies()),
    m_cardEvolution(nullptr),
	m_evolutionFrom(evolutionFrom)
{
	
}

CardPokemon::CardPokemon(const CardPokemon &card) :
    m_status(Status_Normal),
    m_invincibleOnNextTurn(false),
    m_modelListEnergies(new ModelListEnergies()),
    m_cardEvolution(nullptr)
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
int CardPokemon::id()
{
    int idCard = -1;

    if(m_cardEvolution != nullptr)
        idCard = m_cardEvolution->id();
    else
        idCard = m_id;

    return idCard;
}

const QString CardPokemon::name()
{
    QString nameCard = "";

    if(m_cardEvolution != nullptr)
        nameCard = m_cardEvolution->name();
    else
        nameCard = m_name;

    return nameCard;
}

AbstractCard::Enum_typeOfCard CardPokemon::type()
{
    return AbstractCard::TypeOfCard_Pokemon;
}

QUrl CardPokemon::image()
{
    QUrl path;

    //qDebug() << __PRETTY_FUNCTION__ << this << m_id << m_name << m_cardEvolution;

    if(m_cardEvolution != nullptr)
        path = m_cardEvolution->image();
    else
        path = QUrl("pokemon/cards/" + QString::number(id()) + ".png");

    return path;
}

AbstractCard* CardPokemon::clone()
{
    return new CardPokemon(*this);
}

AbstractCard::Enum_element CardPokemon::element()
{
    //Element ne change pas entre les évolutions (pour le set de base)
    /*if(m_cardEvolution != nullptr)
        return m_cardEvolution->element();*/

    return m_element;
}

QString CardPokemon::elementFormatString()
{
    return elementToString(element());
}

unsigned short CardPokemon::lifeTotal()
{
    if(m_cardEvolution != nullptr)
        return m_cardEvolution->lifeTotal();

	return m_lifeTotal;
}

bool CardPokemon::isDied()
{
    return lifeLeft() <= 0;
}

unsigned short CardPokemon::lifeLeft()
{
    return lifeTotal() - currentDamage();
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
    if(m_cardEvolution != nullptr)
        return m_cardEvolution->listAttacks();

	return m_listAttacks;
}

int CardPokemon::attacksCount()
{
    return listAttacks().count();
}

QString CardPokemon::attackName(int index)
{
    QString nameToReturn = "";

    if((index >= 0) && (index < attacksCount()))
        nameToReturn = listAttacks()[index].name;

    return nameToReturn;
}

QString CardPokemon::attackDescription(int index)
{
    QString descriptionToReturn = "";

    if((index >= 0) && (index < attacksCount()))
        descriptionToReturn = listAttacks()[index].description;

    return descriptionToReturn;
}

unsigned short CardPokemon::attackDamage(int index)
{
    unsigned short damageToReturn = 0;

    if((index >= 0) && (index < attacksCount()))
        damageToReturn = listAttacks()[index].damage;

    return damageToReturn;
}

bool CardPokemon::replaceOneAttack(int index, AttackData data)
{
    bool statusBack = true;

    if((index >= 0) && (index < listAttacks().count()))
    {
        //Nettoyage de l'ancienne action
        AttackData oldData = listAttacks()[index];
        if(oldData.action != nullptr)
        {
            delete oldData.action;
            oldData.action = nullptr;
        }

        //Copie
        m_listAttacks.replace(index, data);
    }
    else
        statusBack = false;
    
    return statusBack;
}

#ifdef TESTS_UNITAIRES
void CardPokemon::setAttacks(int index, AttackData data)
{
    if(index > m_listAttacks.count())
        m_listAttacks.append(data);
    else
        m_listAttacks.replace(index, data);
}
#endif

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

CardPokemon::Enum_StatusOfAttack CardPokemon::tryToAttack(int indexAttack, CardPokemon* enemy)
{
    //bool statusBack = false;
    Enum_StatusOfAttack statusBack = Attack_UnknownError;
	
    if ((0 <= indexAttack) && (listAttacks().count() > indexAttack))
    {
        if (true == hasEnoughEnergies(indexAttack))
        {
            if (true == canAttackFromStatus())
            {
                AttackData attack = listAttacks()[indexAttack];
                enemy->takeDamage(attack.damage);

                if(attack.action != nullptr)
                    attack.action->executeAction(indexAttack);

                enemy->setInvincibleForTheNextTurn(false);
                statusBack = Attack_OK;
            }
            else
            {
                statusBack = Attack_WrongStatus;
            }
        }
        else
        {
            statusBack = Attack_NotEnoughEnergies;
        }
    }
    else
    {
        statusBack = Attack_IndexNOK;
    }
	
	return statusBack;
}

void CardPokemon::takeDamage(unsigned short damage)
{
    if(!isInvincibleForTheNextTurn())
    {
        setDamage(currentDamage() + damage);
    }
}

void CardPokemon::restoreLife(unsigned short life)
{
    if(life > currentDamage())
        setDamage(0);
    else
        setDamage(currentDamage() - life);
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
	
    if ((0 <= indexAttack) && (listAttacks().count() > indexAttack))
	{
        statusBack = hasEnoughEnergies(listAttacks()[indexAttack]);
	}
	
	return statusBack;
}

bool CardPokemon::evolve(CardPokemon *evolution)
{
    bool evolutionOk = false;

    //Il y a déjà une évolution
    if(m_cardEvolution != nullptr)
    {
        if(m_cardEvolution->isSubEvolutionOf(evolution))
        {
            m_cardEvolution->evolve(evolution);
            evolutionOk = true;
        }
    }
    else
    {
        if(isSubEvolutionOf(evolution))
        {
            m_cardEvolution = evolution;
            connect(m_cardEvolution, &CardPokemon::dataChanged, this, &CardPokemon::dataChanged);
            connect(m_cardEvolution, &CardPokemon::lifeLeftChanged, this, &CardPokemon::lifeLeftChanged);
            connect(m_cardEvolution, &CardPokemon::statusChanged, this, &CardPokemon::statusChanged);
            connect(m_cardEvolution, &CardPokemon::listEnergiesChanged, this, &CardPokemon::listEnergiesChanged);
            connect(m_cardEvolution, &CardPokemon::hasEvolved, this, &CardPokemon::hasEvolved);

            evolutionOk = true;
        }
    }


    if(evolutionOk)
    {
        //L'évolution reset le status
        setStatus(CardPokemon::Status_Normal);

        emit hasEvolved();
        emit lifeLeftChanged();
        emit dataChanged();
    }

    return evolutionOk;
}

bool CardPokemon::isBase()
{
	return -1 == m_evolutionFrom;
}

bool CardPokemon::isSubEvolutionOf(CardPokemon* evolution)
{
    return m_id == evolution->m_evolutionFrom;
}

bool CardPokemon::isEvolutionOf(CardPokemon* subEvolution)
{
    return m_evolutionFrom == subEvolution->m_id;
}

CardPokemon& CardPokemon::operator =(const CardPokemon& source)
{
    m_id = source.m_id;
    m_name = source.m_name;
    m_element = source.m_element;
    m_lifeTotal = source.m_lifeTotal;
    m_damage = 0;
    m_listAttacks = source.m_listAttacks;
    //m_modelListEnergies = source.m_modelListEnergies;     //Pas besoin
    m_cardEvolution = source.m_cardEvolution;
    m_evolutionFrom = source.m_evolutionFrom;

    return *this;
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
unsigned short CardPokemon::currentDamage()
{
    return m_damage;
}

void CardPokemon::setDamage(unsigned short damage)
{
    if(damage > lifeTotal())
        damage = lifeTotal();

    if(m_damage != damage)
    {
        m_damage = damage;
        emit lifeLeftChanged();
        emit dataChanged();
    }
}

QString CardPokemon::statusToString(Enum_statusOfPokemon status)
{
    switch(status)
    {
    case Status_Confused:   return "Confus";
    case Status_Normal:     return "OK";
    case Status_Paralyzed:  return "Paralysé";
    case Status_Poisoned:   return "Empoisonné";
    case Status_Slept:      return "Endormi";
    }

    return "Erreur de conversion de status";
}

#ifndef CARDPOKEMON_H
#define CARDPOKEMON_H

#include "abstractcard.h"

#include <QMap>

class AbstractAction;
class CardEnergy;

struct AttackData
{
	QString name;
	QString description;
	unsigned short damage;
    QMap<AbstractCard::Enum_element, unsigned short> costEnergies;
    AbstractAction* action;
};

class CardPokemon : public AbstractCard
{
	Q_OBJECT
	
public:
	enum Enum_statusOfPokemon
	{
		Status_Confused = 0,
		Status_Normal,
		Status_Paralyzed,
		Status_Poisoned,
		Status_Slept
	};

    CardPokemon(unsigned short id, 
				const QString& name, 
				AbstractCard::Enum_element element,
				unsigned short lifeTotal,
				QList<AttackData> listAttacks,
				short evolutionFrom = -1);
    CardPokemon(const CardPokemon& card);
    ~CardPokemon();

    static void declareQML();

    Q_INVOKABLE AbstractCard::Enum_typeOfCard type() override;
    Q_INVOKABLE QUrl image() override;
    AbstractCard* clone() override;
    Q_INVOKABLE AbstractCard::Enum_element element();
    Q_INVOKABLE QString elementFormatString();
    Q_INVOKABLE unsigned short lifeTotal();
    Q_INVOKABLE unsigned short lifeLeft();
    Q_INVOKABLE Enum_statusOfPokemon status();
    void setStatus(Enum_statusOfPokemon status);
    Q_INVOKABLE QList<AttackData> listAttacks();
	
    void addEnergy(CardEnergy* energy);
	unsigned short countEnergies();
	unsigned short countEnergies(Enum_element element);
	
    bool tryToAttack(int indexAttack, CardPokemon *enemy);
	void takeDamage(unsigned short damage);
	bool canAttackFromStatus();
	bool hasEnoughEnergies(AttackData attack);
	bool hasEnoughEnergies(int indexAttack);
	bool isBase();
	bool isSubEvolutionOf(CardPokemon* evolution);
	bool isEvolutionOf(CardPokemon* evolution);

    CardPokemon& operator =(const CardPokemon& source);

signals:
    void lifeLeftChanged();
    void statusChanged();
    void listEnergiesChanged();

private:
	AbstractCard::Enum_element m_element;
	unsigned short m_lifeTotal;
	unsigned short m_lifeLeft;
	Enum_statusOfPokemon m_status;
	QList<AttackData> m_listAttacks;
	QList<CardEnergy*> m_listEnergies;
	short m_evolutionFrom;
	
    void setLifeLeft(unsigned short life);

};

#endif // CARDPOKEMON_H

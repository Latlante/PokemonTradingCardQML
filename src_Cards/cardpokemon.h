#ifndef CARDPOKEMON_H
#define CARDPOKEMON_H

#include "abstractcard.h"

#include <QMap>

class AbstractAction;
class CardEnergy;
class ModelListEnergies;

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
    Q_PROPERTY(QString name READ name NOTIFY hasEvolved)
    Q_PROPERTY(QUrl image READ image NOTIFY hasEvolved)
    Q_PROPERTY(unsigned short lifeTotal READ lifeTotal NOTIFY hasEvolved)
    Q_PROPERTY(unsigned short lifeLeft READ lifeLeft NOTIFY lifeLeftChanged)
    Q_PROPERTY(Enum_statusOfPokemon status READ status NOTIFY statusChanged)
	
public:
    enum Enum_statusOfPokemon
    {
        Status_Confused = 0,
        Status_Normal,
        Status_Paralyzed,
        Status_Poisoned,
        Status_Slept
    };
    Q_ENUMS(Enum_statusOfPokemon)

    enum Enum_StatusOfAttack
    {
        Attack_OK = 0,
        Attack_IndexNOK,
        Attack_NotEnoughEnergies,
        Attack_WrongStatus
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

    int id() override;
    const QString name() override;
    Q_INVOKABLE AbstractCard::Enum_typeOfCard type() override;
    Q_INVOKABLE QUrl image() override;
    AbstractCard* clone() override;
    Q_INVOKABLE AbstractCard::Enum_element element();
    Q_INVOKABLE QString elementFormatString();
    unsigned short lifeTotal();
    bool isDied();
    unsigned short lifeLeft();
    Enum_statusOfPokemon status();
    Q_INVOKABLE QString statusFormatString();
    void setStatus(Enum_statusOfPokemon status);
    bool isInvincibleForTheNextTurn();
    void setInvincibleForTheNextTurn(bool status);

    Q_INVOKABLE QList<AttackData> listAttacks();
    Q_INVOKABLE int attacksCount();
    Q_INVOKABLE QString attackName(int index);
    Q_INVOKABLE QString attackDescription(int index);
    Q_INVOKABLE unsigned short attackDamage(int index);
#ifdef TESTS_UNITAIRES
    void setAttacks(int index, AttackData data);
#endif
	
    void addEnergy(CardEnergy* energy);
    CardEnergy* takeEnergy(int index);
    void removeEnergy(int index);
	unsigned short countEnergies();
	unsigned short countEnergies(Enum_element element);
    Q_INVOKABLE ModelListEnergies* modelListOfEnergies();
    QList<CardEnergy*> takeAllEnergies();
	
    bool tryToAttack(int indexAttack, CardPokemon *enemy);
	void takeDamage(unsigned short damage);
    void restoreLife(unsigned short life);
	bool canAttackFromStatus();
	bool hasEnoughEnergies(AttackData attack);
	bool hasEnoughEnergies(int indexAttack);

    bool evolve(CardPokemon* evolution);
	bool isBase();
	bool isSubEvolutionOf(CardPokemon* evolution);
    bool isEvolutionOf(CardPokemon* subEvolution);

    CardPokemon& operator =(const CardPokemon& source);

signals:
    void lifeLeftChanged();
    void statusChanged();
    void listEnergiesChanged();
    void hasEvolved();

private:
	AbstractCard::Enum_element m_element;
	unsigned short m_lifeTotal;
    unsigned short m_damage;
    CardPokemon::Enum_statusOfPokemon m_status;
    bool m_invincibleOnNextTurn;
    QList<AttackData> m_listAttacks;
    ModelListEnergies* m_modelListEnergies;
    CardPokemon* m_cardEvolution;
	short m_evolutionFrom;
	
    unsigned short currentDamage();
    void setDamage(unsigned short damage);
    QString statusToString(Enum_statusOfPokemon status);
};

#endif // CARDPOKEMON_H

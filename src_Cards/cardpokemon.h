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

    bool operator ==(const AttackData& extData)
    {
        return ((name == extData.name) &&
                (description == extData.description) &&
                (damage == extData.damage) &&
                (costEnergies == extData.costEnergies) &&
                (action == extData.action));
    }
};

/*bool operator ==(const AttackData& data1, const AttackData& data2)
{
    return ((data1.name == data2.name) &&
            (data1.description == data2.description) &&
            (data1.damage == data2.damage) &&
            (data1.costEnergies == data2.costEnergies) &&
            (data1.action == data2.action));
}*/

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
        Attack_UnknownError,
        Attack_IndexNOK,
        Attack_NotEnoughEnergies,
        Attack_WrongStatus
    };

    CardPokemon(unsigned short id, 
				const QString& name, 
				AbstractCard::Enum_element element,
				unsigned short lifeTotal,
				QList<AttackData> listAttacks,
                short evolutionFrom = -1,
                unsigned short costRetreat = 0);
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
    unsigned short damageMarker();
    Enum_statusOfPokemon status();
    Q_INVOKABLE QString statusFormatString();
    void setStatus(Enum_statusOfPokemon status);
    bool isProtectedAgainstDamageForTheNextTurn();
    void setProtectedAgainstDamageForTheNextTurn(bool status);
    bool isProtectedAgainstEffectForTheNextTurn();
    void setProtectedAgainstEffectForTheNextTurn(bool status);
    void setInvincibleForTheNextTurn(bool status);

    Q_INVOKABLE QList<AttackData> listAttacks();
    Q_INVOKABLE int attacksCount();
    Q_INVOKABLE QString attackName(int index);
    Q_INVOKABLE QString attackDescription(int index);
    Q_INVOKABLE unsigned short attackDamage(int index);
    bool replaceOneAttack(int index, AttackData data);
#ifdef TESTS_UNITAIRES
    void setAttacks(int index, AttackData data);
#endif
	
    void addEnergy(CardEnergy* energy);
    CardEnergy* takeEnergy(int index);
	unsigned short countEnergies();
	unsigned short countEnergies(Enum_element element);
    Q_INVOKABLE ModelListEnergies* modelListOfEnergies();
    QList<CardEnergy*> takeAllEnergies();
	
    Enum_StatusOfAttack tryToAttack(int indexAttack, CardPokemon *enemy);
	void takeDamage(unsigned short damage);
    void restoreLife(unsigned short life);
	bool canAttackFromStatus();
	bool hasEnoughEnergies(AttackData attack);
	bool hasEnoughEnergies(int indexAttack);

    bool evolve(CardPokemon* evolution);
	bool isBase();
	bool isSubEvolutionOf(CardPokemon* evolution);
    bool isEvolutionOf(CardPokemon* subEvolution);

    void applyDamageIfPoisoned();
    unsigned short damagePoisonPerRound();
    void setDamagePoisonPerRound(unsigned short damage);

    AttackData lastAttackUsed();
    int lastIndexOfAttackUsed();

    unsigned short costRetreat();
    bool canRetreat();

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
    bool m_protectedAgainstDamageForTheNextTurn;
    bool m_protectedAgainstEffectForTheNextTurn;
    QList<AttackData> m_listAttacks;
    ModelListEnergies* m_modelListEnergies;
    CardPokemon* m_cardEvolution;
	short m_evolutionFrom;
    unsigned short m_costRetreat;

    unsigned short m_damageOfPoisonPerRound;
    AttackData m_lastAttackUsed;
	
    unsigned short currentDamage();
    void setDamage(unsigned short damage);
    QString statusToString(Enum_statusOfPokemon status);
};

#endif // CARDPOKEMON_H

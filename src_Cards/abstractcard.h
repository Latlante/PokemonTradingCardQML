#ifndef ABSTRACTCARD_H
#define ABSTRACTCARD_H

#include <QObject>
#include <QDebug>

class AbstractCard : public QObject
{
    Q_OBJECT
public:
	enum Enum_typeOfCard 
	{
		TypeOfCard_Pokemon = 0,
		TypeOfCard_Energy,
		TypeOfCard_Action
	};
	
	enum Enum_element
	{
		Element_Bug = 0,
		Element_Dark = 1,
		Element_Dragon = 2,
		Element_Electric = 3,
		Element_Fighting = 4,
		Element_Fire = 5,
		Element_Flying = 6,
		Element_Ghost = 7,
		Element_Grass = 8,
		Element_Ice = 9,
		Element_Normal = 10,		
		Element_Poison = 11,
		Element_Psychic = 12,
		Element_Rock = 13,
        Element_Water = 14,
        Element_COUNT
	};

    AbstractCard(unsigned short id, const QString& name);
    virtual ~AbstractCard();

    static void declareQML();
	
	virtual Enum_typeOfCard type() = 0;
    virtual QUrl image() = 0;
	
    int id();
	const QString name();
	void setName(const QString& name);

signals:
    void dataChanged();

protected:
	unsigned short m_id;
	QString m_name;
};

#endif // ABSTRACTCARD_H

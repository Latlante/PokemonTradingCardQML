#ifndef CARDENERGY_H
#define CARDENERGY_H

#include "abstractcard.h"

class CardEnergy : public AbstractCard
{
public:
    CardEnergy(unsigned short id, const QString& name, AbstractCard::Enum_element element, unsigned short quantity = 1);
    ~CardEnergy();

    static void declareQML();
	
    Q_INVOKABLE AbstractCard::Enum_typeOfCard type() override;
    Q_INVOKABLE QUrl image() override;

    Q_INVOKABLE AbstractCard::Enum_element element();
	void setElement(AbstractCard::Enum_element element);
    Q_INVOKABLE unsigned short quantity();
	void setQuantity(unsigned short quantity);

private:
	AbstractCard::Enum_element m_element;
	unsigned short m_quantity;
};

#endif // CARDENERGY_H

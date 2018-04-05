#ifndef CARDACTION_H
#define CARDACTION_H

#include "abstractcard.h"

class CardAction : public AbstractCard
{
public:
    CardAction(unsigned short id, const QString& name, const QString& description/*, AbstractAction* action*/);
    CardAction(const CardAction& card);
    ~CardAction();

    static void declareQML();
	
    AbstractCard::Enum_typeOfCard type() override;
    QUrl image() override;
    AbstractCard* clone() override;

	const QString description();
    //AbstractAction* action();
	
	void executeAction();

    CardAction& operator =(const CardAction& source);

private:
	QString m_description;
    //AbstractAction* m_action;
};

#endif // CARDACTION_H

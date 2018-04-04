#include "cardaction.h"
#include <QUrl>
#include <QtQml/qqml.h>

CardAction::CardAction(unsigned short id, const QString& name, const QString& description/*, AbstractAction* action*/) :
    AbstractCard(id, name),
    m_description(description)
    //m_action(action)
{
	
}

CardAction::~CardAction()
{
    //delete m_action;
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void CardAction::declareQML()
{
    qmlRegisterUncreatableType<CardAction>("model", 1, 0, "CardAction", "CardAction error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractCard::Enum_typeOfCard CardAction::type()
{
	return AbstractCard::TypeOfCard_Action;
}

QUrl CardAction::image()
{
    const QString path = "Images/cartes/dresseurs/" + QString::number(id()) + ".png";
    qDebug() << __PRETTY_FUNCTION__ << "path image:" << path;

    //return QPixmap(path);
    return QUrl::fromLocalFile(path);
}

const QString CardAction::description()
{
	return m_description;
}

/*AbstractAction* CardAction::action()
{
	return m_action;
}*/

void CardAction::executeAction()
{
    //m_action->execute();
}

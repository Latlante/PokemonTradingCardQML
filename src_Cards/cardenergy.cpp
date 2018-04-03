#include "cardenergy.h"
#include <QUrl>

CardEnergy::CardEnergy(unsigned short id, const QString& name, AbstractCard::Enum_element element, unsigned short quantity) :
    AbstractCard(id, name),
	m_element(element),
	m_quantity(quantity)
{
	
}

CardEnergy::~CardEnergy()
{
	
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
AbstractCard::Enum_typeOfCard CardEnergy::type()
{
    return AbstractCard::TypeOfCard_Energy;
}

QUrl CardEnergy::image()
{
    const QString path = "Images/cartes/energies/" + QString::number(static_cast<int>(element())) + ".png";
    qDebug() << __PRETTY_FUNCTION__ << "path image:" << path;

    //return QPixmap(path);
    return QUrl::fromLocalFile(path);
}

AbstractCard::Enum_element CardEnergy::element()
{
	return m_element;
}

void CardEnergy::setElement(AbstractCard::Enum_element element)
{
	m_element = element;
}

unsigned short CardEnergy::quantity()
{
	return m_quantity;
}

void CardEnergy::setQuantity(unsigned short quantity)
{
	m_quantity = quantity;
}

#include "abstractcard.h"
#include <QPixmap>

AbstractCard::AbstractCard(unsigned short id, const QString& name) :
    QObject(),
	m_id(id),
    m_name(name)
{
	
}

AbstractCard::~AbstractCard()
{
	
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
int AbstractCard::id()
{
    return m_id;
}

const QString AbstractCard::name()
{
	return m_name;
}

void AbstractCard::setName(const QString& name)
{
	m_name = name;
}

/*QUrl AbstractCard::image()
{
    const QString path = "Images/cartes/" + QString::number(id()) + ".png";
    qDebug() << __PRETTY_FUNCTION__ << "path image:" << path;

    //return QPixmap(path);
    return path;
}*/

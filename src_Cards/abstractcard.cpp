#include "abstractcard.h"
#include <QPixmap>
#include <QtQml/qqml.h>

#include "player.h"

AbstractCard::AbstractCard(unsigned short id, const QString& name) :
    QObject(),
    m_owner(nullptr),
	m_id(id),
    m_name(name)
{
	
}

AbstractCard::AbstractCard()
{
}

AbstractCard::~AbstractCard()
{
	
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void AbstractCard::declareQML()
{
    qmlRegisterUncreatableType<AbstractCard>("model", 1, 0, "AbstractCard", "AbstractCard error");
}

QString AbstractCard::imageByDefault()
{
    return "back.png";
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
Player* AbstractCard::owner()
{
    return m_owner;
}

void AbstractCard::setOwner(Player *play)
{
    m_owner = play;
}

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

QString AbstractCard::elementToString(Enum_element element)
{
    switch(element)
    {
    case Element_Bug:       return "Insecte";
    case Element_Dark:      return "Ombre";
    case Element_Dragon:    return "Dragon";
    case Element_Electric:  return "Electrique";
    case Element_Fighting:  return "Combat";
    case Element_Fire:      return "Feu";
    case Element_Flying:    return "Volant";
    case Element_Ghost:     return "Fantôme";
    case Element_Grass:     return "Plante";
    case Element_Ice:       return "Glace";
    case Element_Normal:    return "Normal";
    case Element_Poison:    return "Poison";
    case Element_Psychic:   return "Psy";
    case Element_Rock:      return "Pierre";
    case Element_Water:     return "Eau";
    }

    return "Erreur de type";
}

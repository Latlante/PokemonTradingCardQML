#include "factorymainpageloader.h"
#include <QtQml/qqml.h>

FactoryMainPageLoader::FactoryMainPageLoader(QObject *parent) :
    QObject(parent),
    m_link("")
{
    displaySelectPlayers();
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void FactoryMainPageLoader::declareQML()
{
    qmlRegisterUncreatableType<FactoryMainPageLoader>("model", 1, 0, "FactoryMainPageLoader", "FactoryMainPageLoader error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
QString FactoryMainPageLoader::link()
{
    return m_link;
}

void FactoryMainPageLoader::displaySelectPlayers()
{
    setLink("qrc:/SelectPlayers.qml");
}

void FactoryMainPageLoader::displaySelectCards()
{
    setLink("qrc:/SelectingCardsQML.qml");
}

void FactoryMainPageLoader::displayBoard()
{
    setLink("qrc:/BoardQML.qml");
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
void FactoryMainPageLoader::setLink(const QString &link)
{
    if(m_link != link)
    {
        m_link = link;
        emit linkChanged();
    }
}

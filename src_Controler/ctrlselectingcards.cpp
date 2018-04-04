#include "ctrlselectingcards.h"

#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#include <QtQml/qqml.h>

#include "src_Models/modelselectingcards.h"
#include "utils.h"

CtrlSelectingCards::CtrlSelectingCards(QObject *parent) :
    QObject(parent),
    m_modelSelectingCards(new ModelSelectingCards())
{

}

CtrlSelectingCards::~CtrlSelectingCards()
{
    if(m_modelSelectingCards != nullptr)
    {
        delete m_modelSelectingCards;
        m_modelSelectingCards = nullptr;
    }
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void CtrlSelectingCards::declareQML()
{
    qmlRegisterUncreatableType<CtrlSelectingCards>("model", 1, 0, "CtrlSelectingCards", "CtrlSelectingCards error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
void CtrlSelectingCards::setName(const QString &name)
{
    m_modelSelectingCards->setName(name);
}

bool CtrlSelectingCards::install(QQmlApplicationEngine *pEngine)
{
    qDebug() << "installing controleur...";

    bool bInstalled = false;

    if (NULL != pEngine)
    {
        QQmlContext* pContext = pEngine->rootContext();
        if (NULL != pContext)
        {
            bInstalled = true;
            qDebug() << "CtrlSelectingCards is installed in QML engine";
            pContext->setContextProperty("ctrlSelectingCards", this);
        }
        else
        {
            qCritical() << "Qml context is null.";
        }
    }

    return bInstalled;
}

ModelSelectingCards* CtrlSelectingCards::model()
{
    return m_modelSelectingCards;
}

void CtrlSelectingCards::addANewCard(int id)
{
    changeQuantityCard(id, m_modelSelectingCards->rowCountById(id)+1);
}

void CtrlSelectingCards::removeACard(int id)
{
    changeQuantityCard(id, m_modelSelectingCards->rowCountById(id)-1);
}

void CtrlSelectingCards::changeQuantityCard(int id, int quantity)
{
    m_modelSelectingCards->changeQuantityCard(id, quantity);
}

void CtrlSelectingCards::fillARandomList()
{
    int rowCount = m_modelSelectingCards->rowCount();

    for(int i=0;i<40;++i)
    {
        int randomId = Utils::randomValue(0, rowCount);
        addANewCard(randomId);
    }
}

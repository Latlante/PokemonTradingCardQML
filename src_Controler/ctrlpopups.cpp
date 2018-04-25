#include "ctrlpopups.h"

#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#include <QtQml/qqml.h>

#include "src_Cards/abstractcard.h"
#include "src_Models/modelpopupselectcardinpacket.h"
#include "src_Packets/abstractpacket.h"
#include "src_Packets/bencharea.h"

CtrlPopups::CtrlPopups(QObject *parent) :
    QObject(parent),
    m_modelPopups(new ModelPopupSelectCardInPacket()),
    m_visible(false)
{

}

CtrlPopups::~CtrlPopups()
{
    delete m_modelPopups;
}

/************************************************************
*****				FONCTIONS STATIQUES					*****
************************************************************/
void CtrlPopups::declareQML()
{
    qmlRegisterUncreatableType<CtrlPopups>("model", 1, 0, "CtrlPopups", "CtrlPopups error");
}

/************************************************************
*****				FONCTIONS PUBLIQUES					*****
************************************************************/
bool CtrlPopups::install(QQmlApplicationEngine *pEngine)
{
    qDebug() << "installing CtrlPopups...";

    bool bInstalled = false;

    if (NULL != pEngine)
    {
        QQmlContext* pContext = pEngine->rootContext();
        if (NULL != pContext)
        {
            bInstalled = true;
            qDebug() << "CtrlPopups is installed in QML engine";
            pContext->setContextProperty("ctrlPopups", this);
        }
        else
        {
            qCritical() << "Qml context is null.";
        }
    }

    return bInstalled;
}

ModelPopupSelectCardInPacket* CtrlPopups::model()
{
    return m_modelPopups;
}

bool CtrlPopups::visible()
{
    return m_visible;
}

void CtrlPopups::setVisible(bool state)
{
    if(m_visible != state)
    {
        m_visible = state;
        emit visibleChanged();
    }
}

void CtrlPopups::displayBench(BenchArea *packet)
{
    m_modelPopups->addPacketFromAbstractPacket(packet);

    setVisible(true);
}

#include "ctrlpopups.h"

#include <QDebug>
#include <QEventLoop>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml/qqml.h>

#include "src_Cards/abstractcard.h"
#include "src_Models/modelpopupselectcardinpacket.h"
#include "src_Packets/abstractpacket.h"
#include "src_Packets/bencharea.h"
#include "src_Packets/packetdeck.h"
#include "src_Packets/packethand.h"

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

QList<int> CtrlPopups::displayBench(BenchArea *packet)
{
    return displayAbstractPacket(packet);
}

QList<int> CtrlPopups::displayDeck(PacketDeck *packet)
{
    return displayAbstractPacket(packet);
}

QList<int> CtrlPopups::displayHand(PacketHand *packet)
{
    return displayAbstractPacket(packet);
}

void CtrlPopups::selectionCardsFinished()
{
    setVisible(false);
    emit selectionFinished();
}

/************************************************************
*****				FONCTIONS PRIVEES					*****
************************************************************/
QList<int> CtrlPopups::displayAbstractPacket(AbstractPacket *packet)
{
    m_modelPopups->addPacketFromAbstractPacket(packet);

    setVisible(true);

    qDebug() << __PRETTY_FUNCTION__ << "En attente";

    QEventLoop loop;
    connect(this, &CtrlPopups::selectionFinished, &loop, &QEventLoop::quit);
    loop.exec();

    qDebug() << __PRETTY_FUNCTION__ << "Popup closed";

    return m_modelPopups->listIndexCardsSelected();
}

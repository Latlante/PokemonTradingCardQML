#include "testsunitaires.h"


TestsUnitaires::TestsUnitaires() : QObject()
{

}


/************************************************************
*****				FONCTIONS PROTEGEES					*****
************************************************************/
const char *TestsUnitaires::messageToDisplayInConsole(const char *nameVar, QVariant arg1, QVariant arg2)
{
    QString message = "ERROR: " + QString::fromUtf8(nameVar) + " => \"";

    switch(arg1.type())
    {
    case QVariant::Bool:
        message += (arg1.toBool() == true) ? "true" : "false";
        break;
    case QVariant::Int:
        message += QString::number(arg1.toInt());
        break;
    case QVariant::UInt:
        message += QString::number(arg1.toUInt());
        break;
    case QVariant::String:
        message += arg1.toString();
        break;
    default:
        qCritical() << "Type arg1 inconnue:" << arg1.type();
    }

    message += "\" <!=> \"";

    switch(arg2.type())
    {
    case QVariant::Bool:
        message += (arg2.toBool() == true) ? "true" : "false";
        break;
    case QVariant::Int:
        message += QString::number(arg2.toInt());
        break;
    case QVariant::UInt:
        message += QString::number(arg2.toUInt());
        break;
    case QVariant::String:
        message += arg2.toString();
        break;
    default:
        qCritical() << "Type arg2 inconnue:" << arg2.type();
    }

    message += "\"";

    QByteArray messageArray = message.toUtf8();
    //const char* messageChar = messageArray.constData();
    //char* test = messageArray.data();

    qCritical() << message;

    return "e";
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "src_Models/factorymainpageloader.h"
#include "src_Controler/ctrlgameboard.h"
#include "src_Models/listplayers.h"
#include "player.h"
#include "src_Packets/bencharea.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packetdeck.h"
#include "src_Packets/packethand.h"
#include "src_Packets/packetrewards.h"
#include "src_Packets/packettrash.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    FactoryMainPageLoader::declareQML();
    CtrlGameBoard::declareQML();
    ListPlayers::declareQML();
    Player::declareQML();
    BenchArea::declareQML();
    PacketDeck::declareQML();
    PacketHand::declareQML();
    PacketRewards::declareQML();
    PacketTrash::declareQML();

    QQmlApplicationEngine engine;
    CtrlGameBoard controler;
    controler.install(&engine);

    const QUrl mainQml(QStringLiteral("qrc:/main.qml"));

    // Catch the objectCreated signal, so that we can determine if the root component was loaded
    // successfully. If not, then the object created from it will be null. The root component may
    // get loaded asynchronously.
    const QMetaObject::Connection connection = QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated,
                &app, [&](QObject *object, const QUrl &url) {
            if (url != mainQml)
            return;

            if (!object)
            app.exit(-1);
            else
            QObject::disconnect(connection);
}, Qt::QueuedConnection);

    engine.load(mainQml);

    return app.exec();
}

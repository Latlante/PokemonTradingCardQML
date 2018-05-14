#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QResource>
#include "common/constantesqml.h"
#include "src_Models/factorymainpageloader.h"
#include "src_Controler/ctrlgameboard.h"
#include "src_Controler/ctrlpopups.h"
#include "src_Controler/ctrlselectingcards.h"
#include "src_Models/listplayers.h"
#include "src_Models/modellistenergies.h"
#include "src_Models/modelpopupselectcardinpacket.h"
#include "src_Models/modelpopupselectenergyinpokemon.h"
#include "src_Models/modelselectingcards.h"
#include "player.h"
#include "src_Cards/abstractcard.h"
#include "src_Cards/cardaction.h"
#include "src_Cards/cardenergy.h"
#include "src_Cards/cardpokemon.h"
#include "src_Packets/bencharea.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packetdeck.h"
#include "src_Packets/fightarea.h"
#include "src_Packets/packethand.h"
#include "src_Packets/packetrewards.h"
#include "src_Packets/packettrash.h"

#ifdef TESTS_UNITAIRES
#include "src_Tests/testsunitairegeneral.h"
#include "src_Tests/testsunitaireactions.h"
#endif

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //QResource::registerResource("Ressources/pokemon.rcc");
    //QResource::registerResource("Ressources/energies.rcc");
    QResource::registerResource("Ressources/cards.rcc");

#ifdef TESTS_UNITAIRES
    GameManager::createInstance();
    TestsUnitaireGeneral testGeneral;
    TestsUnitaireActions testAction;
    return 0;
#endif

    ConstantesQML::declareQML();
    FactoryMainPageLoader::declareQML();
    CtrlGameBoard::declareQML();
    CtrlPopups::declareQML();
    CtrlSelectingCards::declareQML();
    ListPlayers::declareQML();
    ModelListEnergies::declareQML();
    ModelPopupSelectCardInPacket::declareQML();
    ModelPopupSelectEnergyInPokemon::declareQML();
    ModelSelectingCards::declareQML();
    Player::declareQML();
    AbstractCard::declareQML();
    CardAction::declareQML();
    CardEnergy::declareQML();
    CardPokemon::declareQML();
    BenchArea::declareQML();
    PacketDeck::declareQML();
    FightArea::declareQML();
    PacketHand::declareQML();
    PacketRewards::declareQML();
    PacketTrash::declareQML();

    Utils::initRandomValues();

    QQmlApplicationEngine engine;
    CtrlSelectingCards ctrlSC;
    CtrlPopups ctrlPopups;
    CtrlGameBoard ctrlGB(ctrlSC, ctrlPopups);
    ctrlGB.install(&engine);
    ctrlPopups.install(&engine);
    ctrlSC.install(&engine);

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

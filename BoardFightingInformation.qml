import QtQuick 2.0
import QtQuick.Controls 2.2
import model 1.0

Item {
    id: boardFightingInfo1
    width: 500
    height: 600

    property Player player
    property Player currentPlayer
    property CardPokemon cardPok: player.fight().pokemonFighter

    onPlayerChanged: {
        console.log("onPlayerChanged");
        /*if(player !== undefined)
        {
            console.log("onPlayerChanged: player not null");
            var cardPokemon = player.fight().pokemonFighting(0);

            pokemonFighting.source = cardPokemon.image();
            textNamePokemon.text = cardPokemon.name();
            textLifePokemon.text = cardPokemon.lifeLeft + "/" + cardPokemon.lifeTotal() + " PV"
            gridViewEnergies.model = cardPokemon.modelListOfEnergies();
        }
        else
        {
            console.log("onPlayerChanged: player is null");
            pokemonFighting.source = "back.png"
        }*/
    }

    onCardPokChanged: {
        console.log("onCardPokChanged");
        if(cardPok !== undefined)
        {
            console.log("onPlayerChanged: player not null");
            //var cardPokemon = player.fight().pokemonFighting(0);

            pokemonFighting.source = cardPok.image();
            textNamePokemon.text = cardPok.name();
            textStatusPokemon.text = cardPok.status;
            textLifePokemon.text = cardPok.lifeLeft + "/" + cardPok.lifeTotal() + " PV"
            gridViewEnergies.model = cardPok.modelListOfEnergies();
        }
        else
        {
            console.log("onPlayerChanged: player is null");
            pokemonFighting.source = "back.png"
        }
    }

    Rectangle {
        id: rectangleFightingArea
        anchors.fill: parent
        color: "#00000000"
        border.color: "red"
        border.width: 3

        Image {
            id: pokemonFighting
            x: 295
            width: (2./5.) * parent.width
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            fillMode: Image.PreserveAspectFit
            //source: cardPok.cardImage
        }

        /*ListView {
            id: listViewPokemonFighting
            width: (2./5.) * parent.width
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            model: player.fight()
            delegate:
                Item {
                    width: listViewPokemonFighting.width
                    height: listViewPokemonFighting.height

                    Image {
                        anchors.fill: parent
                        source: model.imageCard
                        fillMode: Image.PreserveAspectFit
                    }
                }
        }*/


        Rectangle {
            id: rectangleContainerInformation

            property int heightLines: 50
            property int pixelSize: heightLines - 10

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: pokemonFighting.left
            anchors.bottom: parent.bottom
            color: "transparent"
            border.color: "black"
            border.width: 3

            Text {
                id: textNamePokemon
                height: rectangleContainerInformation.heightLines
                //text: qsTr("Pokemon")
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                font.family: "Times New Roman"
                font.pixelSize: rectangleContainerInformation.pixelSize
            }

            Text {
                id: textLifePokemon
                height: rectangleContainerInformation.heightLines
                //text: cardPok.lifeLeft + "/" + cardPok.lifeTotal() + " PV"
                anchors.top: textNamePokemon.bottom
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.right: parent.right
                anchors.rightMargin: 0
                font.pixelSize: rectangleContainerInformation.pixelSize
                font.family: "Times New Roman"
            }

            Text {
                id: textStatusPokemon
                height: rectangleContainerInformation.heightLines
                anchors.top: textLifePokemon.bottom
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.right: parent.right
                anchors.rightMargin: 0
                font.pixelSize: rectangleContainerInformation.pixelSize
                font.family: "Times New Roman"
            }

            GridView {
                id: gridViewEnergies
                interactive: false
                anchors.top: textStatusPokemon.bottom
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.bottom: buttonAttack.top
                //model: cardPok.modelListOfEnergies()
                cellWidth: 25
                cellHeight: 25
                delegate:
                    Item {
                        width: 25
                        height: 25

                        Image {
                            id: imageModelIcon
                            anchors.fill: parent
                            source: model.icon
                        }
                }
            }

            Button {
                id: buttonAttack
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                //enabled:
                visible: player === currentPlayer

                text: "Attaquer"

                onClicked: ctrlGameBoard.onClicked_ButtonAttack()
            }
        }


    }
}

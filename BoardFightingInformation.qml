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
    property int pokemonLifeLeft: cardPok.lifeLeft
    property int pokemonStatus: cardPok.status

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

    onPokemonLifeLeftChanged: {
        console.log("onPokemonLifeLeftChanged");
        textLifePokemon.text = pokemonLifeLeft + "/" + cardPok.lifeTotal() + " PV"
    }

    onPokemonStatusChanged: {
        console.log("onPokemonStatusChanged");
        textStatusPokemon.text = cardPok.statusFormatString();
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
            //pokemonLifeLeft = cardPok.lifeLeft
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

            MouseArea {
                id: mouseAreaCardFighter
                anchors.fill: parent
                onClicked: {
                    if(cardPok !== undefined)
                    {
                        popupCardDetailsComplete1.card = cardPok;
                        popupCardDetailsComplete1.visible = true;
                    }
                }

                onPressAndHold: {
                    if((cardPok !== undefined) &&
                            (player === currentPlayer) &&
                            (ctrlGameBoard.gameStatus === ConstantesQML.StepGameInProgress))
                    {
                        popupPokemonSelectingAttack1.card = cardPok;
                        popupPokemonSelectingAttack1.visible = true;
                    }
                }
            }

            DropArea {
                id: dropAreaFightingArea
                anchors.fill: parent
                onEntered: console.log("dropAreaFightingArea entered");
                onExited: console.log("dropAreaFightingArea exited");
                onDropped: {
                    console.log("DropArea in fightingArea");
                    console.log("drag.source: " + drag.source.parent.objectName);
                    //Si ca vient du banc
                    if((drag.source.parent.player === boardFightingInfo1.player) &&
                            (drag.source.objectName === "itemDelegatePacketBench"))
                    {
                        console.log("DropArea from bench");
                        //boardFightingInfo1.player.moveCardFromBenchToFight(drag.source.parent.listViewPacketBench.dragItemIndex);
                        //drag.source.parent.listViewPacketBench.dragItemIndex = -1;
                    }
                    //Ca vient de la main
                    else if((drag.source.parent.player === boardFightingInfo1.player) &&
                            (drag.source.objectName === "imageCardInHand"))
                    {
                        console.log("DropArea from hand, " + drag.source.parent.objectName);
                        //boardFightingInfo1.player.moveCardFromHandToFight(drag.source.parent.listViewPacketHand.dragItemIndex);
                        //drag.source.parent.listViewPacketHand.dragItemIndex = -1;
                    }

                    /*if((boardPlayer1.listViewPacketBench.dragItemIndex !== -1) &&
                            (boardPlayer1.player === boardFightingInfo1.player))
                    {
                        console.log("DropArea from bench");
                        player.moveCardFromBenchToFight()
                    }
                    if((boardPlayer1.listViewPacketBench.dragItemIndex !== -1) &&
                            (boardPlayer1.player === boardFightingInfo1.player))
                    {
                        listView.model.append(listView3.model.get(listView3.dragItemIndex))
                        listView3.model.remove(listView3.dragItemIndex)
                        listView3.dragItemIndex = -1;
                    }*/
                }
            }
        }

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

            /*Button {
                id: buttonAttack
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                //enabled:
                visible: player === currentPlayer

                text: "Attaquer"

                onClicked: ctrlGameBoard.onClicked_ButtonAttack(0)
            }*/

            Button {
                id: buttonReadyPreparation
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                visible: ctrlGameBoard.gameStatus === ConstantesQML.StepPreparation

                text: "Prêt"

                onClicked: ctrlGameBoard.onClicked_ButtonReadyPreparation()
            }
        }


    }
}

import QtQuick 2.0
import model 1.0

Item {
    id: board1
    visible: true
    width: 1200
    height: 1920
    //property PacketDeck deckP1: ctrlGameBoard.deck_P1()
    //property PacketDeck deckP2
    property Player play1: ctrlGameBoard.playerAt(0)
    //property PacketDeck deckP1: play1.deck()
    //property PacketDeck deckP1: ctrlGameBoard.deck_P1()

    Component.onCompleted: {
        /*var play1 = ctrlGameBoard.createPlayer("Corentin");
        deckP1 = play1.deck();

        var play2 = ctrlGameBoard.createPlayer("Alice");
        deckP2 = play2.deck();

        console.log("QML: deck1" + deckP1.countCard + ", deck2:" + deckP2.countCard);
*/
        //ctrlGameBoard.initGame();
    }

    Image {
        id: imageBackground
        fillMode: Image.Tile
        anchors.fill: parent
        source: "qrc:/textures/tapis.jpg"

        //ZONE DE JOUEUR 2
        ListView {
            id: listViewPacketHand_P2
            x: 5
            width: 110
            height: 160
            rotation: 180
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            contentWidth: 320
            anchors.leftMargin: 0
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
            anchors.rightMargin: 0
            orientation: ListView.Horizontal
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row4
                    spacing: 10
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                }
            }
        }

        ListView {
            id: listViewPacketBench_P2
            x: -7
            y: 395
            width: 787
            height: 160
            rotation: 180
            anchors.left: parent.left
            anchors.bottom: rectangleInfosPackets_P2.top
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.topMargin: 0
            //model: ctrlGameBoard.benchArea_P1()
            anchors.rightMargin: 0
            orientation: ListView.Horizontal
            anchors.bottomMargin: 0
            anchors.top: listViewPacketHand_P2.bottom
            delegate: Image {
                width: 100
                height: parent.height
                source: image;
            }
        }

        Rectangle {
            id: rectangleInfosPackets_P2
            x: 4
            y: -4
            height: 50
            color: "#00000000"
            anchors.bottom: rectangleFightingArea.top
            anchors.bottomMargin: 0
            rotation: 180
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            border.width: 4
            Text {
                id: textDeckCst_P2
                width: 80
                height: 45
                text: qsTr("Deck:")
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.leftMargin: 10
                font.pixelSize: 30
                anchors.topMargin: 0
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 0
                anchors.top: parent.top
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }

            Text {
                id: textDeck_P2
                width: 50
                //text: deckP2.countCard
                anchors.left: textDeckCst_P2.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 0
                font.pixelSize: 30
                anchors.topMargin: 0
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 0
                anchors.top: parent.top
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }

            Text {
                id: textTrashCst_P2
                width: 92
                height: 45
                text: qsTr("Trash:")
                anchors.left: textDeck_P2.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 30
                font.pixelSize: 30
                anchors.topMargin: 0
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 0
                anchors.top: parent.top
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }

            Text {
                id: textTrash_P2
                width: 50
                text: qsTr("0")
                anchors.left: textTrashCst_P2.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 0
                font.pixelSize: 30
                anchors.topMargin: 0
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 0
                anchors.top: parent.top
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }

            Text {
                id: textRewardsCst_P2
                width: 144
                height: 45
                text: qsTr("Rewards:")
                anchors.left: textTrash_P2.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 30
                font.pixelSize: 30
                anchors.topMargin: 0
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 0
                anchors.top: parent.top
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }

            Text {
                id: textRewards_P2
                width: 50
                text: qsTr("0")
                anchors.left: textRewardsCst_P2.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 0
                font.pixelSize: 30
                anchors.topMargin: 0
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 0
                anchors.top: parent.top
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }
        }

        //ZONE DE COMBAT CENTRALE
        Rectangle {
            id: rectangleFightingArea
            y: 685
            height: 300
            color: "#00000000"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.verticalCenter: parent.verticalCenter
            border.width: 7
            border.color: "#000000"

            Image {
                id: pokemonFighting_P1
                x: 295
                width: 300
                anchors.top: textNamePlayer1.bottom
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -width/2 - 5
                source: "back.png"
            }

            Image {
                id: pokemonFighting_P2
                x: 601
                width: 300
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: width/2 + 5
                rotation: 180
                source: "back.png"
            }

            Text {
                id: textNamePlayer1
                height: 70
                text: qsTr("Player 1")
                anchors.right: parent.right
                anchors.rightMargin: parent.width / 2
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                font.pixelSize: 60
            }

            Text {
                id: textNamePokemonP1
                height: 70
                text: qsTr("Pokemon")
                anchors.right: pokemonFighting_P1.left
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: textNamePlayer1.bottom
                anchors.topMargin: 0
                font.family: "Times New Roman"
                font.pixelSize: 50
            }

            Text {
                id: textLifePokemonP1
                x: 6
                y: 215
                height: 70
                text: qsTr("100 / 120 PV")
                anchors.top: textNamePokemonP1.bottom
                anchors.leftMargin: 8
                font.family: "Times New Roman"
                anchors.left: parent.left
                anchors.rightMargin: 0
                font.pixelSize: 50
                anchors.topMargin: 0
                anchors.right: pokemonFighting_P1.left
            }

            GridView {
                id: gridViewEnergies_P1
                interactive: false
                anchors.rightMargin: 0
                anchors.top: textLifePokemonP1.bottom
                anchors.right: pokemonFighting_P1.left
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.topMargin: 0
                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                    }

                    ListElement {
                        name: "Red"
                        colorCode: "red"
                    }

                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                    }

                    ListElement {
                        name: "Green"
                        colorCode: "green"
                    }
                }
                cellHeight: 70
                delegate: Item {
                    x: 5
                    height: 50
                    Column {
                        spacing: 5
                        Rectangle {
                            width: 40
                            height: 40
                            color: colorCode
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Text {
                            x: 5
                            text: name
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }
                cellWidth: 70
            }
        }

        //ZONE DE JOUEUR 1
        Rectangle {
            id: rectangleInfosPackets_P1
            height: 50
            color: "#00000000"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: rectangleFightingArea.bottom
            anchors.topMargin: 0
            border.width: 4

            Text {
                id: textDeckCst_P1
                width: 80
                height: 45
                text: qsTr("Deck:")
                verticalAlignment: Text.AlignVCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 10
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
                font.pixelSize: 30
            }

            Text {
                id: textDeck_P1
                width: 50
                text: play1.deck().countCard
                verticalAlignment: Text.AlignVCenter
                anchors.left: textDeckCst_P1.right
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                font.pixelSize: 30
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }

            Text {
                id: textTrashCst_P1
                width: 92
                height: 45
                text: qsTr("Trash:")
                verticalAlignment: Text.AlignVCenter
                anchors.left: textDeck_P1.right
                anchors.leftMargin: 30
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                font.pixelSize: 30
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }

            Text {
                id: textTrash_P1
                width: 50
                text: play1.trash().countCard
                verticalAlignment: Text.AlignVCenter
                anchors.left: textTrashCst_P1.right
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                font.pixelSize: 30
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }

            Text {
                id: textRewardsCst_P1
                width: 144
                height: 45
                text: qsTr("Rewards:")
                verticalAlignment: Text.AlignVCenter
                anchors.left: textTrash_P1.right
                anchors.leftMargin: 30
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                font.pixelSize: 30
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }

            Text {
                id: textRewards_P1
                width: 50
                text: play1.rewards().countCard
                verticalAlignment: Text.AlignVCenter
                anchors.left: textRewardsCst_P1.right
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                font.pixelSize: 30
                fontSizeMode: Text.HorizontalFit
                renderType: Text.NativeRendering
            }
        }

        ListView {
            id: listViewPacketBench_P1
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: listViewPacketHand_P1.top
            anchors.bottomMargin: 0
            anchors.top: rectangleInfosPackets_P1.bottom
            anchors.topMargin: 0
            orientation: ListView.Horizontal
            model: play1.bench()
            delegate: model.isCard === true ? componentDelegateCardBench : componentDelegateCardEmptyBench
                /*{
                if(model.isCard === true)
                    return componentDelegateCardBench;
                else
                    return componentDelegateCardEmptyBench;
            }*/


            Component{
                id: componentDelegateCardBench
                Item {
                    id: itemDelegatePacketBench
                    x: 5
                    width: 80
                    height: 120

                    Image {
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: listViewEnergiesByCard.top
                        source: model.imageCard
                        fillMode: Image.PreserveAspectFit

                        MouseArea {
                            id: mouseAreaCardBench
                            anchors.fill: parent
                            onClicked: {
                                if(model.card !== undefined)
                                {
                                    popupCardDetailsComplete1.card = model.card;
                                    popupCardDetailsComplete1.visible = true;
                                }
                            }
                        }
                    }


                    ListView {
                        id: listViewEnergiesByCard
                        height: 25
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        orientation: ListView.Horizontal
                        interactive: false

                        model: listViewPacketBench_P1.model.modelFromCardPokemon(index)
                        //model: ctrlGameBoard.newListEnergies()
                        delegate:
                            Item {
                            width: 25
                            height: 25

                            Image {
                                id: imageIconEnergy
                                anchors.fill: parent
                                source: model.icon
                            }
                        }

                        Component.onCompleted: console.log("listViewEnergiesByCard is created");
                    }
                }
            }

            Component {
                id: componentDelegateCardEmptyBench
                Item {
                    id: itemDelegatePacketBench
                    x: 5
                    width: 80
                    height: 120

                    Image {
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: rectangleEmptyBarCardEmptyBench.top
                        source: model.imageCard
                        fillMode: Image.PreserveAspectFit
                    }

                    Rectangle {
                        id: rectangleEmptyBarCardEmptyBench
                        height: 25
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        color: "green"
                    }
                }
            }

            DropArea {
                id: dropAreaBench
                anchors.fill: parent
                onDropped: {
                    console.log("onDropped");
                    //listView2.model.append(listView.model.get(listView.dragItemIndex))
                    //listView.model.remove(listView.dragItemIndex)
                    play1.moveCardFromHandToBench(listViewPacketHand_P1.dragItemIndex, 0);
                    listViewPacketHand_P1.dragItemIndex = -1;
                }
            }
        }

        ListView {
            property int dragItemIndex: -1

            id: listViewPacketHand_P1
            y: 1728
            width: 110
            height: 80
            contentWidth: 320
            orientation: ListView.Horizontal
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            model: play1.hand()
            delegate: Item {
                width: 80
                height: 160

                Image {
                    id: imageCardInHand
                    width: 120
                    height: 160
                    source: model.imageCard
                    fillMode: Image.PreserveAspectFit

                    MouseArea {
                        id: mouseAreaCardHand
                        anchors.fill: parent
                        drag.target: imageCardInHand

                        drag.onActiveChanged: {
                            if (mouseAreaCardHand.drag.active) {
                                listViewPacketHand_P1.dragItemIndex = index;
                            }
                            imageCardInHand.Drag.drop();
                        }

                        /*onPressAndHold: {
                            popupCardDetailsBasic1.card = model.card;
                            popupCardDetailsBasic1.visible = true;
                        }*/
                    }

                    states: [
                        State {
                            when: imageCardInHand.Drag.active
                            ParentChange {
                                target: imageCardInHand
                                parent: board1
                            }

                            AnchorChanges {
                                target: imageCardInHand
                                anchors.horizontalCenter: undefined
                                anchors.verticalCenter: undefined
                            }
                        }
                    ]

                    Drag.active: mouseAreaCardHand.drag.active
                    Drag.hotSpot.x: imageCardInHand.width / 2
                    Drag.hotSpot.y: imageCardInHand.height / 2
                }
            }
        }

        //POP-UPS
        PopupCardDetailsBasic {
            id: popupCardDetailsBasic1
            anchors.fill: parent
            visible: false
        }

        PopupCardDetailsComplete {
            id: popupCardDetailsComplete1
            anchors.fill: parent
            visible: false
        }
    }
}


import QtQuick 2.0
import model 1.0

Item {
    id: board1
    visible: true
    width: 1200
    height: 1920

    property Player play1: ctrlGameBoard.playerAt(0)
    property Player play2: ctrlGameBoard.playerAt(1)

    Image {
        id: imageBackground
        fillMode: Image.Tile
        anchors.fill: parent
        source: "qrc:/textures/tapis.jpg"

        //ZONE DE JOUEUR 2
        BoardPLayerAreaQML {
            id: boardPlayer2
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: rectangleFightingArea.top
            rotation: 180

            player: play2
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
        BoardPLayerAreaQML {
            id: boardPlayer1
            anchors.top: rectangleFightingArea.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            player: play1
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


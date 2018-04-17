import QtQuick 2.0
import model 1.0

Item {
    id: popupPokemonSelectingAttack1

    property CardPokemon card

    signal clickedAttack(int index)
    //signal clickedAttack2
    //signal clickedAttack3

    width: 1000
    height: 1000

    Rectangle {
        id: background
        anchors.fill: parent

        color: "#AAAAAAAA"

        Image {
            id: imageCard
            anchors.fill: parent

            fillMode: Image.Pad
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            //source: card.image
            source: "Images/cartes/pokemon/1.png"

            Rectangle {
                id: rectangleAttack1
                width: imageCard.paintedWidth
                height: 120 / card.attacksCount()
                color: "transparent"
                anchors.verticalCenterOffset: 102
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                border.color: "steelblue"
                border.width: 3

                MouseArea {
                    id: mouseAreaAttack1
                    anchors.fill: parent

                    onClicked: popupPokemonSelectingAttack1.clickedAttack(0)
                }
            }

            Rectangle {
                id: rectangleAttack2
                width: imageCard.paintedWidth
                height: 120 / card.attacksCount()
                color: "transparent"
                anchors.top: rectangleAttack1.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                border.color: "black"
                border.width: 3
                visible: card.attacksCount() >= 2

                MouseArea {
                    id: mouseAreaAttack2
                    anchors.fill: parent

                    onClicked: popupPokemonSelectingAttack1.clickedAttack(1)
                }
            }

            Rectangle {
                id: rectangleAttack3
                width: imageCard.paintedWidth
                height: 120 / card.attacksCount()
                color: "transparent"
                anchors.top: rectangleAttack2.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                border.color: "red"
                border.width: 3
                visible: card.attacksCount() >= 3

                MouseArea {
                    id: mouseAreaAttack3
                    anchors.fill: parent

                    onClicked: popupPokemonSelectingAttack1.clickedAttack(2)
                }
            }


        }
    }
}

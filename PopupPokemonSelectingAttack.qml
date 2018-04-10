import QtQuick 2.0
import model 1.0

Item {
    id: popupPokemonSelectingAttack1

    property CardPokemon card

    signal clickedAttack1

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

            MouseArea {
                id: mouseArea
                x: 334
                y: 535
                width: imageCard.paintedWidth
                height: 127

                onClicked: popupPokemonSelectingAttack1.clickedAttack1()
            }
        }
    }
}

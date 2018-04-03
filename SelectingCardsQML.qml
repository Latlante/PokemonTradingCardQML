import QtQuick 2.0
import QtQuick.Controls 2.2
import model 1.0

Item {
    id: selectCards1
    width: 500
    height: 900

    property int colCount: 4
    property int space: 4   //PAS DE NOMBRE IMPAIRE

    Rectangle {
        id: background
        anchors.fill: parent
        color: "white"

        Text {
            id: namePlayer
            height: 40
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 35
            text: "Player 1"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        GridView {
            id: viewCards
            anchors.top: namePlayer.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: buttonRandom.top
            anchors.bottomMargin: 10
            cellWidth: (viewCards.width-selectCards1.space)/selectCards1.colCount
            cellHeight: cellWidth*2

            model: ctrlSelectingCards.model()
            delegate: Item {
                id: itemCard
                anchors.fill: parent

                Image {
                    id: imageCard
                    anchors.fill: parent
                    source: model.imageCard
                }
            }

        }

        Button {
            id: buttonRandom
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: buttonOk.top
            anchors.bottomMargin: 10

            onClicked: ctrlSelectingCards.fillARandomList()
        }

        Button {
            id: buttonOk
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            onClicked: ctrlGameBoard.onClicked_ButtonOk_SelectCards()
        }
    }
}

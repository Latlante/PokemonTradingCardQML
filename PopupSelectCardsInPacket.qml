import QtQuick 2.0
import QtQuick.Controls 2.2
import model 1.0

Item {
    id: popupSelectCardsInPacket1
    width: 500
    height: 900

    property int cardsToSelect: 1
    //property alias modelOfCards: viewCards.model

    property int colCount: 4
    property int space: 4   //PAS DE NOMBRE IMPAIRE

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#AAAAAAAA"

        Text {
            id: title
            height: 40
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 35
            //text: viewCards.model.name + " (" + viewCards.model.countTotalQuantity + " / " + viewCards.model.maxCards() + ")"
            text: "Test"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        GridView {
            id: viewCards
            anchors.top: title.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: buttonOk.top
            anchors.bottomMargin: 10
            cellWidth: 160
            cellHeight: 270
            clip: true

            model: ctrlPopups.model()
            delegate: Item {
                id: itemCard
                //anchors.fill: parent
                width: 150
                height: 240

                Rectangle {
                    id: rectangleContainerImageCard
                    anchors.fill: parent

                    color: model.selected ? "#2b95ff" : "transparent"

                    Image {
                        id: imageCard
                        anchors.fill: parent
                        anchors.margins: 3
                        fillMode: Image.PreserveAspectFit
                        source: model.imageCard

                        MouseArea {
                            id: mouseAreaCard
                            anchors.fill: parent
                            onClicked: {
                                model.selected = !model.selected
                            }
                        }
                    }
                }
            }
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
            text: "OK"

            onClicked: ctrlPopups.visible = false
        }
    }
}

import QtQuick 2.0
import QtQuick.Controls 2.3
import model 1.0

Item {

    Rectangle {
        id: rectangle
        color: "#bbbbbb"
        anchors.fill: parent

        Text {
            id: title
            color: "#000000"
            text: qsTr("List of players")
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 20
        }

        Rectangle {
            id: rectangleContainerListView
            color: "#ffffff"
            border.width: 3
            anchors.rightMargin: 20
            anchors.leftMargin: 20
            anchors.bottomMargin: 10
            anchors.top: title.bottom
            anchors.right: parent.right
            anchors.bottom: buttonAddNewPlyer.top
            anchors.left: parent.left
            anchors.topMargin: 10

            ListView {
                id: listView
                anchors.fill: parent
                model: ctrlGameBoard.newListPlayers()
                delegate: Rectangle {
                    /*anchors.left: parent.left
                    anchors.right: parent.right*/
                    width: 200
                    height: 40
                    color: "#CCCCCC"

                    Text {
                        anchors.fill: parent
                        font.pixelSize: 35
                        text: model.name
                    }
                }
            }
        }

        Button {
            id: buttonAddNewPlyer
            width: (parent.width / 2) - 20
            text: qsTr("Ajouter un nouveau joueur")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: buttonValidate.top
            anchors.bottomMargin: 10

            onClicked: listView.model.addNewPlayer()
        }

        Button {
            id: buttonRemoveOnePlayer
            y: 400
            text: qsTr("Supprimer un joueur")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: buttonAddNewPlyer.right
            anchors.leftMargin: 10
            anchors.bottom: buttonValidate.top
            anchors.bottomMargin: 10

            onClicked: listView.model.removeOnePlayer()
        }

        Button {
            id: buttonValidate
            x: 20
            y: 420
            text: qsTr("Valider")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            onClicked: ctrlGameBoard.initGame(listView.model.listOfPlayers)
        }

    }
}

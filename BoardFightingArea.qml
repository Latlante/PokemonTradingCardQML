import QtQuick 2.0
import model 1.0

Item {
    id: boardFightingArea1
    width: 1000
    height: 600

    property Player play1
    property Player play2

    BoardFightingInformation {
        id: boardFightingInformation_P1
        width: parent.width / 2
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        player: play1
    }

    BoardFightingInformation {
        id: boardFightingInformation_P2
        anchors.top: parent.top
        anchors.left: boardFightingInformation_P1.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        rotation: 180

        player: play2
    }
}

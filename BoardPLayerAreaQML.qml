import QtQuick 2.0
import model 1.0

Item {
    id: boardPlayerArea1
    objectName: "boardPlayerArea1"
    width: 1000
    height: 600

    property Player player

    // |-----------------|
    // |***** Infos *****|
    // |-----------------|
    // |      Bench      |
    // |-----------------|
    // |       Hand      |
    // |-----------------|
    Rectangle {
        id: rectangleInfosPackets
        height: 50
        color: "#00000000"
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 0
        border.width: 4

        Text {
            id: textDeckCst
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
            id: textDeck
            width: 50
            text: player.deck().countCard
            verticalAlignment: Text.AlignVCenter
            anchors.left: textDeckCst.right
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
            id: textTrashCst
            width: 92
            height: 45
            text: qsTr("Trash:")
            verticalAlignment: Text.AlignVCenter
            anchors.left: textDeck.right
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
            id: textTrash
            width: 50
            text: player.trash().countCard
            verticalAlignment: Text.AlignVCenter
            anchors.left: textTrashCst.right
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
            id: textRewardsCst
            width: 144
            height: 45
            text: qsTr("Rewards:")
            verticalAlignment: Text.AlignVCenter
            anchors.left: textTrash.right
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
            id: textRewards
            width: 50
            text: player.rewards().countCard
            verticalAlignment: Text.AlignVCenter
            anchors.left: textRewardsCst.right
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

    // |-----------------|
    // |      Infos      |
    // |-----------------|
    // |***** Bench *****|
    // |-----------------|
    // |       Hand      |
    // |-----------------|
    ListView {
        id: listViewPacketBench
        objectName: "listViewPacketBench"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: listViewPacketHand.top
        anchors.bottomMargin: 0
        anchors.top: rectangleInfosPackets.bottom
        anchors.topMargin: 0
        orientation: ListView.Horizontal

        property int dragItemIndex: -1

        model: player.bench()
        delegate: Loader {
            id: loaderListViewPacketBench

            property int modelIndex: index
            property bool modelIsCard: model.isCard
            property AbstractCard modelCard: model.card
            property string modelImageCard: model.imageCard

            sourceComponent: {
                if(modelIsCard === true)
                {
                    //console.log("Loader: componentDelegateCardBench");
                    return componentDelegateCardBench;
                }
                else
                {
                    //console.log("Loader: componentDelegateCardEmptyBench");
                    return componentDelegateCardEmptyBench;
                }
            }
        }

        Component{
            id: componentDelegateCardBench
            Item {
                id: itemDelegatePacketBench
                x: 5
                width: 80
                height: 120

                Image {
                    id: imageCardInBench
                    objectName: "imageCardInBench"
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: listViewEnergiesByCard.top

                    property Player play: boardPlayerArea1.player
                    property int idArea: 0

                    source: modelImageCard
                    fillMode: Image.PreserveAspectFit

                    MouseArea {
                        id: mouseAreaCardBench
                        anchors.fill: parent
                        drag.target: imageCardInHand

                        drag.onActiveChanged: {
                            if (mouseAreaCardBench.drag.active)
                            {
                                listViewPacketBench.dragItemIndex = index;
                            }
                            imageCardInBench.Drag.drop();
                        }

                        onPressAndHold: {
                            popupCardDetailsComplete1.card = modelCard;
                            popupCardDetailsComplete1.visible = true;
                        }
                    }

                    states: [
                        State {
                            when: imageCardInBench.Drag.active
                            ParentChange {
                                target: imageCardInBench
                                parent: boardPlayerArea1
                            }

                            AnchorChanges {
                                target: imageCardInBench
                                anchors.horizontalCenter: undefined
                                anchors.verticalCenter: undefined
                            }
                        }
                    ]

                    Drag.active: mouseAreaCardBench.drag.active
                    Drag.hotSpot.x: imageCardInBench.width / 2
                    Drag.hotSpot.y: imageCardInBench.height / 2

                    DropArea {
                        id: dropAreaBenchCardBench
                        anchors.fill: parent
                        onDropped: {
                            console.log("onDropped");
                            if(drag.source.objectName === "imageCardInHand")
                            {
                                player.moveCardFromHandToBench(listViewPacketHand.dragItemIndex, modelIndex);
                                listViewPacketHand.dragItemIndex = -1;
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

                    //model: listViewPacketBench.model.modelFromCardPokemon(modelIndex)
                    model: modelCard.modelListOfEnergies()
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
                    source: modelImageCard
                    fillMode: Image.PreserveAspectFit
                }

                Rectangle {
                    id: rectangleEmptyBarCardEmptyBench
                    height: 25
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    //color: "green"
                    color: "transparent"
                }

                DropArea {
                    id: dropAreaBenchEmptyCard
                    anchors.fill: parent
                    onDropped: {
                        console.log("onDropped");
                        if(drag.source.objectName === "imageCardInHand")
                        {
                            player.moveCardFromHandToBench(listViewPacketHand.dragItemIndex, modelIndex);
                            listViewPacketHand.dragItemIndex = -1;
                        }
                    }
                }
            }
        }

        /*DropArea {
            id: dropAreaBench
            anchors.fill: parent
            onDropped: {
                console.log("onDropped");
                player.moveCardFromHandToBench(listViewPacketHand.dragItemIndex, 0);
                listViewPacketHand.dragItemIndex = -1;
            }
        }*/
    }

    // |-----------------|
    // |      Infos      |
    // |-----------------|
    // |      Bench      |
    // |-----------------|
    // |****** Hand *****|
    // |-----------------|
    ListView {
        id: listViewPacketHand
        objectName: "listViewPacketHand"
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

        property int dragItemIndex: -1

        model: player.hand()
        delegate: Item {
            width: 80
            height: 160

            Image {
                id: imageCardInHand
                objectName: "imageCardInHand"
                width: 120
                height: 160

                property Player play: boardPlayerArea1.player
                property int idArea: 1

                source: model.imageCard
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    id: mouseAreaCardHand
                    anchors.fill: parent
                    drag.target: imageCardInHand

                    drag.onActiveChanged: {
                        if (mouseAreaCardHand.drag.active)
                        {
                            listViewPacketHand.dragItemIndex = index;
                        }
                        imageCardInHand.Drag.drop();
                    }

                    onPressAndHold: {
                        popupCardDetailsBasic1.card = model.card;
                        popupCardDetailsBasic1.visible = true;
                    }
                }

                states: [
                    State {
                        when: imageCardInHand.Drag.active
                        ParentChange {
                            target: imageCardInHand
                            parent: boardPlayerArea1
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
}

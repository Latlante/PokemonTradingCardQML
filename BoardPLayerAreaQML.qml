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
            id: textNamePlayer
            verticalAlignment: Text.AlignVCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            font.pixelSize: 30
            text: player.name()
        }

        Text {
            id: textDeckCst
            width: 80
            height: 45
            text: qsTr("Deck:")
            anchors.right: textDeck.left
            anchors.rightMargin: 0
            verticalAlignment: Text.AlignVCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            fontSizeMode: Text.HorizontalFit
            renderType: Text.NativeRendering
            font.pixelSize: 30
        }

        Text {
            id: textDeck
            width: 50
            text: player.deck().countCard
            anchors.right: textTrashCst.left
            anchors.rightMargin: 0
            verticalAlignment: Text.AlignVCenter
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
            anchors.right: textTrash.left
            anchors.rightMargin: 0
            verticalAlignment: Text.AlignVCenter
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
            anchors.right: textRewardsCst.left
            anchors.rightMargin: 0
            verticalAlignment: Text.AlignVCenter
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
            anchors.right: textRewards.left
            anchors.rightMargin: 0
            verticalAlignment: Text.AlignVCenter
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
            anchors.right: parent.right
            anchors.rightMargin: 0
            verticalAlignment: Text.AlignVCenter
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
        preferredHighlightBegin: width/2 - widthComponent/2
        preferredHighlightEnd: width/2 + widthComponent/2
        //highlightRangeMode: ListView.StrictlyEnforceRange

        property int dragItemIndex: -1
        property int widthComponent: 80
        property int heightComponent: 140

        spacing: 10
        model: player.bench()
        delegate: Loader {
            id: loaderListViewPacketBench
            //width: 100
            //height: 140

            property int modelIndex: index
            property bool modelIsCard: model.isCard
            property AbstractCard modelCard: model.card === undefined ? null : model.card
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
            /*MouseArea {
                id: mouseAreaTestCardBench
                anchors.fill: parent
                drag.target: loaderListViewPacketBench

                drag.onActiveChanged: {
                    if (mouseAreaTestCardBench.drag.active)
                    {
                        listViewPacketBench.dragItemIndex = index;
                    }
                    loaderListViewPacketBench.Drag.drop();
                }

                //onReleased: rectangleCardInBench.Drag.drop();

                onPressAndHold: {
                    popupCardDetailsComplete1.card = modelCard;
                    popupCardDetailsComplete1.visible = true;
                }
            }

            states: [
                State {
                    when: loaderListViewPacketBench.Drag.active
                    ParentChange {
                        target: loaderListViewPacketBench
                        parent: boardPlayerArea1
                    }

                    AnchorChanges {
                        target: loaderListViewPacketBench
                        //anchors.horizontalCenter: undefined
                        //anchors.verticalCenter: undefined
                        anchors.top: undefined
                        anchors.left: undefined
                        anchors.right: undefined
                        anchors.bottom: undefined
                    }
                }
            ]

            Drag.active: mouseAreaTestCardBench.drag.active
            Drag.hotSpot.x: loaderListViewPacketBench.width / 2
            Drag.hotSpot.y: loaderListViewPacketBench.height / 2
        }*/
                  /*Item {
                      id: itemTestDelegatePacketBench
                      x: 5
                      width: 100
                      height: 140

                      Image {
                          id: imageTestPacketBench
                          objectName: "imageTestPacketBench"
                          anchors.top: parent.top
                          anchors.left: parent.left
                          anchors.right: parent.right
                          anchors.bottom: rectangleEmptyBarCardEmptyBench.top
                          source: model.imageCard
                          fillMode: Image.PreserveAspectFit

                          MouseArea {
                              id: mouseAreaTestCardBench
                              anchors.fill: parent
                              drag.target: imageTestPacketBench

                              drag.onActiveChanged: {
                                  if (mouseAreaTestCardBench.drag.active)
                                  {
                                      listViewPacketBench.dragItemIndex = index;
                                  }
                                  imageTestPacketBench.Drag.drop();
                              }

                              //onReleased: rectangleCardInBench.Drag.drop();

                              onPressAndHold: {
                                  popupCardDetailsComplete1.card = modelCard;
                                  popupCardDetailsComplete1.visible = true;
                              }
                          }

                          states: [
                              State {
                                  when: imageTestPacketBench.Drag.active
                                  ParentChange {
                                      target: imageTestPacketBench
                                      parent: boardPlayerArea1
                                  }

                                  AnchorChanges {
                                      target: imageTestPacketBench
                                      //anchors.horizontalCenter: undefined
                                      //anchors.verticalCenter: undefined
                                      anchors.top: undefined
                                      anchors.left: undefined
                                      anchors.right: undefined
                                      anchors.bottom: undefined
                                  }
                              }
                          ]

                          Drag.active: mouseAreaTestCardBench.drag.active
                          Drag.hotSpot.x: imageTestPacketBench.width / 2
                          Drag.hotSpot.y: imageTestPacketBench.height / 2
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
                          onEntered: console.log("dropAreaBenchEmptyCard entered");
                          onExited: console.log("dropAreaBenchEmptyCard exited");
                          onDropped: {
                              console.log("onDropped dropAreaBenchEmptyCard");
                              if(drag.source.objectName === "imageCardInHand")
                              {
                                  player.moveCardFromHandToBench(listViewPacketHand.dragItemIndex, modelIndex);
                                  listViewPacketHand.dragItemIndex = -1;
                              }
                          }
                      }
                  }*/


        Component{
            id: componentDelegateCardBench
            Item {
                id: itemDelegatePacketBench
                objectName: "itemDelegatePacketBench"
                x: 5
                width: listViewPacketBench.widthComponent
                height: listViewPacketBench.heightComponent

                Image {
                    id: imageCardInBench
                    objectName: "imageCardInBench"
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: listViewEnergiesByCard.top

                    source: modelImageCard
                    fillMode: Image.PreserveAspectFit

                    MouseArea {
                        id: mouseAreaCardBench
                        anchors.fill: parent
                        drag.target: imageCardInBench

                        drag.onActiveChanged: {
                            if (mouseAreaCardBench.drag.active)
                            {
                                listViewPacketBench.dragItemIndex = modelIndex;
                            }
                            imageCardInBench.Drag.drop();
                        }

                        //onReleased: rectangleCardInBench.Drag.drop();

                        onPressAndHold: {
                            popupCardDetailsComplete1.card = modelCard;
                            popupCardDetailsComplete1.visible = true;
                            //player.moveCardFromBenchToFight(modelIndex)

                            //TESTS
                            //ctrlPopups.displayBench(player.bench())
                            //ctrlPopups.displayDeck(player.deck())
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
                                //anchors.horizontalCenter: undefined
                                //anchors.verticalCenter: undefined
                                anchors.top: undefined
                                anchors.left: undefined
                                anchors.right: undefined
                                anchors.bottom: undefined
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
                            console.log("onDropped dropAreaBenchCardBench, " + drag.source.objectName);
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
                id: itemEmptyDelegatePacketBench
                x: 5
                width: listViewPacketBench.widthComponent
                height: listViewPacketBench.heightComponent

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
                    onEntered: console.log("dropAreaBenchEmptyCard entered");
                    onExited: console.log("dropAreaBenchEmptyCard exited");
                    onDropped: {
                        console.log("onDropped dropAreaBenchEmptyCard");
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
            id: itemCardInHand
            objectName: "itemCardInHand"
            width: 80
            height: 160

            Image {
                id: imageCardInHand
                objectName: "imageCardInHand"
                width: 120
                height: 160
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                //anchors.fill: parent

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

                    //onReleased: imageCardInHand.Drag.drop();

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
                            parent: listViewPacketHand
                        }

                        AnchorChanges {
                            target: imageCardInHand
                            //anchors.horizontalCenter: undefined
                            //anchors.verticalCenter: undefined
                            //anchors.left: undefined
                            anchors.top: undefined
                            anchors.left: undefined
                            anchors.bottom: undefined
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

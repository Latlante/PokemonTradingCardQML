import QtQuick 2.0
import model 1.0

Item {
    id: popupCardDetailBasic1
    width: 1000
    height: 500

    property AbstractCard card

    onCardChanged: {
        if(card != undefined)
        {
            var description = "";
            imageCard.source = card.image();

            if(card.type() === AbstractCard.TypeOfCard_Pokemon)
            {
                //description = card.id() + " - " + card.name();
                //description += " (" + card.lifeTotal() + ")";

                description += "----- " + card.name() + " -----\n\n";
                description += "ID: " + card.id() + "\n";
                description += "Element: " + card.elementFormatString() + "\n";
                description += "Vie totale: " + card.lifeTotal() + "\n\n";

                for(var i=0;i<card.attacksCount();++i)
                {
                    description += card.attackName() + " - " + card.attackDescription() + " (" + card.attackDamage() + ")\n\n";
                }

                //description += "ID: " + card.id() + "\n";

            }
            else if(card.type() === AbstractCard.TypeOfCard_Energy)
            {
                //description = card.id() + " - " + card.name();
                //description += " (" + card.quantity() + ")";

                description += "----- Energie " + card.name() + " -----\n\n";
                description += "Element: " + card.elementFormatString() + "\n";
                description += "Quantité: " + card.quantity();
            }

            textDescription.text = description;
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent

        color: "#AAAAAAAA"

        Image {
            id: imageCard
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.width / 2

            fillMode: Image.Pad
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            //source: card.imageCard
        }

        Text {
            id: textDescription
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.left: imageCard.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 30
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: mouseAreaClosing
            anchors.fill: parent
            onClicked: popupCardDetailBasic1.visible = false
        }
    }

}

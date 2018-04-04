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
                description = card.id() + " - " + card.name();
                description += " (" + card.lifeTotal() + ")";

                description += "----- " + card.name() + " -----";
                description += "ID: " + card.id();
                description += "Element: " + card.element();
                description += "Vie totale: " + card.lifeTotal();
                description += "ID: " + card.id();

            }
            else if(card.type() === AbstractCard.TypeOfCard_Energy)
            {
                description = card.id() + " - " + card.name();
                description += " (" + card.quantity() + ")";
            }

            textDescription.text = description;
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent

        color: "#000000AA"

        Image {
            id: imageCard
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.width / 2

            fillMode: Image.Pad
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            source: card.imageCard
        }

        Text {
            id: textDescription
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.left: imageCard.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 20
            wrapMode: Text.WordWrap
        }
    }

}

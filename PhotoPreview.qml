import QtQuick 2.0
import QtMultimedia 5.0

Item {
    id: previewForm
    property alias source : preview.source
    property string path
    signal closed

    Image {
        id: preview
        anchors.fill : parent
        fillMode: Image.PreserveAspectFit
        smooth: true

        Text {
                id: previewText
                color: "#ffffff"
                objectName: "previewText"
                anchors.left: parent.right
                anchors.bottom: parent.bottom
                text: "Waite a moment...";
                styleColor: "#ff0000"
                style: Text.Raised;
                font.pixelSize: 16
            }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            parent.closed();
        }
    }
}


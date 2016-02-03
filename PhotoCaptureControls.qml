import QtQuick 2.0
import QtMultimedia 5.0

FocusScope {
    property Camera camera
    property bool previewAvailable : false
    property string location
    property int buttonsPanelWidth: buttonPaneShadow.width

    signal previewSelected
    id : captureControls

    Rectangle {
        id: buttonPaneShadow
        width: buttonsColumn.width + 16
        height: parent.height
        anchors.top: parent.top
        anchors.right: parent.right
        color: Qt.rgba(0.08, 0.08, 0.08, 1)

        Column {
            anchors {
                right: parent.right
                top: parent.top
                margins: 8
            }

            id: buttonsColumn
            spacing: 8

            CameraButton {
                text: "Capture"
                visible: camera.imageCapture.ready
                onClicked: {
                    camera.imageCapture.capture();
                }
            }

        }

        Column {
            anchors {
                bottom: parent.bottom
                right: parent.right
                margins: 8
            }

            id: bottomColumn
            spacing: 8

            CameraButton {
                id: quitButton
                text: "Quit"
                onClicked: Qt.quit()
            }
        }
    }


    ZoomControl {
        x : 0
        y : 0
        width : 100
        height: parent.height

        currentZoom: camera.digitalZoom
        maximumZoom: Math.min(4.0, camera.maximumDigitalZoom)
        onZoomTo: camera.setDigitalZoom(value)
    }
}

import QtQuick 2.0

Rectangle {
    id: firstWin
    objectName: "objFirstWin"
    anchors.fill : parent
    width: 800
    height: 480

    color: "black"

    ListView {
        id: listView
        anchors.fill : parent
        model: myModel
        delegate: CameraButton {
            id: button
            width: parent.width
            onClicked: myObj.quitFirst(button.text);
            text: modelData
        }
    }

    CameraButton {
        id: quitButton
        width: parent.width
        objectName: "objQuitButton"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        text: "Quit"
        onClicked: myObj.quit();
    }
}

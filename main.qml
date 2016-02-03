import QtQuick 2.3
import QtMultimedia 5.2

Rectangle {
    id : cameraUI

    width: 800
    height: 480

    color: "black"
    state: "PhotoCapture"

    states: [
        State {
            id: state1
            name: "PhotoCapture"
            StateChangeScript {
                script: {
                    camera.captureMode = Camera.CaptureStillImage
                    camera.start()
                }
            }

            PropertyChanges {
                name: "PhotoCapture"
                target: state1
            }
        },
        State {
            name: "PhotoPreview"

            PropertyChanges {
                name: "PhotoPreview"
                target: state1
            }
        }
    ]

    Camera {
        id: camera
        captureMode: Camera.CaptureStillImage

        imageCapture {
            onImageCaptured: {
                photoPreview.source = preview
                photoPreview.path = stillControls.location
                stillControls.previewAvailable = true
                cameraUI.state = "PhotoPreview"
            }
            onImageSaved: {
                myObject.sendPhoto(camera.imageCapture.capturedImagePath.toString());
            }
        }
    }

    PhotoPreview {
        id : photoPreview
        objectName: "photoPreview"
        anchors.fill : parent
        onClosed: cameraUI.state = "PhotoCapture"
        visible: cameraUI.state == "PhotoPreview"
        focus: visible
    }

    VideoOutput {
        id: viewfinder
        visible: cameraUI.state == "PhotoCapture"
        x: 0
        y: 0
        width: parent.width - stillControls.buttonsPanelWidth
        height: parent.height

        source: camera
    }

    PhotoCaptureControls {
        id: stillControls
        anchors.fill: parent
        camera: camera
        visible: cameraUI.state == "PhotoCapture"
        onPreviewSelected: cameraUI.state = "PhotoPreview"
    }
}

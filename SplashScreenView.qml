import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

import ConfigView 1.0

Window {
    id: splashScreen
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen
    width: 300
    height: 200

    Rectangle {
       id: splashRect
       anchors.fill: parent
       color: ConfigView.mainWhiteColor
       border.width: 1
       border.color: ConfigView.addLightBlueColor

       Text {
           text: qsTr("Loading...")
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.bottom: parent.bottom
           anchors.bottomMargin: parent.height*0.02
           font.bold: true
           font.pixelSize: 20
           color: ConfigView.addLightBlueColor
       }

       Image {
           anchors.top: parent.top
           anchors.topMargin: 10
           width: parent.height*0.8
           height: width
           anchors.horizontalCenter: parent.horizontalCenter
           source: "Resources/AppIcon.png"
           fillMode: Image.PreserveAspectFit
           opacity: 0.9
        }

       BusyIndicator {
           id: busyAnimation
           anchors.horizontalCenter: parent.horizontalCenter
           // anchors.verticalCenter: parent.verticalCenter
           anchors.bottom: parent.bottom
           anchors.bottomMargin: parent.height*0.15
           width: parent.height*0.2
           height: width
           running: true
       }
    }

    Component.onCompleted: visible = true
}

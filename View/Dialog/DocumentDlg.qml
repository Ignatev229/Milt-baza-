import QtQuick 2.15
import QtWebEngine 1.10

import "../../Component"

Rectangle {
    id: root
    color: "lightgray"

    property string fileName: "document.pdf"

    visible: true
    required property string titleDescription

    signal moveByTitleBar(int xPos, int yPos)
    signal closeDlg()

    // title bar
    Rectangle {
        id: titleBar
        width: parent.width
        height: 40
        color: "#404142"

        Text {
            id: titleBarText
            text: qsTr(titleDescription)
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 30
        }



        MouseArea {
            id: titleBarDragArea
            anchors.fill: parent

            property real dragStartX
            property real dragStartY

            onPressed: {
                dragStartX = mouseX
                dragStartY = mouseY
            }

            onPositionChanged: {
                root.moveByTitleBar(mouseX - dragStartX, mouseY - dragStartY)
            }

        }

        TopBarButton{
            _height: parent.height
            _width: _height*1.7
            _btnColorDefault: titleBar.color
            _btnColorOverlay: "#C4C4C4"
            _btnColorMouseOver: "#D71526"
            _btnIconSource: "../../Resources/close_icon.svg"
            anchors.right: parent.right
            onClicked:{
                root.closeDlg()
            }
        }
    }


    Rectangle {
        anchors {
            top: titleBar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        width: parent.width
        height: parent.height - titleBar.height
        WebEngineView {
            anchors.fill: parent
            url: {
                var path = Qt.platform.os === "windows" ? "file:///" : "file://"
                return path + mainVM.homePath + "/" + root.fileName
            }
            settings {
                pluginsEnabled: true // Enable plugins for PDF support
            }
        }
    }
}

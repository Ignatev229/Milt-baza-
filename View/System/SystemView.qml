import QtQuick 2.15


import ConfigView 1.0
import "../../View"
import "../../Component"

Item {
    id: system_view
    width: parent.width
    height: parent.height

    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.mainBlueColor
    property int _fontSize: 24

    Rectangle {
        width: parent.width
        height: parent.height
        Image {
            opacity: 0.4
            width: parent.width
            height: parent.height
            source: "../../Resources/LoginBG.png"
        }


        Column {
            width: parent.width*0.7
            height: parent.height*0.7
            anchors.centerIn: parent
            spacing: parent.height*0.05

            Row {
                height: parent.height*0.15
                width: parent.width*0.96
                spacing: parent.width*0.03
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: qsTr("Current Time") + ": "
                    width: parent.width*0.5
                    font.pointSize: _fontSize
                    color: _textColor
                    font.family: _fontFamily
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WordWrap
                    lineHeight: _fontSize * 0.03
                }

                Text {
                    text: ConfigView.currentDate + " " + ConfigView.currentTime
                    width: contentWidth
                    font.pointSize: _fontSize
                    color: _textColor
                    font.family: _fontFamily
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

            }

            Row {
                height: parent.height*0.15
                width: parent.width*0.96
                spacing: parent.width*0.03
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: qsTr("System Start Time") + ": "
                    width: parent.width*0.5
                    font.pointSize: _fontSize
                    color: _textColor
                    font.family: _fontFamily
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WordWrap
                    lineHeight: _fontSize * 0.03
                }

                Text {
                    text: ConfigView.systemStartDateTime
                    width: contentWidth
                    font.pointSize: _fontSize
                    color: _textColor
                    font.family: _fontFamily
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

            }

            Row {
                height: parent.height*0.15
                width: parent.width*0.96
                spacing: parent.width*0.03
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: qsTr("Number Of Bottles") + ": "
                    width: parent.width*0.5
                    font.pointSize: _fontSize
                    color: _textColor
                    font.family: _fontFamily
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WordWrap
                    lineHeight: _fontSize * 0.03
                }

                Text {
                    text: _viewModel.numberOfBottles
                    width: contentWidth
                    font.pointSize: _fontSize
                    color: _textColor
                    font.family: _fontFamily
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

            }

            Row {
                height: parent.height*0.15
                width: parent.width*0.96
                spacing: parent.width*0.03
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: qsTr("Time Of Last Bottle") + ": "
                    width: parent.width*0.5
                    font.pointSize: _fontSize
                    color: _textColor
                    font.family: _fontFamily
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WordWrap
                    lineHeight: _fontSize * 0.03
                }

                Text {
                    text: _viewModel.lastBottleTime
                    width: contentWidth
                    font.pointSize: _fontSize
                    color: _textColor
                    font.family: _fontFamily
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

            }


        }

    }
}

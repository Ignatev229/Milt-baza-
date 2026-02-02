import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import ConfigView 1.0

import "../../Component"

Item {
    id: debug_log_view_layout
    property int _fontSizeText: 10
    property string _fontFamily: ConfigView.fontFamily
    property QtObject _model: QtObject{}
    property color _textActivateColor: "white"//"#90CAF9"
    property color headerColor: ConfigView.addLightBlueColor
    property string _headerName: qsTr("Debug Log")
    property double _headerHeight: height*0.15

    signal swapDebugLogTab_Signal() //


    Column{
        anchors.fill: parent
        anchors.centerIn: parent

        Rectangle{
            //header
            id: header
            width:  parent.width
            height: _headerHeight
            color: headerColor
            clip : true

            Text {
                text: _headerName
                width: parent.width
                height: parent.height
                font.family: _fontFamily
                font.pointSize: _fontSizeText + 1
                font.bold: true
                color: _textActivateColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle{
                width: parent.width*0.1
                height: parent.height
                color: "transparent"
                anchors.right: parent.right
                ButtonMaterial{
                    _width: parent.height
                    _height: parent.height
                    _size: _width*0.9
                    _iconSourceOn: "swapHorizontalCircleOutline"
                    _colorBorder: " transparent"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    _colorBGDefault: "transparent"
                    _colorBGMouseOver: "transparent"
                    _colorIconDefault: ConfigView.addGrayColor
                    onClicked: {
                        debug_log_view_layout.swapDebugLogTab_Signal()
                    }
                }
            }


        }

        Rectangle{
            id: content
            width:  parent.width
            height: parent.height - header.height
            color: ConfigView.mainWhiteColor
            border.width: 1
            border.color: headerColor
            clip : true
            ListView {
                id: listView
                width: parent.width
                height: parent.height
                spacing: 10
                clip: true
                flickableDirection: Flickable.VerticalFlick
                boundsBehavior: Flickable.StopAtBounds
                model: _model

                delegate:  Item {
                    // implicitWidth: parent.width
                    implicitHeight: grid.height
                    Rectangle{
                        id: grid
                        // spacing: 0
                        width: parent.width
                        height: commentLabel.implicitHeight
                        color: "transparent"
                        Label {
                            id: commentLabel
                            // Layout.fillWidth: true
                            text: model.info
                            wrapMode: Label.Wrap
                            font.family: _fontFamily
                            font.pointSize: _fontSizeText
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width*0.01
                        }
                    }
                }

                ScrollBar.vertical:ScrollBar{
                    anchors.right: parent.right
                    visible: listView.contentHeight > listView.height ? true : false
                }
                onContentHeightChanged: {
                    if (listView.contentY >= listView.contentHeight - height - 150) {
                        positionViewAtEnd()
                    }
                }
            }

        }

    }

}

import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import ConfigView 1.0


import "../../View"
import "../../Component"

Item {

    id: layout
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.mainWhiteColor
    property int _fontSize: 12

    Column {
        height: parent.height*0.7
        width: parent.width*0.8
        spacing: parent.height*0.02
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Row {
            width: parent.width
            height: parent.height*0.5
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: parent.width*0.03

            ButtonMaterialTextHorizontal{
                height: parent.height*0.5
                width: parent.width*0.3
                _size: height*0.8
                _text: qsTr("Install Update")
                _iconSourceOn: "update"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: _fontFamily
                _textRatio: 0.2
                onClicked: {

                }
            }

            ButtonMaterialTextHorizontal{
                height: parent.height*0.5
                width: parent.width*0.3
                _size: height*0.8
                _text: qsTr("Exit Software")
                _iconSourceOn: "exitToApp"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: _fontFamily
                _textRatio: 0.2
                onClicked: {
                    _viewModel.exitSoftware()
                }
            }

            ButtonMaterialTextHorizontal{
                height: parent.height*0.5
                width: parent.width*0.3
                _size: height*0.8
                _text: qsTr("Swap Version")
                _iconSourceOn: "folderSwap"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: _fontFamily
                _textRatio: 0.2
                onClicked: {

                }
            }

        }

        Row {
            width: parent.width
            height: parent.height*0.5
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: parent.width*0.03

            ButtonMaterialTextHorizontal{
                height: parent.height*0.5
                width: parent.width*0.3
                _size: height*0.8
                _text: qsTr("Restart Software")
                _iconSourceOn: "restart"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: _fontFamily
                _textRatio: 0.2
                onClicked: {
                    _viewModel.restartSoftware()
                }
            }

            ButtonMaterialTextHorizontal{
                height: parent.height*0.5
                width: parent.width*0.3
                _size: height*0.8
                _text: qsTr("Reboot System")
                _iconSourceOn: "lockReset"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: _fontFamily
                _textRatio: 0.2
                onClicked: {
                    _viewModel.rebootSystem()
                }
            }

            ButtonMaterialTextHorizontal{
                height: parent.height*0.5
                width: parent.width*0.3
                _size: height*0.8
                _text: qsTr("Shutdown System")
                _iconSourceOn: "power"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: _fontFamily
                _textRatio: 0.2
                onClicked: {
                    _viewModel.shutdownSystem()
                }
            }

        }

    }

}

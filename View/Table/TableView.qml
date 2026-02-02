import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3


import ConfigView 1.0

import "../../Component/MaterialDesign"
import "../../Component"

Item {
    id: table_layout

    width: parent.width
    height: parent.height
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property int _fontSize: 14
    property color _textColor: ConfigView.textColor

    function resetAllButtonChecked(){
        stop_btn.setStatusSelected(false);
        auto_btn.setStatusSelected(false);
        manual_btn.setStatusSelected(false);

        table_elevation_go_btn.setStatusSelected(false);
        table_elevation_home_btn.setStatusSelected(false);

        table_angle_rotate_left_btn .setStatusSelected(false);
        table_angle_rotate_right_btn.setStatusSelected(false);
        table_angle_rotate_home_btn.setStatusSelected(false);

        go_to_load_btn.setStatusSelected(false);
        go_to_unload_btn.setStatusSelected(false);

        save_as_load_btn.setStatusSelected(false);
        save_as_unload_btn.setStatusSelected(false);
    }

    Rectangle{
        anchors.fill: parent
        color: ConfigView.mainWhiteColor

        Column {
            width: parent.width*0.96
            height: parent.height*0.9
            spacing: parent.height*0.05
            anchors.centerIn: parent

            Row {
                width: parent.width
                height: parent.height*0.12
                spacing: width*0.1
                property int buttonWidth: width*0.18

                ButtonMaterialTextHorizontal {
                    id: stop_btn
                    enabled: !ConfigView.isAutoMode
                    opacity: enabled ? 1 : 0.5
                    height: parent.height*0.9
                    width: parent.buttonWidth
                    _size: height*0.8
                    _text: qsTr("Stop")
                    _iconSourceOn: "stop"
                    _colorIconMouseOver: _colorIconDefault
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: _fontFamily
                    _textRatio: 0.4
                    _numberStatus: 3
                    onClicked: {
                        feederAndPushersVM.stopAllCommand_Qml_Slot();
                        table_layout.resetAllButtonChecked();
                        setStatusSelected(true);
                    }
                }

                Text {
                    text: qsTr("Mode") + ": "
                    width: right_layout.textWidth
                    font.pointSize: _fontSize
                    color: ConfigView.mainBlueColor
                    font.family: _fontFamily
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    // anchors.left: parent.left
                    // anchors.leftMargin: parent.width*0.2
                }

                ButtonMaterialTextHorizontal{
                    id: auto_btn
                    height: parent.height*0.9
                    width: parent.buttonWidth
                    // anchors.left: parent.left
                    // anchors.leftMargin: parent.width*0.28
                    _size: height*0.8
                    _text: qsTr("Auto")
                    _iconSourceOn: "stateMachine"
                    _colorIconMouseOver: _colorIconDefault
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: _fontFamily
                    _textRatio: 0.4
                    _numberStatus: 3
                    onClicked: {
                        feederAndPushersVM.autoManualModeChanged_Qml_Slot(true);
                        ConfigView.isAutoMode = true
                        table_layout.resetAllButtonChecked();
                        setStatusSelected(true);
                    }
                }

                ButtonMaterialTextHorizontal{
                    id: manual_btn
                    height: parent.height*0.9
                    width: parent.buttonWidth
                    // anchors.right: parent.right
                    // anchors.rightMargin: parent.width*0.28
                    _size: height*0.8
                    _text: qsTr("Manual")
                    _iconSourceOn: "accountEdit"
                    _colorIconMouseOver: _colorIconDefault
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: _fontFamily
                    _textRatio: 0.4
                    _numberStatus: 3
                    onClicked: {
                        feederAndPushersVM.autoManualModeChanged_Qml_Slot(false);
                        ConfigView.isAutoMode = false
                        table_layout.resetAllButtonChecked();
                        setStatusSelected(true);
                    }
                }
            }

            GroupBox{
                enabled: !ConfigView.isAutoMode
                opacity: enabled ? 1 : 0.5
                width: parent.width
                height: parent.height*0.29
                anchors.horizontalCenter: parent.horizontalCenter
                background:Rectangle{
                    color: "transparent"
                    width: parent.width
                    height: parent.height
                    radius: 10
                    border.width: 2
                    border.color: "#7F7F7F"
                }

                label:Rectangle{
                    color: ConfigView.addLightBlueColor
                    width: title.contentWidth*1.1
                    height: parent.height*0.2
                    anchors.left: parent.left
                    anchors.leftMargin: 7
                    anchors.bottom: parent.top
                    anchors.bottomMargin: -height/2
                    radius: 10
                    Text {
                        id: title
                        height: parent.height
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        text: qsTr("Move Table")
                        color: _textColor
                        font.bold: true
                        font.pointSize: _fontSize + 2
                        font.family: _fontFamily
                    }
                }

                Column {
                    width: parent.width*0.96
                    height: parent.height*0.9
                    spacing: parent.height*0.04
                    anchors.centerIn: parent
                    property int textWidth: width*0.13
                    property int buttonWidth: width*0.18
                    property int itemHeight: height*0.48

                    Row {
                        width: parent.width
                        height: parent.itemHeight
                        spacing: parent.width*0.04

                        Text {
                            text: qsTr("Table Elevation") + ": "
                            width: parent.parent.textWidth*0.7
                            font.pointSize: _fontSize
                            color: ConfigView.mainBlueColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            text: _viewModel.tableElevationValue.toFixed(1)
                            width: parent.parent.textWidth/2
                            font.pointSize: _fontSize
                            color: ConfigView.mainBlueColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        InputText{
                            id: table_elevation_pos_text
                            _width: parent.parent.textWidth*0.7
                            _height: parent.height*0.8
                            _fontSizeText: _fontSize
                            _text: "0"
                            _leftMagin: 0
                            anchors.verticalCenter: parent.verticalCenter
                            _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                            _inputMethodHints: Qt.ImhFormattedNumbersOnly
                        }

                        ButtonMaterialTextHorizontal{
                            id: table_elevation_go_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Go")
                            _iconSourceOn: "arrowUpBold"
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.37
                            _colorIconMouseOver: _colorIconDefault
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.tableElevationGo_Qml_Slot(table_elevation_pos_text.getText())
                                table_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }

                        // ButtonMaterialTextHorizontal{
                        //     height: parent.height*0.9
                        //     width: parent.parent.buttonWidth
                        //     _size: height*0.8
                        //     _text: qsTr("Down")
                        //     _iconSourceOn: "arrowDownBoldBox"
                        //     anchors.verticalCenter: parent.verticalCenter
                        //     _fontFamily: _fontFamily
                        //     _textRatio: 0.4
                        //     _colorIconMouseOver: _colorIconDefault
                        //     onClicked: {
                        //         _viewModel.tableElevationDown_Qml_Slot()
                        //     }
                        // }

                        ButtonMaterialTextHorizontal{
                            id: table_elevation_home_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Home")
                            _iconSourceOn: "home"
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.37
                            _colorIconMouseOver: _colorIconDefault
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.tableElevationHome_Qml_Slot()
                                table_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }
                    }

                    Row {
                        width: parent.width
                        height: parent.itemHeight
                        spacing: parent.width*0.04

                        Text {
                            text: qsTr("Table Angle") + ": "
                            width: parent.parent.textWidth*0.7
                            font.pointSize: _fontSize
                            color: _textColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            text: _viewModel.tableAngleValue.toFixed(1)
                            width: parent.parent.textWidth/2
                            font.pointSize: _fontSize
                            color: _textColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        InputText{
                            id: table_angle_pos_text
                            _width: parent.parent.textWidth*0.7
                            _height: parent.height*0.8
                            _fontSizeText: _fontSize
                            _text: "0"
                            _leftMagin: 0
                            anchors.verticalCenter: parent.verticalCenter
                            _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                            _inputMethodHints: Qt.ImhFormattedNumbersOnly
                        }

                        ButtonMaterialTextHorizontal{
                            id: table_angle_rotate_left_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.75
                            _text: qsTr("Rotate Left")
                            _iconSourceOn: "axisZRotateCounterclockwise"
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.35
                            _colorIconMouseOver: _colorIconDefault
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.tableAngleRotateLeft_Qml_Slot(table_angle_pos_text.getText())
                                table_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }

                        ButtonMaterialTextHorizontal{
                            id: table_angle_rotate_right_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Rotate Right")
                            _iconSourceOn: "axisZRotateClockwise"
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.35
                            _colorIconMouseOver: _colorIconDefault
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.tableAngleRotateRight_Qml_Slot(table_angle_pos_text.getText())
                                table_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }

                        ButtonMaterialTextHorizontal{
                            id: table_angle_rotate_home_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Home")
                            _iconSourceOn: "home"
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.35
                            _colorIconMouseOver: _colorIconDefault
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.tableAngleHome_Qml_Slot()
                                table_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }
                    }

                }
            }

            GroupBox{
                visible: false
                enabled: !ConfigView.isAutoMode
                opacity: enabled ? 1 : 0.5
                width: parent.width
                height: parent.height*0.2
                anchors.horizontalCenter: parent.horizontalCenter
                background:Rectangle{
                    color: "transparent"
                    width: parent.width
                    height: parent.height
                    radius: 10
                    border.width: 2
                    border.color: "#7F7F7F"
                }

                label:Rectangle{
                    color: ConfigView.addLightBlueColor
                    width: title1.contentWidth*1.1
                    height: parent.height*0.2
                    anchors.left: parent.left
                    radius: 10
                    anchors.leftMargin: 10
                    anchors.bottom: parent.top
                    anchors.bottomMargin: -height/2
                    Text {
                        id: title1
                        height: parent.height
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        text: qsTr("Current Setting")
                        color: _textColor
                        font.bold: true
                        font.pointSize: _fontSize + 2
                        font.family: _fontFamily
                    }
                }

                Row {
                    width: parent.width*0.86
                    height: parent.height*0.9
                    spacing: parent.width*0.01
                    anchors.centerIn: parent
                    property int textWidth: width*0.2
                    Text {
                        text: qsTr("Load Position") + ": "
                        width: parent.textWidth
                        font.pointSize: _fontSize
                        color: ConfigView.mainBlueColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WordWrap
                        lineHeight: _fontSize * 0.05
                    }

                    Text {
                        text: _viewModel.loadPosition
                        width: parent.textWidth/2
                        font.pointSize: _fontSize
                        color: ConfigView.mainBlueColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    // Spacing
                    Rectangle {
                        color: "transparent"
                        width: parent.width*0.2
                        height: parent.height
                    }
                    Text {
                        text: qsTr("Unload Position") + ": "
                        width: parent.textWidth
                        font.pointSize: _fontSize
                        color: ConfigView.mainBlueColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WordWrap
                        lineHeight: _fontSize * 0.05
                    }

                    Text {
                        text: _viewModel.unloadPosition
                        width: parent.textWidth/2
                        font.pointSize: _fontSize
                        color: ConfigView.mainBlueColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                }
            }

            Row {
                visible: false
                enabled: !ConfigView.isAutoMode
                opacity: enabled ? 1 : 0.5
                width: parent.width
                height: parent.height*0.27
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: parent.width*0.04

                GroupBox{
                    width: parent.width*0.48
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    background:Rectangle{
                        color: "transparent"
                        width: parent.width
                        height: parent.height
                        radius: 10
                        border.width: 2
                        border.color: "#7F7F7F"
                    }

                    label:Rectangle{
                        color: ConfigView.addLightBlueColor
                        width: title2.contentWidth*1.1
                        height: parent.height*0.06
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.bottom: parent.top
                        anchors.bottomMargin: -height/2
                        Text {
                            id: title2
                            height: parent.height
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("Test")
                            color: _textColor
                            font.bold: true
                            font.pointSize: _fontSize + 2
                            font.family: _fontFamily
                        }
                    }


                    Row {
                        width: parent.width*0.86
                        height: parent.height*0.9
                        spacing: parent.width*0.1
                        anchors.centerIn: parent
                        ButtonMaterialTextHorizontal{
                            id: go_to_load_btn
                            height: parent.height*0.55
                            width: parent.width*0.45
                            _size: height*0.8
                            _text: qsTr("Go To Load")
                            _iconSourceOn: "upload"
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.33
                            _colorIconMouseOver: _colorIconDefault
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.testGotoLoad_Qml_Slot()
                                table_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }


                        ButtonMaterialTextHorizontal{
                            id: go_to_unload_btn
                            height: parent.height*0.55
                            width: parent.width*0.45
                            _size: height*0.8
                            _text: qsTr("Go To Unload")
                            _iconSourceOn: "download"
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.33
                            _colorIconMouseOver: _colorIconDefault
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.testGotoUnload_Qml_Slot()
                                table_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }

                    }

                }


                GroupBox{
                    width: parent.width*0.48
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    background:Rectangle{
                        color: "transparent"
                        width: parent.width
                        height: parent.height
                        radius: 10
                        border.width: 2
                        border.color: "#7F7F7F"
                    }

                    label:Rectangle{
                        color: ConfigView.addLightBlueColor
                        width: title3.contentWidth*1.1
                        height: parent.height*0.2
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.bottom: parent.top
                        anchors.bottomMargin: -height/2
                        Text {
                            id: title3
                            height: parent.height
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("Save")
                            color: _textColor
                            font.bold: true
                            font.pointSize: _fontSize + 2
                            font.family: _fontFamily
                        }
                    }

                    Row {
                        width: parent.width*0.86
                        height: parent.height*0.9
                        spacing: parent.width*0.1
                        anchors.centerIn: parent
                        ButtonMaterialTextHorizontal{
                            id: save_as_load_btn
                            height: parent.height*0.55
                            width: parent.width*0.45
                            _size: height*0.8
                            _text: qsTr("Save As Load")
                            _iconSourceOn: "upload"
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.33
                            _colorIconMouseOver: _colorIconDefault
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.saveAsLoad_Qml_Slot()
                                table_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }


                        ButtonMaterialTextHorizontal{
                            id: save_as_unload_btn
                            height: parent.height*0.55
                            width: parent.width*0.45
                            _size: height*0.8
                            _text: qsTr("Save As Unload")
                            _iconSourceOn: "download"
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.33
                            _colorIconMouseOver: _colorIconDefault
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.saveAsUnload_Qml_Slot()
                                table_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }
                    }
                }
            }

        }
    }
}

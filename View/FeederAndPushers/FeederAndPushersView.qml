import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.5 as C1_5
import QtQuick.Controls.Styles 1.4

import ConfigView 1.0

import "../../Component/MaterialDesign"
import "../../Component"

Item {
    id: feeder_and_pusher_layout
    width: parent.width
    height: parent.height
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property int _fontSize: 18
    property color _textColor: ConfigView.mainBlueColor

    function resetAllButtonChecked(){
        // machine_home_position_btn.setStatusSelected(false);
        reset_drivers_btn.setStatusSelected(false);
        stop_btn.setStatusSelected(false);

        conveyor_start_stop_btn.setStatusSelected(false);

        infeed_cylinder_1_open_btn.setStatusSelected(false);
        infeed_cylinder_1_close_btn.setStatusSelected(false);

        infeed_cylinder_2_open_btn.setStatusSelected(false);
        infeed_cylinder_2_close_btn.setStatusSelected(false);

        outfeed_cylinder_open_btn.setStatusSelected(false);
        outfeed_cylinder_close_btn.setStatusSelected(false);

        rotate_cylinder_open_btn.setStatusSelected(false);
        rotate_cylinder_close_btn.setStatusSelected(false);

        // save_btn.setStatusSelected(false);
        // cancel_btn.setStatusSelected(false);

        auto_btn.setStatusSelected(false);
        manual_btn.setStatusSelected(false);

        scale_pusher_move_btn.setStatusSelected(false);
        scale_pusher_home_btn.setStatusSelected(false);

        table_pusher_move_btn.setStatusSelected(false);
        table_pusher_home_btn.setStatusSelected(false);

        pushup_distance_reset_btn.setStatusSelected(false);
        scale_reset_btn.setStatusSelected(false);

        // test_bottle_diameter_test_btn.setStatusSelected(false);
        // test_bottle_diameter_push_home_btn.setStatusSelected(false);

        motor_camera_move_btn.setStatusSelected(false);
        motor_camera_home_btn.setStatusSelected(false);

        air_compressor_open_btn.setStatusSelected(false);
        air_compressor_close_btn.setStatusSelected(false);

        vaccum_ejector_open_btn.setStatusSelected(false);
        vaccum_ejector_close_btn.setStatusSelected(false);


    }

    Rectangle{
        anchors.fill: parent
        color: ConfigView.mainWhiteColor
        Column {
            width: parent.width*0.96
            height: parent.height*0.9
            spacing: height*0.02
            anchors.centerIn: parent

            Row {
                width: parent.width
                height: parent.height*0.98

                Column {
                    id: left_layout
                    width: parent.width*0.5
                    height: parent.height
                    spacing: parent.height*0.06



                    property int textWidth: width*0.34
                    property int itemHeight: height*0.1
                    property int buttonWidth: width*0.27
                    property int space: width*0.04
                    property color openButtonIconDefaultColor: ConfigView.mainBlueColor
                    property color openButtonIconHighColor: ConfigView.mainBlueColor
                    property color closeButtonIconDefaultColor: ConfigView.mainBlueColor
                    property color closeButtonIconHighColor: ConfigView.mainBlueColor

                    Rectangle {
                        width: parent.width
                        height: parent.itemHeight
                        color: "transparent"

                        // ButtonMaterialTextHorizontal{
                        //     id: machine_home_position_btn
                        //     enabled: ConfigView.isAutoMode
                        //     opacity: enabled ? 1 : 0.5
                        //     height: parent.height*0.9
                        //     width: left_layout.buttonWidth*1.2
                        //     _size: height*0.8
                        //     _text: qsTr("Machine \nCalibration")
                        //     _iconSourceOn: "home"
                        //     _colorIconMouseOver: _colorIconDefault
                        //     anchors.verticalCenter: parent.verticalCenter
                        //     anchors.left: parent.left
                        //     anchors.leftMargin: parent.width*0.18
                        //     _fontFamily: _fontFamily
                        //     _textRatio: 0.37
                        //     _numberStatus: 3
                        //     onClicked: {
                        //         _viewModel.machineHomePosition_Qml_Slot();
                        //         feeder_and_pusher_layout.resetAllButtonChecked();
                        //         setStatusSelected(true);
                        //     }
                        // }

                        ButtonMaterialTextHorizontal{
                            id: reset_drivers_btn
                            enabled: !ConfigView.isAutoMode
                            opacity: enabled ? 1 : 0.5
                            height: parent.height*0.9
                            width: left_layout.buttonWidth*1.2
                            _size: height*0.8
                            _text: qsTr("Reset \nDrivers")
                            _iconSourceOn: "restart"
                            _colorIconMouseOver: _colorIconDefault
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width*0.18
                            _fontFamily: _fontFamily
                            _textRatio: 0.35
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.resetDrives_Qml_Slot();
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }

                        ButtonMaterialTextHorizontal{
                            id: stop_btn
                            enabled: !ConfigView.isAutoMode
                            opacity: enabled ? 1 : 0.5
                            height: parent.height*0.9
                            width: left_layout.buttonWidth*1.2
                            _size: height*0.8
                            _text: qsTr("Stop")
                            _iconSourceOn: "stop"
                            _colorIconMouseOver: _colorIconDefault
                            // anchors.verticalCenter: parent.verticalCenter
                            // anchors.horizontalCenter: parent.horizontalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: parent.width*0.09
                            _fontFamily: _fontFamily
                            _textRatio: 0.35
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.stopAllCommand_Qml_Slot();
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }





                    }

                    Row {
                        width: parent.width
                        height: parent.itemHeight
                        spacing: parent.space
                        enabled: !ConfigView.isAutoMode
                        opacity: enabled ? 1 : 0.5
                        Text {
                            text: qsTr("Conveyor") + ": "
                            width: parent.parent.textWidth
                            font.pointSize: _fontSize
                            color: _textColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        ToggleButtonMaterialTextHorizontal{
                            id: conveyor_start_stop_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth*1.2
                            _size: height*0.8
                            _text: _isClicked ? qsTr("Stop") : qsTr("Start")
                            _iconSourceOn: "square"
                            _iconSourceOff: "arrowRightDropCircle"
                            _colorIconDefault: left_layout.openButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.closeButtonIconDefaultColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.conveyorStartStop_Qml_Slot(_isClicked)
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }
                    }

                    Row {
                        width: parent.width
                        height: parent.itemHeight
                        spacing: parent.space
                        enabled: !ConfigView.isAutoMode
                        opacity: enabled ? 1 : 0.5
                        Text {
                            text: qsTr("Infeed cylinder 1") + ": "
                            width: parent.parent.textWidth
                            font.pointSize: _fontSize
                            color: _textColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        ButtonMaterialTextHorizontal{
                            id: infeed_cylinder_1_open_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Open")
                            _iconSourceOn: "valveOpen"
                            _colorIconDefault: left_layout.openButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.openButtonIconHighColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.infeedCylinder1OpenClose_Qml_Slot(true);
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }

                        ButtonMaterialTextHorizontal{
                            id: infeed_cylinder_1_close_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Close")
                            _iconSourceOn: "valveClosed"
                            _colorIconDefault: left_layout.closeButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.closeButtonIconHighColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.infeedCylinder1OpenClose_Qml_Slot(false);
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }
                    }

                    Row {
                        width: parent.width
                        height: parent.itemHeight
                        spacing: parent.space
                        enabled: !ConfigView.isAutoMode
                        opacity: enabled ? 1 : 0.5
                        Text {
                            text: qsTr("Infeed cylinder 2") + ": "
                            width: parent.parent.textWidth
                            font.pointSize: _fontSize
                            color: _textColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        ButtonMaterialTextHorizontal{
                            id: infeed_cylinder_2_open_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Open")
                            _iconSourceOn: "valveOpen"
                            _colorIconDefault: left_layout.openButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.openButtonIconHighColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.infeedCylinder2OpenClose_Qml_Slot(true);
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }

                        ButtonMaterialTextHorizontal{
                            id: infeed_cylinder_2_close_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Close")
                            _iconSourceOn: "valveClosed"
                            _colorIconDefault: left_layout.closeButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.closeButtonIconHighColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.infeedCylinder2OpenClose_Qml_Slot(false);
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }
                    }

                    Row {
                        width: parent.width
                        height: parent.itemHeight
                        spacing: parent.space
                        enabled: !ConfigView.isAutoMode
                        opacity: enabled ? 1 : 0.5
                        Text {
                            text: qsTr("Outfeed cylinder") + ": "
                            width: parent.parent.textWidth
                            font.pointSize: _fontSize
                            color: _textColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        ButtonMaterialTextHorizontal{
                            id: outfeed_cylinder_open_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Open")
                            _iconSourceOn: "valveOpen"
                            _colorIconDefault: left_layout.openButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.openButtonIconHighColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.outfeedCylinder2OpenClose_Qml_Slot(true);
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }

                        ButtonMaterialTextHorizontal{
                            id: outfeed_cylinder_close_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Close")
                            _iconSourceOn: "valveClosed"
                            _colorIconDefault: left_layout.closeButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.closeButtonIconHighColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.outfeedCylinder2OpenClose_Qml_Slot(false);
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }
                    }

                    Row {
                        width: parent.width
                        height: parent.itemHeight
                        spacing: parent.space
                        enabled: !ConfigView.isAutoMode
                        opacity: enabled ? 1 : 0.5
                        Text {
                            text: qsTr("Rotate cylinder") + ": "
                            width: parent.parent.textWidth
                            font.pointSize: _fontSize
                            color: _textColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        ButtonMaterialTextHorizontal{
                            id: rotate_cylinder_open_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Open")
                            _iconSourceOn: "valveOpen"
                            _colorIconDefault: left_layout.openButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.openButtonIconHighColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.rotateCylinderOpenClose_Qml_Slot(true);
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }

                        ButtonMaterialTextHorizontal{
                            id: rotate_cylinder_close_btn
                            height: parent.height*0.9
                            width: parent.parent.buttonWidth
                            _size: height*0.8
                            _text: qsTr("Close")
                            _iconSourceOn: "valveClosed"
                            _colorIconDefault: left_layout.closeButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.closeButtonIconHighColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.rotateCylinderOpenClose_Qml_Slot(false);
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }
                    }

                    // Row {
                    //     width: parent.width
                    //     height: parent.itemHeight
                    //     spacing: parent.space
                    //     enabled: !ConfigView.isAutoMode
                    //     opacity: enabled ? 1 : 0.5
                    //     Rectangle {
                    //         color: "transparent"
                    //         width: parent.parent.textWidth
                    //         height: parent.height*0.9
                    //     }

                    //     ButtonMaterialTextHorizontal{
                    //         id: save_btn
                    //         height: parent.height*0.9
                    //         width: left_layout.buttonWidth
                    //         _size: height*0.8
                    //         _text: qsTr("Save")
                    //         _iconSourceOn: "databaseExport"
                    //         _colorIconDefault: left_layout.openButtonIconDefaultColor
                    //         _colorIconMouseOver: _colorIconDefault
                    //         _colorIconHigh: left_layout.openButtonIconDefaultColor
                    //         anchors.verticalCenter: parent.verticalCenter
                    //         _fontFamily: _fontFamily
                    //         _textRatio: 0.4
                    //         _numberStatus: 3
                    //         onClicked: {
                    //             _viewModel.save_Qml_Slot(scale_puhser_distance_text.getText(),
                    //                                      table_puhser_distance_text.getText(),
                    //                                      puhsup_distance_text.getText(),
                    //                                      test_bottle_distance_text.getText())
                    //             feeder_and_pusher_layout.resetAllButtonChecked();
                    //             setStatusSelected(true);
                    //         }
                    //     }


                    //     ButtonMaterialTextHorizontal{
                    //         id: cancel_btn
                    //         height: parent.height*0.9
                    //         width: left_layout.buttonWidth
                    //         _size: height*0.8
                    //         _text: qsTr("Cancel")
                    //         _iconSourceOn: "databaseExport"
                    //         _colorIconDefault: left_layout.closeButtonIconDefaultColor
                    //         _colorIconMouseOver: _colorIconDefault
                    //         _colorIconHigh: left_layout.closeButtonIconDefaultColor
                    //         anchors.verticalCenter: parent.verticalCenter
                    //         _fontFamily: _fontFamily
                    //         _textRatio: 0.4
                    //         _numberStatus: 3
                    //         onClicked: {
                    //             scale_puhser_distance_text.setText(_viewModel.scalePusherDistance)
                    //             table_puhser_distance_text.setText(_viewModel.tablePusherDistance)
                    //             puhsup_distance_text.setText(_viewModel.pushupDistance)
                    //             test_bottle_distance_text.setText(_viewModel.testBottleDiameter)
                    //             feeder_and_pusher_layout.resetAllButtonChecked();
                    //             setStatusSelected(true);
                    //         }
                    //     }

                    // }

                }


                Column {
                    id: right_layout
                    width: parent.width*0.5
                    height: parent.height
                    spacing: parent.height*0.06

                    property int textWidth: width*0.27
                    property int inputTextWidth: width*0.14
                    property int itemHeight: height*0.2
                    property int buttonWidth: width*0.35
                    property int space: width*0.02

                    Rectangle {
                        width: parent.width
                        height: left_layout.itemHeight
                        color: "transparent"


                        Text {
                            text: qsTr("Mode") + ": "
                            width: left_layout.buttonWidth/2
                            font.pointSize: _fontSize
                            color: _textColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                        }

                        ButtonMaterialTextHorizontal{
                            id: auto_btn
                            height: parent.height*0.9
                            width: left_layout.buttonWidth*1.2
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width*0.18
                            _size: height*0.8
                            _text: qsTr("Auto")
                            _iconSourceOn: "stateMachine"
                            _colorIconDefault: left_layout.openButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.openButtonIconHighColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.autoManualModeChanged_Qml_Slot(true);
                                ConfigView.isAutoMode = true
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }

                        ButtonMaterialTextHorizontal{
                            id: manual_btn
                            height: parent.height*0.9
                            width: left_layout.buttonWidth*1.2
                            anchors.right: parent.right
                            anchors.rightMargin: parent.width*0.09
                            _size: height*0.8
                            _text: qsTr("Manual")
                            _iconSourceOn: "accountEdit"
                            _colorIconDefault: left_layout.closeButtonIconDefaultColor
                            _colorIconMouseOver: _colorIconDefault
                            _colorIconHigh: left_layout.closeButtonIconHighColor
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: _fontFamily
                            _textRatio: 0.4
                            _numberStatus: 3
                            onClicked: {
                                _viewModel.autoManualModeChanged_Qml_Slot(false);
                                ConfigView.isAutoMode = false
                                feeder_and_pusher_layout.resetAllButtonChecked();
                                setStatusSelected(true);
                            }
                        }
                    }

                    C1_5.ScrollView {
                        width: parent.width*1
                        height: parent.height*0.8
                        clip: true
                        // anchors.horizontalCenter: parent.horizontalCenter
                        style: ScrollViewStyle {
                            property int iScrollWidth: 10
                            handle: Rectangle {
                                implicitWidth: iScrollWidth
                                color: "lightgray"
                                radius: 20
                            }
                            scrollBarBackground: Rectangle {
                                implicitWidth: iScrollWidth
                                color: "gray"
                                radius: 20
                            }
                            decrementControl: Rectangle {
                                implicitWidth: 0
                            }
                            incrementControl: Rectangle {
                                implicitWidth: 0
                            }
                        }

                        verticalScrollBarPolicy: Qt.ScrollBarAsNeeded
                        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                        flickableItem.flickableDirection : Flickable.VerticalFlick
                        flickableItem.boundsBehavior: Flickable.StopAtBounds

                        Column  {
                            width: right_layout.width
                            height: right_layout.itemHeight*10
                            anchors.horizontalCenter: parent.horizontalCenter
                            clip: true
                            enabled: !ConfigView.isAutoMode
                            opacity: enabled ? 1 : 0.5
                            spacing: right_layout.spacing

                            Row {
                                width: parent.width
                                height: right_layout.itemHeight
                                spacing: right_layout.space

                                Text {
                                    text: qsTr("Scale Pusher \nDistance") + ": "
                                    width: right_layout.textWidth
                                    font.pointSize: _fontSize
                                    color: _textColor
                                    font.family: _fontFamily
                                    verticalAlignment: Text.AlignVCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                InputText{
                                    _width: right_layout.inputTextWidth
                                    _height: parent.height*0.5
                                    _fontSizeText: _fontSize
                                    _text: _viewModel.scalePusherDistance.toFixed(1)
                                    _leftMagin: 0
                                    _readOnly: true
                                    anchors.verticalCenter: parent.verticalCenter
                                    _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                                    _inputMethodHints: Qt.ImhFormattedNumbersOnly
                                }

                                InputText{
                                    id: scale_puhser_distance_text
                                    _width: right_layout.inputTextWidth
                                    _height: parent.height*0.5
                                    _fontSizeText: _fontSize
                                    _text: "0"
                                    _leftMagin: 0
                                    anchors.verticalCenter: parent.verticalCenter
                                    _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                                    _inputMethodHints: Qt.ImhFormattedNumbersOnly
                                }

                                Column {
                                    width: right_layout.buttonWidth
                                    height: parent.height
                                    spacing: height*0.1

                                    ButtonMaterialTextHorizontal{
                                        id: scale_pusher_move_btn
                                        height: parent.height*0.5
                                        width: parent.width
                                        _size: height*0.8
                                        _text: qsTr("Scale Pusher Move")
                                        _iconSourceOn: "applicationImport"
                                        _colorIconDefault: left_layout.openButtonIconDefaultColor
                                        _colorIconMouseOver: _colorIconDefault
                                        _colorIconHigh: left_layout.openButtonIconHighColor
                                        _fontFamily: _fontFamily
                                        _textRatio: 0.27
                                        _numberStatus: 3
                                        onClicked: {
                                            _viewModel.scalePusherInOut_Qml_Slot(true, scale_puhser_distance_text.getText());
                                            feeder_and_pusher_layout.resetAllButtonChecked();
                                            setStatusSelected(true);
                                        }
                                    }

                                    ButtonMaterialTextHorizontal{
                                        id: scale_pusher_home_btn
                                        height: parent.height*0.5
                                        width: parent.width
                                        _size: height*0.8
                                        _text: qsTr("Home Position")
                                        _iconSourceOn: "home"
                                        _colorIconMouseOver: _colorIconDefault
                                        _fontFamily: _fontFamily
                                        _textRatio: 0.27
                                        _numberStatus: 3
                                        onClicked: {
                                            _viewModel.scalePusherInOut_Qml_Slot(false, scale_puhser_distance_text.getText());
                                            feeder_and_pusher_layout.resetAllButtonChecked();
                                            setStatusSelected(true);
                                        }
                                    }
                                }


                            }

                            Row {
                                width: parent.width
                                height: right_layout.itemHeight
                                spacing: right_layout.space

                                Text {
                                    text: qsTr("Table Pusher \nDistance") + ": "
                                    width: right_layout.textWidth
                                    font.pointSize: _fontSize
                                    color: _textColor
                                    font.family: _fontFamily
                                    verticalAlignment: Text.AlignVCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                InputText{
                                    _width: right_layout.inputTextWidth
                                    _height: parent.height*0.5
                                    _fontSizeText: _fontSize
                                    _text: _viewModel.tablePusherDistance.toFixed(1)
                                    _leftMagin: 0
                                    _readOnly: true
                                    anchors.verticalCenter: parent.verticalCenter
                                    _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                                    _inputMethodHints: Qt.ImhFormattedNumbersOnly
                                }

                                InputText{
                                    id: table_puhser_distance_text
                                    _width: right_layout.inputTextWidth
                                    _height: parent.height*0.5
                                    _fontSizeText: _fontSize
                                    _text: "0"
                                    _leftMagin: 0
                                    anchors.verticalCenter: parent.verticalCenter
                                    _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                                    _inputMethodHints: Qt.ImhFormattedNumbersOnly
                                }

                                Column {
                                    width: right_layout.buttonWidth
                                    height: parent.height
                                    spacing: height*0.1

                                    ButtonMaterialTextHorizontal{
                                        id: table_pusher_move_btn
                                        height: parent.height*0.5
                                        width: parent.width
                                        _size: height*0.8
                                        _text: qsTr("Table Pusher Move")
                                        _iconSourceOn: "applicationImport"
                                        _colorIconDefault: left_layout.openButtonIconDefaultColor
                                        _colorIconMouseOver: _colorIconDefault
                                        _colorIconHigh: left_layout.openButtonIconHighColor
                                        _fontFamily: _fontFamily
                                        _textRatio: 0.27
                                        _numberStatus: 3
                                        onClicked: {
                                            _viewModel.tablePusherInOut_Qml_Slot(true, table_puhser_distance_text.getText());
                                            feeder_and_pusher_layout.resetAllButtonChecked();
                                            setStatusSelected(true);
                                        }
                                    }



                                    ButtonMaterialTextHorizontal{
                                        id: table_pusher_home_btn
                                        height: parent.height*0.5
                                        width: parent.width
                                        _size: height*0.8
                                        _text: qsTr("Home Position")
                                        _iconSourceOn: "home"
                                        _colorIconMouseOver: _colorIconDefault
                                        _fontFamily: _fontFamily
                                        _textRatio: 0.27
                                        _numberStatus: 3
                                        onClicked: {
                                            _viewModel.tablePusherInOut_Qml_Slot(false, table_puhser_distance_text.getText());
                                            feeder_and_pusher_layout.resetAllButtonChecked();
                                            setStatusSelected(true);
                                        }
                                    }
                                }


                            }

                            Row {
                                width: parent.width
                                height: right_layout.itemHeight/2
                                spacing: right_layout.space

                                Text {
                                    text: qsTr("Pushup \nDistance") + ": "
                                    width: right_layout.textWidth
                                    font.pointSize: _fontSize
                                    color: _textColor
                                    font.family: _fontFamily
                                    verticalAlignment: Text.AlignVCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                InputText{
                                    id: puhsup_distance_text
                                    _width: right_layout.inputTextWidth
                                    _height: parent.height
                                    _fontSizeText: _fontSize
                                    _text: _viewModel.pushupDistance.toFixed(1)
                                    _leftMagin: 0
                                    _readOnly: true
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                Rectangle {
                                    width: right_layout.inputTextWidth
                                    height: parent.height
                                    color: "transparent"
                                }

                                // Text
                                // {
                                //    height: parent.height
                                //    width: parent.parent.inputTextWidth
                                //    font.family: _fontFamily
                                //    text: _viewModel.pushupDistance
                                //    font.pixelSize: height*0.5
                                //    wrapMode: Text.WordWrap
                                //    lineHeight: 0.5
                                // }
                                ButtonMaterialTextHorizontal{
                                    id: pushup_distance_reset_btn
                                    height: parent.height
                                    width: right_layout.buttonWidth
                                    _size: height*0.8
                                    _text: qsTr("Reset")
                                    _iconSourceOn: "fileEdit"
                                    _colorIconMouseOver: _colorIconDefault
                                    _fontFamily: _fontFamily
                                    _textRatio: 0.27
                                    _numberStatus: 3
                                    onClicked: {
                                        _viewModel.resetPushupDistance_Qml_Slot();
                                        feeder_and_pusher_layout.resetAllButtonChecked();
                                        setStatusSelected(true);
                                    }
                                }
                            }

                            Row {
                                width: parent.width
                                height: right_layout.itemHeight/2
                                spacing: right_layout.space

                                Text {
                                    text: qsTr("Scale") + ": "
                                    width: right_layout.textWidth
                                    font.pointSize: _fontSize
                                    color: _textColor
                                    font.family: _fontFamily
                                    verticalAlignment: Text.AlignVCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                InputText{
                                    _width: right_layout.inputTextWidth
                                    _height: parent.height
                                    _fontSizeText: _fontSize
                                    _text: _viewModel.scaleValue
                                    _leftMagin: 0
                                    _readOnly: true
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                Rectangle {
                                    width: right_layout.inputTextWidth
                                    height: parent.height
                                    color: "transparent"
                                }

                                ButtonMaterialTextHorizontal{
                                    id: scale_reset_btn
                                    height: parent.height
                                    width: right_layout.buttonWidth
                                    _size: height*0.8
                                    _text: qsTr("Reset")
                                    _iconSourceOn: "fileEdit"
                                    _colorIconMouseOver: _colorIconDefault
                                    _fontFamily: _fontFamily
                                    _textRatio: 0.27
                                    _numberStatus: 3
                                    onClicked: {
                                        _viewModel.resetScale_Qml_Slot();
                                        feeder_and_pusher_layout.resetAllButtonChecked();
                                        setStatusSelected(true);
                                    }
                                }
                            }

                            // Row {
                            //     width: parent.width
                            //     height: right_layout.itemHeight
                            //     spacing: right_layout.space

                            //     Text {
                            //         text: qsTr("Test Bottle \nDiameter") + ": "
                            //         width: right_layout.textWidth
                            //         font.pointSize: _fontSize
                            //         color: _textColor
                            //         font.family: _fontFamily
                            //         verticalAlignment: Text.AlignVCenter
                            //         anchors.verticalCenter: parent.verticalCenter
                            //     }

                            //     InputText{
                            //         id: test_bottle_distance_text
                            //         _width: right_layout.inputTextWidth
                            //         _height: parent.height*0.5
                            //         _fontSizeText: _fontSize
                            //         _text: _viewModel.testBottleDiameter
                            //         _leftMagin: 0
                            //         anchors.verticalCenter: parent.verticalCenter
                            //         _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                            //     }

                            //     Rectangle {
                            //         width: right_layout.inputTextWidth
                            //         height: parent.height
                            //         color: "transparent"
                            //     }

                            //     Column {
                            //         width: right_layout.buttonWidth
                            //         height: parent.height
                            //         spacing: height*0.1

                            //         ButtonMaterialTextHorizontal{
                            //             id: test_bottle_diameter_test_btn
                            //             height: parent.height*0.5
                            //             width: parent.width
                            //             _size: height*0.8
                            //             _text: qsTr("Test")
                            //             _iconSourceOn: "fileEdit"
                            //             _colorIconDefault: left_layout.openButtonIconDefaultColor
                            //             _colorIconMouseOver: _colorIconDefault
                            //             _colorIconHigh: left_layout.openButtonIconHighColor
                            //             _fontFamily: _fontFamily
                            //             _textRatio: 0.27
                            //             _numberStatus: 3
                            //             onClicked: {
                            //                 _viewModel.test_Qml_Slot(test_bottle_distance_text.getText());
                            //                 feeder_and_pusher_layout.resetAllButtonChecked();
                            //                 setStatusSelected(true);
                            //             }
                            //         }

                            //         ButtonMaterialTextHorizontal{
                            //             id: test_bottle_diameter_push_home_btn
                            //             height: parent.height*0.5
                            //             width: parent.width
                            //             _size: height*0.8
                            //             _text: qsTr("Push Home")
                            //             _iconSourceOn: "home"
                            //             _colorIconMouseOver: _colorIconDefault
                            //             _fontFamily: _fontFamily
                            //             _textRatio: 0.27
                            //             _numberStatus: 3
                            //             onClicked: {
                            //                 _viewModel.pushHome_Qml_Slot(test_bottle_distance_text.getText());
                            //                 feeder_and_pusher_layout.resetAllButtonChecked();
                            //                 setStatusSelected(true);
                            //             }
                            //         }
                            //     }
                            // }

                            Row {
                                width: parent.width
                                height: right_layout.itemHeight
                                spacing: right_layout.space
                                visible: false

                                Text {
                                    text: qsTr("Motor \nCamera") + ": "
                                    width: right_layout.textWidth
                                    font.pointSize: _fontSize
                                    color: _textColor
                                    font.family: _fontFamily
                                    verticalAlignment: Text.AlignVCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                InputText{
                                    _width: right_layout.inputTextWidth
                                    _height: parent.height*0.5
                                    _fontSizeText: _fontSize
                                    _text: _viewModel.motorCameraValue.toFixed(1)
                                    _leftMagin: 0
                                    _readOnly: true
                                    anchors.verticalCenter: parent.verticalCenter
                                    _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                                    _inputMethodHints: Qt.ImhFormattedNumbersOnly
                                }

                                InputText{
                                    id: motor_camera_text
                                    _width: right_layout.inputTextWidth
                                    _height: parent.height*0.5
                                    _fontSizeText: _fontSize
                                    _text: "0"
                                    _leftMagin: 0
                                    anchors.verticalCenter: parent.verticalCenter
                                    _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                                    _inputMethodHints: Qt.ImhFormattedNumbersOnly
                                }

                                Column {
                                    width: right_layout.buttonWidth
                                    height: parent.height
                                    spacing: height*0.1

                                    ButtonMaterialTextHorizontal{
                                        id: motor_camera_move_btn
                                        height: parent.height*0.5
                                        width: parent.width
                                        _size: height*0.8
                                        _text: qsTr("Motor Camera Move")
                                        _iconSourceOn: "applicationImport"
                                        _colorIconDefault: left_layout.openButtonIconDefaultColor
                                        _colorIconMouseOver: _colorIconDefault
                                        _colorIconHigh: left_layout.openButtonIconHighColor
                                        _fontFamily: _fontFamily
                                        _textRatio: 0.27
                                        _numberStatus: 3
                                        onClicked: {
                                            _viewModel.motorCameraMove_Qml_Slot(true, motor_camera_text.getText());
                                            feeder_and_pusher_layout.resetAllButtonChecked();
                                            setStatusSelected(true);
                                        }
                                    }

                                    ButtonMaterialTextHorizontal{
                                        id: motor_camera_home_btn
                                        height: parent.height*0.5
                                        width: parent.width
                                        _size: height*0.8
                                        _text: qsTr("Home Position")
                                        _iconSourceOn: "home"
                                        _colorIconMouseOver: _colorIconDefault
                                        _fontFamily: _fontFamily
                                        _textRatio: 0.27
                                        _numberStatus: 3
                                        onClicked: {
                                            _viewModel.motorCameraMove_Qml_Slot(false, motor_camera_text.getText());
                                            feeder_and_pusher_layout.resetAllButtonChecked();
                                            setStatusSelected(true);
                                        }
                                    }
                                }


                            }

                            Row {
                                width: parent.width
                                height: right_layout.itemHeight
                                spacing: right_layout.space

                                Text {
                                    text: qsTr("Air Compressor") + ": "
                                    width: right_layout.textWidth
                                    font.pointSize: _fontSize
                                    color: _textColor
                                    font.family: _fontFamily
                                    verticalAlignment: Text.AlignVCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                Rectangle {
                                    width: right_layout.inputTextWidth
                                    height: parent.height*0.5
                                    color: "transparent"
                                }


                                Rectangle {
                                    width: right_layout.inputTextWidth
                                    height: parent.height*0.5
                                    color: "transparent"
                                }

                                Column {
                                    width: right_layout.buttonWidth
                                    height: parent.height
                                    spacing: height*0.1

                                    ButtonMaterialTextHorizontal{
                                        id: air_compressor_open_btn
                                        height: parent.height*0.5
                                        width: parent.width
                                        _size: height*0.8
                                        _text: qsTr("Open")
                                        _iconSourceOn: "valveOpen"
                                        _colorIconDefault: ConfigView.acceptSignalColor
                                        _colorIconMouseOver: _colorIconDefault
                                        _fontFamily: _fontFamily
                                        _textRatio: 0.27
                                        _numberStatus: 3
                                        onClicked: {
                                            _viewModel.airCompressorChanged_Qml_Slot(true);
                                            feeder_and_pusher_layout.resetAllButtonChecked();
                                            setStatusSelected(true);
                                        }
                                    }

                                    ButtonMaterialTextHorizontal{
                                        id: air_compressor_close_btn
                                        height: parent.height*0.5
                                        width: parent.width
                                        _size: height*0.8
                                        _text: qsTr("Close")
                                        _iconSourceOn: "valveClosed"
                                        _colorIconMouseOver: _colorIconDefault
                                        _fontFamily: _fontFamily
                                        _textRatio: 0.27
                                        _numberStatus: 3
                                        onClicked: {
                                            _viewModel.airCompressorChanged_Qml_Slot(false);
                                            feeder_and_pusher_layout.resetAllButtonChecked();
                                            setStatusSelected(true);
                                        }
                                    }
                                }


                            }

                            Row {
                                width: parent.width
                                height: right_layout.itemHeight
                                spacing: right_layout.space

                                Text {
                                    text: qsTr("Vaccum Ejector") + ": "
                                    width: right_layout.textWidth
                                    font.pointSize: _fontSize
                                    color: _textColor
                                    font.family: _fontFamily
                                    verticalAlignment: Text.AlignVCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                Rectangle {
                                    width: right_layout.inputTextWidth
                                    height: parent.height*0.5
                                    color: "transparent"
                                }


                                Rectangle {
                                    width: right_layout.inputTextWidth
                                    height: parent.height*0.5
                                    color: "transparent"
                                }

                                Column {
                                    width: right_layout.buttonWidth
                                    height: parent.height
                                    spacing: height*0.1

                                    ButtonMaterialTextHorizontal{
                                        id: vaccum_ejector_open_btn
                                        height: parent.height*0.5
                                        width: parent.width
                                        _size: height*0.8
                                        _text: qsTr("Open")
                                        _iconSourceOn: "valveOpen"
                                        _colorIconDefault: ConfigView.acceptSignalColor
                                        _colorIconMouseOver: _colorIconDefault
                                        _fontFamily: _fontFamily
                                        _textRatio: 0.27
                                        _numberStatus: 3
                                        onClicked: {
                                            _viewModel.vaccumEjectorChanged_Qml_Slot(true);
                                            feeder_and_pusher_layout.resetAllButtonChecked();
                                            setStatusSelected(true);
                                        }
                                    }

                                    ButtonMaterialTextHorizontal{
                                        id: vaccum_ejector_close_btn
                                        height: parent.height*0.5
                                        width: parent.width
                                        _size: height*0.8
                                        _text: qsTr("Close")
                                        _iconSourceOn: "valveClosed"
                                        _colorIconMouseOver: _colorIconDefault
                                        _fontFamily: _fontFamily
                                        _textRatio: 0.27
                                        _numberStatus: 3
                                        onClicked: {
                                            _viewModel.vaccumEjectorChanged_Qml_Slot(false);
                                            feeder_and_pusher_layout.resetAllButtonChecked();
                                            setStatusSelected(true);
                                        }
                                    }
                                }


                            }


                        }
                    }
                }
            }
        }
    }


    Connections {
        target: _viewModel
        function onConveyorStartStop_Qml_Signal(value) {
            conveyor_start_stop_btn.changeButtonStatus(value)
        }
    }

}

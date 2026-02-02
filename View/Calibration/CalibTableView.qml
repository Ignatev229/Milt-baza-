import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3

import ConfigView 1.0

import "../../Component/MaterialDesign"
import "../../Component"

import "../../View"

Item {
    id: calibration_table
    width: parent.width
    height: parent.height
    property QtObject _viewModel: QtObject{}
    property QtObject _homeModel: mainHomeVM
    property string _fontFamily: ConfigView.fontFamily
    property int _fontSize: 14
    property color _textColor: ConfigView.mainBlueColor

    QtObject{
        id: internal_calibration_table
        property bool isDoubleClick: cam_main_id_1.isDoubleClick || cam_main_id_2.isDoubleClick/* || cam_main_id_3.isDoubleClick*/

    }

    function zoomInOneTrack(trackIndex: int){
        if(trackIndex === 0){
            cam_main_id_1.isDoubleClick = !cam_main_id_1.isDoubleClick
            if(cam_main_id_1.isDoubleClick){
                cam_main_id_2.visible = false
                // cam_main_id_3.visible = false
            }
            else{
                cam_main_id_2.visible = true
                // cam_main_id_3.visible = true
            }
        }
        else if(trackIndex === 1){
            cam_main_id_2.isDoubleClick = !cam_main_id_2.isDoubleClick
            if(cam_main_id_2.isDoubleClick){
                cam_main_id_1.visible = false
                // cam_main_id_3.visible = false
            }
            else{
                cam_main_id_1.visible = true
                // cam_main_id_3.visible = true
            }
        }
        // else if(trackIndex === 2){
        //     cam_main_id_3.isDoubleClick = !cam_main_id_3.isDoubleClick
        //     if(cam_main_id_3.isDoubleClick){
        //         cam_main_id_1.visible = false
        //         cam_main_id_2.visible = false
        //     }
        //     else{
        //         cam_main_id_1.visible = true
        //         cam_main_id_2.visible = true
        //     }
        // }
    }



    function processMouseActionFromTrack(trackIndex: int, mouseType: int){
        if(mouseType === ConfigView.MOUSE_ACTION.LEFT_CLICK){

        }
        else if(mouseType === ConfigView.MOUSE_ACTION.RIGHT_CLICK){

        }
        else if(mouseType === ConfigView.MOUSE_ACTION.LEFT_DOUBLE_CLICK){
            zoomInOneTrack(trackIndex)
            cam_main_id_1.updateCalibGrib()
            cam_main_id_2.updateCalibGrib()
            // cam_main_id_3.updateCalibGrib()
        }
        else if(mouseType === ConfigView.MOUSE_ACTION.RIGHT_DOUBLE_CLICK){

        }
    }


    Row {
        id: calib_layout
        width: parent.width*0.98
        height: parent.height*0.9
        anchors.centerIn: parent
        spacing: parent.width*0.01


        Column {
            width: parent.width*0.16
            height: parent.height
            spacing: parent.height*0.06


            ComboBoxCustom{
                id: calib_pos
                ListModel {
                    id: calib_pos_model
                    ListElement { text: qsTr("Camera 1") }
                    ListElement { text: qsTr("Camera 2") }
                }
                _model: calib_pos_model
                width: parent.width*0.8
                height: parent.height*0.1
                _fontSize: calibration_table._fontSize
                currentIndex: 0
                anchors.horizontalCenter: parent.horizontalCenter
                onCurrentTextChanged:{
                    _viewModel.cameraCalibIndexChanged_Qml_Slot(currentIndex)
                }
            }

            ButtonMaterialTextHorizontal{
                id: combine_btn
                height: parent.height*0.1
                width: parent.width*0.8
                _size: height*0.8
                _text: qsTr("Combine")
                _iconSourceOn: "vectorCombine"
                _colorIconDefault: ConfigView.mainBlueColor
                _colorIconMouseOver: _colorIconDefault
                _colorIconHigh: ConfigView.mainBlueColor
                anchors.horizontalCenter: parent.horizontalCenter
                _fontFamily: _fontFamily
                _textRatio: 0.27
                onClicked: {
                    _viewModel.combineImage_Qml_Slot()
                }
            }

            ButtonMaterialTextHorizontal{
                height: parent.height*0.1
                width: parent.width*0.8
                _size: height*0.8
                _text: qsTr("Save")
                _iconSourceOn: "databaseExport"
                _colorIconDefault: ConfigView.mainBlueColor
                _colorIconMouseOver: _colorIconDefault
                _colorIconHigh: ConfigView.mainBlueColor
                anchors.horizontalCenter: parent.horizontalCenter
                _fontFamily: _fontFamily
                _textRatio: combine_btn._textRatio
                onClicked: {
                    _viewModel.saveCameraCalib_Qml_Slot();
                }
            }


            ToggleButtonMaterialTextHorizontal{
                id: show_calib_grid
                height: parent.height*0.1
                width: parent.width*0.8
                _size: height*0.8
                _text: _isClicked ? qsTr("Hide Grid") : qsTr("Show Grid")
                _iconSourceOn: "gridOff"
                _iconSourceOff: "grid"
                _colorIconDefault: ConfigView.mainBlueColor
                _colorIconMouseOver: _colorIconDefault
                _colorIconHigh: ConfigView.mainWhiteColor
                anchors.horizontalCenter: parent.horizontalCenter
                _fontFamily: _fontFamily
                _textRatio: combine_btn._textRatio
                onClicked: {
                    cam_main_id_1._isShowCalibGrib = _isClicked
                    cam_main_id_2._isShowCalibGrib = _isClicked
                    // cam_main_id_3._isShowCalibGrib = _isClicked
                    if(_isClicked){
                        cam_main_id_1.updateCalibGrib()
                        cam_main_id_2.updateCalibGrib()
                        // cam_main_id_3.updateCalibGrib()
                    }

                }
            }

            ToggleButtonMaterialTextHorizontal{
                id: calib_camera_pos_btn
                // visible: false
                height: parent.height*0.1
                width: parent.width*0.8
                _size: height*0.8
                _text: _isClicked ? qsTr("Camera \nPosition") : qsTr("Camera \nPosition")
                _iconSourceOn: "tuneVertical"
                _iconSourceOff: "tuneVertical"
                _colorIconDefault: ConfigView.mainBlueColor
                _colorIconMouseOver: _colorIconDefault
                _colorIconHigh: ConfigView.mainWhiteColor
                anchors.horizontalCenter: parent.horizontalCenter
                _fontFamily: _fontFamily
                _textRatio: combine_btn._textRatio
                onClicked: {
                    calib_camera_pos_layout.visible = _isClicked
                }
            }

        }

        Rectangle {
            width: parent.width*0.3
            height: parent.height
            color: "transparent"
            // border.color: "#007ACC"
            // border.width: 2
            // radius: 5

            Row {
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
                visible: !calib_camera_pos_layout.visible

                Column {
                    width: parent.width*0.5
                    height: parent.height
                    spacing: parent.height*0.03


                    Text {
                        text: qsTr("Table Elevation")
                        width: parent.width*0.8
                        height: parent.height*0.1
                        font.pointSize: _fontSize + 5
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        text: tableVM.tableElevationValue.toFixed(1)
                        width: parent.width*0.5
                        height: parent.height*0.1
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    InputText{
                        id: table_elevation_pos_text
                        _width: parent.width*0.5
                        _height: parent.height*0.1
                        _fontSizeText: _fontSize
                        _text: "0"//_viewModel.tableElevationValue
                        _leftMagin: 0
                        anchors.horizontalCenter: parent.horizontalCenter
                        _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                    }

                    ButtonMaterial{
                        _width: parent.width*0.5
                        _height: _width
                        _size: _height*0.9
                        _radiusCorner: _width/2
                        _iconSourceOn: "arrowUpBold"
                        _colorBGDefault: ConfigView.mainWhiteColor
                        _colorBGMouseOver: ConfigView.mainBlueColor
                        _colorBGHigh: ConfigView.mainBlueColor
                        _colorBorder: ConfigView.mainBlueColor
                        _colorIconHigh: ConfigView.mainBlueColor
                        _colorIconDefault: ConfigView.mainBlueColor
                        _colorIconMouseOver: ConfigView.mainWhiteColor
                        anchors.horizontalCenter: parent.horizontalCenter
                        onClicked: {
                            tableVM.tableElevationGo_Qml_Slot(table_elevation_pos_text.getText())
                        }
                    }

                    // ButtonMaterial{
                    //     _width: parent.width*0.6
                    //     _height: _width
                    //     _size: _height*0.9
                    //     _radiusCorner: _width/2
                    //     _iconSourceOn: "chevronDown"
                    //     _colorBGDefault: "#424343"
                    //     _colorBGMouseOver: "#5E5F60"
                    //     _colorBGHigh: "#083A6A"
                    //     _colorBorder: "#797979"
                    //     _colorIconHigh: "#FFCE44"
                    //     _colorIconDefault: ConfigView.mainBlueColor
                    //     anchors.horizontalCenter: parent.horizontalCenter
                    //     onClicked: {
                    //         _viewModel.tableElevationDown_Qml_Slot(table_elevation_text.getText())
                    //     }
                    // }

                    ButtonMaterial{
                        _width: parent.width*0.5
                        _height: parent.height*0.14
                        _size: _height*0.9
                        _iconSourceOn: "home"
                        _colorBGDefault: ConfigView.addLightBlueColor
                        _colorBGMouseOver: ConfigView.mainWhiteColor
                        _colorBGHigh: ConfigView.addLightBlueColor
                        _colorBorder: ConfigView.mainBlueColor
                        _colorIconHigh: ConfigView.mainBlueColor
                        _colorIconDefault: ConfigView.mainWhiteColor
                        _colorIconMouseOver: ConfigView.addLightBlueColor
                        anchors.horizontalCenter: parent.horizontalCenter
                        onClicked: {
                            tableVM.tableElevationHome_Qml_Slot()
                        }
                    }


                }

                Column {
                    width: parent.width*0.5
                    height: parent.height
                    spacing: parent.height*0.03


                    Text {
                        text: qsTr("Table Angle")
                        width: parent.width*0.8
                        height: parent.height*0.1
                        font.pointSize: _fontSize + 5
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        text: tableVM.tableAngleValue.toFixed(1)
                        width: parent.width*0.5
                        height: parent.height*0.1
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    InputText{
                        id: table_angle_pos_text
                        _width: parent.width*0.5
                        _height: parent.height*0.1
                        _fontSizeText: _fontSize
                        _text: "0"//_viewModel.tableAngleValue
                        _leftMagin: 0
                        anchors.horizontalCenter: parent.horizontalCenter
                        _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                    }

                    ButtonMaterial{
                        _width: parent.width*0.5
                        _height: _width
                        _size: _height*0.9
                        _radiusCorner: _width/2
                        _iconSourceOn: "axisZRotateCounterclockwise"
                        _colorBGDefault: ConfigView.mainWhiteColor
                        _colorBGMouseOver: ConfigView.mainBlueColor
                        _colorBGHigh: ConfigView.mainBlueColor
                        _colorBorder: ConfigView.mainBlueColor
                        _colorIconHigh: ConfigView.mainBlueColor
                        _colorIconDefault: ConfigView.mainBlueColor
                        _colorIconMouseOver: ConfigView.mainWhiteColor
                        anchors.horizontalCenter: parent.horizontalCenter
                        onClicked: {
                            tableVM.tableAngleRotateLeft_Qml_Slot(table_angle_pos_text.getText())
                        }
                    }

                    ButtonMaterial{
                        _width: parent.width*0.5
                        _height: _width
                        _size: _height*0.9
                        _radiusCorner: _width/2
                        _iconSourceOn: "axisZRotateClockwise"
                        _colorBGDefault: ConfigView.mainWhiteColor
                        _colorBGMouseOver: ConfigView.mainBlueColor
                        _colorBGHigh: ConfigView.mainBlueColor
                        _colorBorder: ConfigView.mainBlueColor
                        _colorIconHigh: ConfigView.mainBlueColor
                        _colorIconDefault: ConfigView.mainBlueColor
                        _colorIconMouseOver: ConfigView.mainWhiteColor
                        anchors.horizontalCenter: parent.horizontalCenter
                        onClicked: {
                            tableVM.tableAngleRotateRight_Qml_Slot(table_angle_pos_text.getText())
                        }
                    }

                    ButtonMaterial{
                        _width: parent.width*0.5
                        _height: parent.height*0.14
                        _size: _height*0.9
                        _iconSourceOn: "home"
                        _colorBGDefault: ConfigView.addLightBlueColor
                        _colorBGMouseOver: ConfigView.mainWhiteColor
                        _colorBGHigh: ConfigView.addLightBlueColor
                        _colorBorder: ConfigView.mainBlueColor
                        _colorIconHigh: ConfigView.mainBlueColor
                        _colorIconDefault: ConfigView.mainWhiteColor
                        _colorIconMouseOver: ConfigView.addLightBlueColor
                        anchors.horizontalCenter: parent.horizontalCenter
                        onClicked: {
                            tableVM.tableAngleHome_Qml_Slot()
                        }
                    }


                }
            }

            Column {
                id: calib_camera_pos_layout
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
                visible: false
                spacing: height*0.01

                property int textWidth: width*0.7
                property int itemHeight: height*0.1

                Text {
                    text: qsTr("1. Change to Manual mode.\n"+
                                "2. Place the calibration tool on the table.\n"+
                                "3. Input the calibration tool Width and Height.\n"+
                                "4. Input the table position for Bottom camera can clearly view the top of the calibration tool.\n"+
                                "5. Input the table position for Bottom camera can clearly view the bottom of the calibration tool.\n"+
                                "6. Input the table position for Top camera can clearly view the top of the calibration tool.")
                    width: parent.width
                    font.pointSize: _fontSize - 2
                    color: "#D69545"
                    font.family: _fontFamily
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    anchors.horizontalCenter: parent.horizontalCenter
                    wrapMode: Text.WordWrap
                }

                Row {
                    width: parent.width
                    height: calib_camera_pos_layout.itemHeight
                    // spacing: parent.width*0.04

                    Text {
                        text: qsTr("Calibration Tool Height") + ": "
                        width: calib_camera_pos_layout.textWidth
                        font.pointSize: calib_tool_height_text._fontSizeText
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    InputText{
                        id: calib_tool_height_text
                        _width: calib_camera_pos_layout.textWidth*0.4
                        _height: parent.height*0.8
                        _fontSizeText: _fontSize - 2
                        _text: "0"
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                    }
                }

                Row {
                    width: parent.width
                    height: calib_camera_pos_layout.itemHeight
                    // spacing: parent.width*0.04

                    Text {
                        text: qsTr("Calibration Tool Width") + ": "
                        width: calib_camera_pos_layout.textWidth
                        font.pointSize: calib_tool_height_text._fontSizeText
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    InputText{
                        id: calib_tool_width_text
                        _width: calib_tool_height_text._width
                        _height: parent.height*0.8
                        _fontSizeText: calib_tool_height_text._fontSizeText
                        _text: "0"
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                    }
                }

                Row {
                    width: parent.width
                    height: calib_camera_pos_layout.itemHeight
                    // spacing: parent.width*0.04

                    Text {
                        text: qsTr("Table Elevation Bottom") + " 1: "
                        width: calib_camera_pos_layout.textWidth
                        font.pointSize: calib_tool_height_text._fontSizeText
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    InputText{
                        id: table_elevation_bottom_pos_1_text
                        _width: calib_tool_height_text._width
                        _height: parent.height*0.8
                        _fontSizeText: calib_tool_height_text._fontSizeText
                        _text: "0"
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                    }
                }

                Row {
                    width: parent.width
                    height: calib_camera_pos_layout.itemHeight
                    // spacing: parent.width*0.04

                    Text {
                        text: qsTr("Table Elevation Bottom") + " 2: "
                        width: calib_camera_pos_layout.textWidth
                        font.pointSize: calib_tool_height_text._fontSizeText
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    InputText{
                        id: table_elevation_bottom_pos_2_text
                        _width: calib_tool_height_text._width
                        _height: parent.height*0.8
                        _fontSizeText: calib_tool_height_text._fontSizeText
                        _text: "0"
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                    }
                }

                Row {
                    width: parent.width
                    height: calib_camera_pos_layout.itemHeight
                    // spacing: parent.width*0.04

                    Text {
                        text: qsTr("Table Elevation Top") + ": "
                        width: calib_camera_pos_layout.textWidth
                        font.pointSize: calib_tool_height_text._fontSizeText
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    InputText{
                        id: table_elevation_top_pos_text
                        _width: calib_tool_height_text._width
                        _height: parent.height*0.8
                        _fontSizeText: calib_tool_height_text._fontSizeText
                        _text: "0"
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                    }
                }

                BusyIndicator {
                    id: busyAnimation
                    visible: false
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: height
                    height: parent.height*0.16
                    running: visible
                }

                Row {
                    width: parent.width*0.9
                    height: parent.height*0.1
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: width*0.2
                    visible: !busyAnimation.visible


                    // ButtonMaterialTextHorizontal{
                    //     height: parent.height*0.9
                    //     width: parent.width*0.4
                    //     _size: height*0.8
                    //     _text: qsTr("Cancel")
                    //     _iconSourceOn: "cancel"
                    //     _colorIconDefault: ConfigView.mainBlueColor
                    //     _colorIconMouseOver: _colorIconDefault
                    //     _colorIconHigh: ConfigView.mainBlueColor
                    //     anchors.verticalCenter: parent.verticalCenter
                    //     _fontFamily: _fontFamily
                    //     _textRatio: 0.28
                    //     onClicked: {
                    //         busyAnimation.visible = false
                    //         _viewModel.calibCameraPos_Qml_Slot(false,
                    //             calib_tool_height_text.getText(),
                    //             calib_tool_width_text.getText(),
                    //             table_elevation_bottom_pos_1_text.getText(),
                    //             table_elevation_bottom_pos_2_text.getText(),
                    //             table_elevation_top_pos_text.getText())
                    //     }
                    // }

                    ButtonMaterialTextHorizontal{
                        height: parent.height*0.9
                        width: parent.width*0.55
                        _size: height*0.8
                        _text: qsTr("Calibration")
                        _iconSourceOn: "tuneVertical"
                        _colorIconDefault: ConfigView.mainBlueColor
                        _colorIconMouseOver: _colorIconDefault
                        _colorIconHigh: ConfigView.mainBlueColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        _fontFamily: _fontFamily
                        _textRatio: 0.28
                        onClicked: {
                            busyAnimation.visible = true
                            _viewModel.calibCameraPos_Qml_Slot(true,
                                calib_tool_height_text.getText(),
                                calib_tool_width_text.getText(),
                                table_elevation_bottom_pos_1_text.getText(),
                                table_elevation_bottom_pos_2_text.getText(),
                                table_elevation_top_pos_text.getText())
                        }
                    }
                }
            }
        }

        Column {
            width: parent.width*0.5
            height: parent.height
            spacing: parent.height*0.01

            Track{
                id: cam_main_id_1
                property bool  isDoubleClick: false
                width: parent.width
                height: isDoubleClick ? parent.height : parent.height*0.5
                _viewModel: _homeModel.listTrackVM[0]
                _numVerticalCell: _homeModel.numVerticalCell[0]
                _numHorizontalCell: _homeModel.numHorizontalCell[0]
                _isPickTrack: true
                // _isShowCalibGrib: show_calib_grid._isClicked
                onTrackMouseAction_Signal:(type) => {
                    processMouseActionFromTrack(0, type)
                }
            }

            Track{
                id: cam_main_id_2
                property bool  isDoubleClick: false
                width: parent.width
                height: isDoubleClick ? parent.height : parent.height*0.5
                _viewModel: _homeModel.listTrackVM[1]
                _numVerticalCell: _homeModel.numVerticalCell[1]
                _numHorizontalCell: _homeModel.numHorizontalCell[1]
                _isPickTrack: true
                // _isShowCalibGrib: show_calib_grid._isClicked
                onTrackMouseAction_Signal:(type) => {
                    processMouseActionFromTrack(1, type)
                }
            }

            // Track{
            //     id: cam_main_id_3
            //     property bool  isDoubleClick: false
            //     width: parent.width
            //     height: isDoubleClick ? parent.height : parent.height*0.33
            //     _viewModel: _homeModel.listTrackVM[2]
            //     _numVerticalCell: _homeModel.numVerticalCell[2]
            //     _numHorizontalCell: _homeModel.numHorizontalCell[2]
            //     _isPickTrack: true
            //     // _isShowCalibGrib: show_calib_grid._isClicked
            //     onTrackMouseAction_Signal:(type) => {
            //         processMouseActionFromTrack(2, type)
            //     }
            // }
        }

        // Column {
        //     width: parent.width*0.25
        //     height: parent.height*1.01
        //     spacing: parent.height*0.01
        //     visible: !internal_calibration_table.isDoubleClick
        //     Track{
        //         width: parent.width
        //         height: parent.height
        //         _viewModel: _homeModel.listTrackVM[calib_pos.currentIndex]
        //         _numVerticalCell: _homeModel.numVerticalCell[calib_pos.currentIndex]
        //         _numHorizontalCell: _homeModel.numHorizontalCell[calib_pos.currentIndex]
        //         _isPickTrack: true
        //         _isShowImageViewInfo: false
        //     }
        // }



    }

    Connections{
        target: _viewModel
        function onUpdateCalibCameraPos_Signal(toolHeight, toolWidth, bottomPos1, bottomPos2, topPos){
            calib_tool_height_text.setText(toolHeight)
            calib_tool_width_text.setText(toolWidth)
            table_elevation_bottom_pos_1_text.setText(bottomPos1)
            table_elevation_bottom_pos_2_text.setText(bottomPos2)
            table_elevation_top_pos_text.setText(topPos)
        }

        function onIsShowWaitingCalib(isShow){
            busyAnimation.visible = isShow
        }

        function onOpenConfirmSaveDialog(){
            message_confirm_save_dialog.open()
        }
    }

    MessageDialog {
        id: message_confirm_save_dialog
        title: qsTr("Calibration")
        icon: StandardIcon.Question
        text: qsTr("Calibration is complete\n Would you like to apply the parameters?")
        standardButtons: StandardButton.Yes |StandardButton.No


        onYes: {
            // _viewModel.confirmSaveCalib_Qml_Slot(true)
            message_confirm_save_dialog.close()
            confirm_password.setText("");
            inputPasswordSaveCalibPopUp.open()
        }
        onNo: {
            _viewModel.confirmSaveCalib_Qml_Slot(false)
            message_confirm_save_dialog.close()
        }
    }

    MessageDialog {
        id: wrong_confirm_password_dialog
        title: qsTr("Calibration")
        icon: StandardIcon.Question
        text: qsTr("The password entered is incorrect. Please try again")
        standardButtons: StandardButton.Yes
        onYes: {

        }
    }


    Popup{
        id: inputPasswordSaveCalibPopUp
        width: 350
        height: 150
        modal: true
        focus: true
        anchors.centerIn: parent
        Column {
            width: parent.width
            height: parent.height
            spacing: 10

            Rectangle{
                width: parent.width
                height: parent.height*0.1
                anchors.horizontalCenter: parent.horizontalCenter
                color: "transparent"

            }

            InputMaterialText{
                id: confirm_password
                _width: parent.width*0.8
                _height: parent.height*0.3
                _fontSizeText: _fontSizeText
                anchors.horizontalCenter: parent.horizontalCenter
                _text: ""
                _placeholderText: qsTr("Password")
                _iconSourceOn: "lock"
                _echoMode: TextInput.Password
            }

            Rectangle{
                width: parent.width*0.9
                height: parent.height*0.3
                anchors.horizontalCenter: parent.horizontalCenter
                color: "transparent"

                ButtonMaterialTextHorizontal {
                    width: parent.width*0.45
                    height: width*0.3
                    _size: height*0.8
                    _text: qsTr("OK")
                    _fontFamily: _fontFamily
                    _iconSourceOn: "checkBold"
                    _textRatio: 0.28
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        if(confirm_password.getText() === "engineer")
                        {
                            _viewModel.confirmSaveCalib_Qml_Slot(true)
                            inputPasswordSaveCalibPopUp.close()

                        }
                        else
                        {
                            wrong_confirm_password_dialog.open()
                            _viewModel.confirmSaveCalib_Qml_Slot(false)
                        }
                    }
                }

                ButtonMaterialTextHorizontal {
                    width: parent.width*0.45
                    height: width*0.3
                    _size: height*0.8
                    _textRatio: 0.28
                    _text: qsTr("Cancel")
                    _iconSourceOn: "cancel"
                    _fontFamily: _fontFamily
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        _viewModel.confirmSaveCalib_Qml_Slot(false)
                        inputPasswordSaveCalibPopUp.close()
                    }
                }
            }
        }
    }



}

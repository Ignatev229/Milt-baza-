import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.3 as QDialog
import QtQuick.Controls 1.5 as C1_5
import QtQuick.Controls.Styles 1.4

import "../../Component"

import ConfigView 1.0

Item {
    id: ribbon
    property QtObject _viewModel: QtObject{}

    property color colorSeparator: ConfigView.mainBlueColor
    property double heightRatio: 0.7
    property double iconRatio: 0.35
    property string _fontFamily: ConfigView.fontFamily
    // for update stream btn status
    property var streamBtnStatus: [false, false, false]
    property int currentTrackPicked: 0

    signal pixelRuler_Signal(isOpen: bool)


    function changePixelRulerButtonStatus(isClick){
        pixel_ruler_btn.changeButtonStatus(isClick)
    }

    function updateStreamButtonStatus(trackIdx: int){
        currentTrackPicked = trackIdx
        stream_btn.changeButtonStatus(streamBtnStatus[trackIdx])
    }


    Rectangle{
        anchors.fill: parent
        color: ConfigView.mainWhiteColor

        C1_5.ScrollView {
            id: ribbon_scroll_view
            anchors.fill: parent
            clip: true
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

            verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            flickableItem.flickableDirection : Flickable.VerticalFlick
            flickableItem.boundsBehavior: Flickable.StopAtBounds


            property int buttonWidth: width*0.8
            property int buttonHeight: buttonWidth*heightRatio

            Column{
                width: ribbon_scroll_view.width
                height: ribbon_scroll_view.height*1.1
                spacing: parent.width*0.1
                ButtonMaterialText{
                    width: ribbon_scroll_view.buttonWidth
                    height: ribbon_scroll_view.buttonHeight
                    _size: width*iconRatio
                    _text: qsTr("Load Image")
                    _iconSourceOn: "fileImage"
                    anchors.horizontalCenter: parent.horizontalCenter
                    _fontFamily: ribbon._fontFamily
                    onClicked: {
                        load_image_dialog.folder = "file:///" + _viewModel.oldLoadImagePath
                        load_image_dialog.open()
                    }

                }

                ButtonMaterialText{
                    enabled: !stream_btn._isClicked
                    opacity: enabled ? 1 : 0.5
                    width: ribbon_scroll_view.buttonWidth
                    height: ribbon_scroll_view.buttonHeight
                    _size: width*iconRatio
                    _text: qsTr("Snap")
                    _iconSourceOn: "cameraIris"
                    anchors.horizontalCenter: parent.horizontalCenter
                    _fontFamily: ribbon._fontFamily
                    onClicked: {
                        _viewModel.snap_Qml_Slot()
                    }

                }

                ToggleButtonMaterialText{
                    id: stream_btn
                    width: ribbon_scroll_view.buttonWidth
                    height: ribbon_scroll_view.buttonHeight
                    _size: width*iconRatio
                    _text: qsTr("Stream")
                    _iconSourceOn: "camera"
                    _iconSourceOff: "cameraOff"
                    anchors.horizontalCenter: parent.horizontalCenter
                    _fontFamily: ribbon._fontFamily
                    onClicked: {
                        _viewModel.stream_Qml_Slot(_isClicked)
                        streamBtnStatus[currentTrackPicked] = _isClicked
                    }

                }

                ButtonMaterialText{
                    width: ribbon_scroll_view.buttonWidth
                    height: ribbon_scroll_view.buttonHeight
                    _size: width*iconRatio
                    _text: qsTr("Save Image")
                    _iconSourceOn: "contentSaveAll"
                    anchors.horizontalCenter: parent.horizontalCenter
                    _fontFamily: ribbon._fontFamily
                    onClicked: {
                        save_image_dialog.open()
                    }

                }

                //separator
                Rectangle {
                    width: parent.width
                    height: 10
                    color: "transparent"
                    Rectangle{
                        implicitWidth: parent.width*0.8
                        implicitHeight: 2
                        radius: height/2
                        anchors.centerIn: parent
                        color: colorSeparator
                    }
                }

                ButtonMaterialText{
                    enabled: !inspect_cycle_btn._isClicked && !inspect_folder._isClicked
                    opacity: enabled ? 1 : 0.5
                    width: ribbon_scroll_view.buttonWidth
                    height: ribbon_scroll_view.buttonHeight
                    _size: width*iconRatio
                    _text: qsTr("Inspect")
                    _iconSourceOn: "imageSearch"
                    anchors.horizontalCenter: parent.horizontalCenter
                    _fontFamily: ribbon._fontFamily
                    onClicked: {
                        _viewModel.inspect_Qml_Slot()
                    }
                }


                ToggleButtonMaterialText{
                    id: inspect_cycle_btn
                    enabled: !inspect_folder._isClicked
                    opacity: enabled ? 1 : 0.5
                    width: parent.width*0.8
                    height: width*heightRatio
                    _size: width*iconRatio
                    _text: qsTr("Inspect \nCycle")
                    _iconSourceOn: "eye"
                    _iconSourceOff: "eyeOff"
                    _colorIconHigh: ConfigView.mainWhiteColor
                    anchors.horizontalCenter: parent.horizontalCenter
                    _fontFamily: ribbon._fontFamily
                    onClicked: {
                        _viewModel.inspectCycle_Qml_Slot(_isClicked)
                    }

                }


                ToggleButtonMaterialText{
                    visible: false
                    id: inspect_folder
                    enabled: !inspect_cycle_btn._isClicked
                    opacity: enabled ? 1 : 0.5
                    width: parent.width*0.8
                    height: width*heightRatio
                    _size: width*iconRatio
                    _text: qsTr("Inspect \nFolder")
                    _iconSourceOn: "folderSearch"
                    _iconSourceOff: "folderMultipleImage"
                    anchors.horizontalCenter: parent.horizontalCenter
                    _fontFamily: ribbon._fontFamily
                    onClicked: {
                        if(_isClicked){
                            inspect_folder_image_dialog.open()
                        }
                        else{
                            _viewModel.inspectFolder_Qml_Slot(false, "")
                        }
                    }
                }

                // ToggleButtonMaterialText{
                //     id: inspect_glass_container_shape_btn
                //     enabled: !inspect_cycle_btn._isClicked
                //     opacity: enabled ? 1 : 0.5
                //     width: parent.width*0.8
                //     height: width*heightRatio
                //     _size: width*iconRatio
                //     _text: qsTr("Inspect \nShape")
                //     _iconSourceOn: "shapeOutline"
                //     _iconSourceOff: "shape"
                //     anchors.horizontalCenter: parent.horizontalCenter
                //     _fontFamily: ribbon._fontFamily
                //     onClicked: {
                //         if(_isClicked){
                //             inspect_glass_container_shape_dialog.open()
                //         }
                //         else{
                //             _viewModel.inspectGlassContainerShape_Qml_Slot(false, "")
                //         }
                //     }
                // }

                // ToggleButtonMaterialText{
                //     id: inspect_top_btn
                //     enabled: !inspect_cycle_btn._isClicked
                //     opacity: enabled ? 1 : 0.5
                //     width: parent.width*0.8
                //     height: width*heightRatio
                //     _size: width*iconRatio
                //     _text: qsTr("Inspect \nTop")
                //     _iconSourceOn: "monitorEye"
                //     _iconSourceOff: "monitorEye"
                //     anchors.horizontalCenter: parent.horizontalCenter
                //     _fontFamily: ribbon._fontFamily
                //     onClicked: {
                //         if(_isClicked){
                //             inspect_top_dialog.open()
                //         }
                //         else{
                //             _viewModel.inspectTop_Qml_Slot(false, "")
                //         }
                //     }
                // }


                //separator
                Rectangle {
                    width: parent.width
                    height: 10
                    color: "transparent"
                    Rectangle{
                        implicitWidth: parent.width*0.8
                        implicitHeight: 2
                        radius: height/2
                        anchors.centerIn: parent
                        color: colorSeparator
                    }
                }

                ToggleButtonMaterialText{
                    id: pixel_ruler_btn
                    width: parent.width*0.8
                    height: width*heightRatio
                    _size: width*iconRatio
                    _text: qsTr("Pixel \nRuler")
                    _iconSourceOn: "pencilRuler"
                    _iconSourceOff: "pencilRuler"
                    anchors.horizontalCenter: parent.horizontalCenter
                    _fontFamily: ribbon._fontFamily
                    onClicked: {
                        ribbon.pixelRuler_Signal(_isClicked)
                    }

                }

            }
        }
    }


    QDialog.FileDialog{
        id: load_image_dialog;
        title: qsTr("Select image file");
        folder: "file:///" + _viewModel.oldLoadImagePath
        nameFilters: ["Image Files (*.bmp *.png *.jpg *.jpeg)"];
        selectMultiple: false
        selectExisting: true
        onAccepted: {
            var raw_text = String(load_image_dialog.fileUrl);
            var path = Qt.platform.os === "windows" ?
                        raw_text.substring(8, raw_text.length) :
                        raw_text.substring(7, raw_text.length)
            _viewModel.loadImage_Qml_Slot(path)
            load_image_dialog.close()
        }
    }

    QDialog.FileDialog {
        id: save_image_dialog
        title: qsTr("Select Save Image Path")
        selectMultiple: false
        selectExisting: false
        onAccepted: {
            var raw_text = String(save_image_dialog.fileUrl);
            var path = Qt.platform.os === "windows" ?
                        raw_text.substring(8, raw_text.length) :
                        raw_text.substring(7, raw_text.length)
            _viewModel.saveImage_Qml_Slot(path)
            save_image_dialog.close()
        }
    }

    QDialog.FileDialog{
        id: inspect_folder_image_dialog;
        title: qsTr("Select png image folder");
        selectFolder: true
        onAccepted: {
            var raw_text = String(inspect_folder_image_dialog.folder);
            var path = Qt.platform.os === "windows" ?
                        raw_text.substring(8, raw_text.length) :
                        raw_text.substring(7, raw_text.length)
            _viewModel.inspectFolder_Qml_Slot(true, path)
            inspect_folder_image_dialog.close()
        }
        onRejected: {
            inspect_folder.clicked()
        }
    }

    QDialog.FileDialog{
        id: inspect_glass_container_shape_dialog;
        title: qsTr("Select png image folder");
        selectFolder: true
        onAccepted: {
            var raw_text = String(inspect_glass_container_shape_dialog.folder);
            var path = Qt.platform.os === "windows" ?
                        raw_text.substring(8, raw_text.length) :
                        raw_text.substring(7, raw_text.length)
            _viewModel.inspectGlassContainerShape_Qml_Slot(true, path)
            inspect_glass_container_shape_dialog.close()
        }
        onRejected: {
            inspect_glass_container_shape_btn.clicked()
        }
    }

    QDialog.FileDialog{
        id: inspect_top_dialog;
        title: qsTr("Select png image folder");
        selectFolder: true
        onAccepted: {
            var raw_text = String(inspect_top_dialog.folder);
            var path = Qt.platform.os === "windows" ?
                        raw_text.substring(8, raw_text.length) :
                        raw_text.substring(7, raw_text.length)
            _viewModel.inspectTop_Qml_Slot(true, path)
            inspect_top_dialog.close()
        }
        onRejected: {
            inspect_top_btn.clicked()
        }
    }

    Connections{
        target: _viewModel
        function onInspectFolderStatusChanged_Signal(isClicked){
            if(inspect_folder._isClicked !== isClicked)
                inspect_folder.clicked()
        }

        function onInspectGlassContainerShapeStatusChanged_Signal(isClicked){
            if(inspect_glass_container_shape_btn._isClicked !== isClicked)
                inspect_glass_container_shape_btn.clicked()
        }
        function onInspectTopStatusChanged_Signal(isClicked){
            if(inspect_top_btn._isClicked !== isClicked)
                inspect_top_btn.clicked()
        }
    }
}

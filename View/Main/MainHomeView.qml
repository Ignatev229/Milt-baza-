import QtQuick 2.15
import QtQuick.Controls 2.0

import DataDebugLog 1.0
import DataStatistics 1.0
import ConfigView 1.0

import "../../View"
import "../../View/Dialog"
Item {

    id: main_home_view_id
    width: parent.width
    height: parent.height

    property QtObject _homeModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily

    property int spacing: 5



    QtObject{
        id: internalHomeHomeView
        property bool isDoubleClick: cam_main_id_1.isDoubleClick || cam_main_id_2.isDoubleClick/* || cam_main_id_3.isDoubleClick*/

    }

    function tabSelected (isSelected: bool){
        openPixelRuler (isSelected && ConfigView.isShowPixelRuler)

        defectInforTrack1.visible = cam_main_id_1.isDoubleClick && isSelected 
        defectInforTrack2.visible = cam_main_id_2.isDoubleClick && isSelected 
        // defectInforTrack3.visible = cam_main_id_3.isDoubleClick && isSelected

    }

    function openPixelRuler (isOpen: bool){
        if(isOpen){
            pixel_ruler_dialog.visible = isOpen
        }
        else{
            pixel_ruler_dialog.visible = isOpen
        }
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


            if(cam_main_id_1.isDoubleClick) defectInforTrack1.visible = true
            else defectInforTrack1.visible = false
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


            if(cam_main_id_2.isDoubleClick) defectInforTrack2.visible = true
            else defectInforTrack2.visible = false
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

        //     if(cam_main_id_3.isDoubleClick) defectInforTrack3.visible = true
        //     else defectInforTrack3.visible = false
        // }
    }

    function pickTrackChanged(trackIndex: int){
        if(trackIndex === 0){
            track_id_1._isPickTrack = true
            track_id_2._isPickTrack = false
            // track_id_3._isPickTrack = false
            _homeModel.currentTrackChanged_Qml_Slot(0);
            ribbon.updateStreamButtonStatus(0)
        }
        else if(trackIndex === 1){
            track_id_1._isPickTrack = false
            track_id_2._isPickTrack = true
            // track_id_3._isPickTrack = false
            _homeModel.currentTrackChanged_Qml_Slot(1);
            ribbon.updateStreamButtonStatus(1)
        }
        else if(trackIndex === 2){
            track_id_1._isPickTrack = false
            track_id_2._isPickTrack = false
            // track_id_3._isPickTrack = true
            _homeModel.currentTrackChanged_Qml_Slot(2);
            ribbon.updateStreamButtonStatus(2)
        }
    }

    function processMouseActionFromTrack(trackIndex: int, mouseType: int){
        if(mouseType === ConfigView.MOUSE_ACTION.LEFT_CLICK){
            pickTrackChanged(trackIndex)
        }
        else if(mouseType === ConfigView.MOUSE_ACTION.RIGHT_CLICK){

        }
        else if(mouseType === ConfigView.MOUSE_ACTION.LEFT_DOUBLE_CLICK){
            zoomInOneTrack(trackIndex)
        }
        else if(mouseType === ConfigView.MOUSE_ACTION.RIGHT_DOUBLE_CLICK){

        }
    }




    Rectangle{
        anchors.fill: parent
        color: ConfigView.mainWhiteColor

        Column{
            width: parent.width*0.921
            height: parent.height
            spacing: parent.width*0.002
            anchors.right: parent.right
            Row {
                width: parent.width
                height: internalHomeHomeView.isDoubleClick ? parent.height : parent.height*0.65
                spacing: main_home_view_id.spacing
                Rectangle{
                    id: cam_main_id_1
                    width: isDoubleClick ? parent.width : parent.width/2 - main_home_view_id.spacing
                    height: parent.height
                    property bool  isDoubleClick: false
                    Track{
                        id: track_id_1
                        width: parent.width
                        height: parent.height
                        _viewModel: _homeModel.listTrackVM[0]
                        _numVerticalCell: _homeModel.numVerticalCell[0]
                        _numHorizontalCell: _homeModel.numHorizontalCell[0]
                        _isPickTrack: true
                        onTrackMouseAction_Signal:(type) => {
                            processMouseActionFromTrack(0, type)
                        }
                        onUpdateDataToPixelRuler_Signal: (prePosX, prePosY, posX, posY) => {
                            pixel_ruler_view.updateData(prePosX, prePosY, posX, posY, 0)
                        }
                    }
                }

                Rectangle{
                    id: cam_main_id_2
                    width: isDoubleClick ? parent.width : parent.width/2 - main_home_view_id.spacing
                    height: parent.height
                    property bool  isDoubleClick: false
                    Track{
                        id: track_id_2
                        width: parent.width
                        height: parent.height
                        _viewModel: _homeModel.listTrackVM[1]
                        _numVerticalCell: _homeModel.numVerticalCell[1]
                        _numHorizontalCell: _homeModel.numHorizontalCell[1]
                        onTrackMouseAction_Signal:(type) => {
                            processMouseActionFromTrack(1, type)
                        }
                        onUpdateDataToPixelRuler_Signal: (prePosX, prePosY, posX, posY) => {
                            pixel_ruler_view.updateData(prePosX, prePosY, posX, posY, 1)
                        }
                    }

                }

                // Rectangle{
                //     id: cam_main_id_3
                //     width: isDoubleClick ? parent.width : parent.width/3 - main_home_view_id.spacing
                //     height: parent.height
                //     property bool  isDoubleClick: false
                //     Track{
                //         id: track_id_3
                //         width: parent.width
                //         height: parent.height
                //         _viewModel: _homeModel.listTrackVM[2]
                //         _numVerticalCell: _homeModel.numVerticalCell[2]
                //         _numHorizontalCell: _homeModel.numHorizontalCell[2]
                //         onTrackMouseAction_Signal:(type) => {
                //             processMouseActionFromTrack(2, type)
                //         }
                //         onUpdateDataToPixelRuler_Signal: (prePosX, prePosY, posX, posY) => {
                //             pixel_ruler_view.updateData(prePosX, prePosY, posX, posY, 2)
                //         }
                //     }
                // }
            }

            Row{
                width: parent.width
                height: parent.height*0.348
                spacing: main_home_view_id.spacing

                StatisticView{
                    width: parent.width*2/3 - main_home_view_id.spacing
                    height: parent.height
                    _fontSizeText: 9
                    _model: StatisticsModel{
                        list: statisticsVM
                    }
                }

                Rectangle {
                    width: parent.width/3
                    height: parent.height
                    color: "transparent"

                    DebugLogView{
                        id: plc_communication_log
                        visible: false
                        width: parent.width
                        height: parent.height
                        _fontSizeText: 9
                        _headerName: qsTr("PLC Communication Log")
                        _model: DebugLogModel{
                            list: plcCommunicationLogVM
                        }
                        onSwapDebugLogTab_Signal: () => {
                            plc_communication_log.visible = false;
                            debug_log_view.visible = true;
                        }
                    }

                    DebugLogView{
                        id: debug_log_view
                        width: parent.width
                        height: parent.height
                        _fontSizeText: 9
                        _model: DebugLogModel{
                            list: debugLogVM
                        }
                        onSwapDebugLogTab_Signal: () => {
                            plc_communication_log.visible = true;
                            debug_log_view.visible = false;
                        }
                    }


                }



            }
        }


        RibbonView{
            id: ribbon
            width: parent.width*0.075
            height: parent.height
            anchors.left: parent.left
            _viewModel: ribbonVM
            onPixelRuler_Signal: (isOpen) => {
                pixel_ruler_dialog.visible = isOpen
                ConfigView.isShowPixelRuler = isOpen
            }
        }
    }

    readonly property int defectInforWidth: 800
    readonly property int defectInforHeight: 600

    Popup {
        id: defectInforTrack1
        width: defectInforWidth
        height: defectInforHeight
        modal: false
        closePolicy: Popup.NoAutoClose
        y: 200
        x: 200

        focus: true

        contentItem: DefectInforDlg {
            id: defectInforDlgCam1
            titleDescription: "Defect Infor Cam 1"
            anchors.fill: parent

            onMoveByTitleBar: {
                defectInforTrack1.x += xPos
                defectInforTrack1.y += yPos
            }
        }
    }

    Popup {
        id: defectInforTrack2
        width: defectInforWidth
        height: defectInforHeight
        modal: false
        closePolicy: Popup.NoAutoClose
        y: 200
        x: 200

        focus: true

        contentItem: DefectInforDlg {
            id: defectInforDlgCam2
            titleDescription: "Defect Infor Cam 2"
            anchors.fill: parent

            onMoveByTitleBar: {
                defectInforTrack2.x += xPos
                defectInforTrack2.y += yPos
            }
        }
    }

    Popup {
        id: defectInforTrack3
        width: defectInforWidth
        height: defectInforHeight
        modal: false
        closePolicy: Popup.NoAutoClose
        y: 200
        x: 200

        focus: true

        contentItem: DefectInforDlg {
            id: defectInforDlgCam3
            titleDescription: "Defect Infor Cam 3"
            anchors.fill: parent

            onMoveByTitleBar: {
                defectInforTrack3.x += xPos
                defectInforTrack3.y += yPos
            }
        }
    }

    Popup {
        id: pixel_ruler_dialog
        width: 400
        height: 200
        modal: false
        focus: true
        closePolicy: Popup.CloseOnEscape
        y: 0
        x: parent.y
        contentItem: PixelRulerView {
            id: pixel_ruler_view
            anchors.fill: parent
            _fontSizeText: 10
        }

        background: Rectangle {
            opacity: 0.7
            implicitWidth: parent.width
            implicitHeight: parent.height
            border.color: "transparent"
            color: "red"
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#202020" }
                GradientStop { position: 0.5; color: "#2E2F30" }
                GradientStop { position: 1.0; color: "#494A4B" }
            }
        }


        onClosed: {
            ribbon.changePixelRulerButtonStatus(false)
            ConfigView.isShowPixelRuler = false
        }
    }

    Connections{
        target: _homeModel
        function onStartToChangeLanguage_Signal(){
            pixel_ruler_view.startToChangeLanguage()
        }
    }

    Connections {
        target: _homeModel
        onAddDataToDefectInforSignal: {
            
            if(trackIndex === 0) {
                  defectInforDlgCam1.addData(strHeader, strDescription, strPixelValue, strmmValue)
            } 
            else if(trackIndex === 1) {
                  defectInforDlgCam2.addData(strHeader, strDescription, strPixelValue, strmmValue)
            } 
            else if(trackIndex === 2) {
                defectInforDlgCam3.addData(strHeader, strDescription, strPixelValue, strmmValue)
            }
            

        //int trackIndex, QString strHeader, QString strDescription, QString strValue, bool isClear
        }

        onClearDataToDefectInforSignal: {
            defectInforDlgCam1.clearData()
            defectInforDlgCam2.clearData()
            defectInforDlgCam3.clearData()
        }
    }

}

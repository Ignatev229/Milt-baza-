import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4 as QC14
import QtQuick.Controls.Styles 1.4 as QCS14
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.5 as C1_5
import QtQuick.Layouts 1.0

import ConfigView 1.0
import DataListString 1.0
import DataDebugLog 1.0


import "../../View"
import "../../Component"
import "../../View/Dialog"
import "../../View/Main"

Item {

    id: main_home_view_id
    width: parent.width
    height: parent.height

    property QtObject _homeModel: QtObject{}
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property int _fontSize: 12
    property color _textColor: ConfigView.mainBlueColor
    property int spacing: 5

    property int _numberRow: 8
    property int _numberCol: 7

    function getColor(index){
        if(index === 0){
            return "#D1D1D1" // empty
        }
        else if(index === 1){
            return ConfigView.acceptSignalColor // pass
        }
        if(index === 2){
            return ConfigView.warningSignalColor // warning
        }
        if(index === 3){
            return ConfigView.cancelSignalColor // fail
        }
        return "#D1D1D1" // empty
    }


    ListModel {
        id: _setoutModel
    }

    QtObject{
        id: internalHomeHomeView
        property bool isDoubleClick: cam_main_id_1.isDoubleClick || cam_main_id_2.isDoubleClick /*|| cam_main_id_3.isDoubleClick*/

    }

    function getcurrentJobIndex(){
        return job_cbb.currentIndex
    }

    function getcurrentJobText(){
        return job_cbb.currentText
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

    function pickTrackChanged(trackIndex: int){
        if(trackIndex === 0){
            track_id_1._isPickTrack = true
            track_id_2._isPickTrack = false
            // track_id_3._isPickTrack = false
            _homeModel.currentTrackChanged_Qml_Slot(0);
        }
        else if(trackIndex === 1){
            track_id_1._isPickTrack = false
            track_id_2._isPickTrack = true
            // track_id_3._isPickTrack = false
            _homeModel.currentTrackChanged_Qml_Slot(1);
        }
        // else if(trackIndex === 2){
        //     track_id_1._isPickTrack = false
        //     track_id_2._isPickTrack = false
        //     track_id_3._isPickTrack = true
        //     _homeModel.currentTrackChanged_Qml_Slot(2);
        // }
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

    function initSetoutModel(){
        _setoutModel.clear()
        for(var i = 0; i < _numberCol; i++){
            for(var j = 0; j < _numberRow; j++){
                _setoutModel.append({
                    "mold": "",
                    "value": 0,
                })
            }
        }
    }

    Rectangle{
        anchors.fill: parent
        color: ConfigView.mainWhiteColor

        Column{
            width: parent.width
            height: parent.height
            spacing: parent.width*0.002
            anchors.right: parent.right
            Row {
                width: parent.width
                height: internalHomeHomeView.isDoubleClick ? parent.height : parent.height*0.48
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
                            pixel_ruler_view.updateData(prePosX, prePosY, posX, posY)
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
                            pixel_ruler_view.updateData(prePosX, prePosY, posX, posY)
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
                //     }
                // }
            }

            Row{
                width: parent.width*0.98
                height: parent.height*0.05
                spacing: main_home_view_id.spacing*2.5
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: qsTr("Job") + ": "
                    width: contentWidth*1
                    font.pointSize: main_home_view_id._fontSize
                    color: _textColor
                    font.family: _fontFamily
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

                ComboBoxCustom{
                    id: job_cbb
                    _model: ListStringModel{
                        list: listRecipeModel
                    }
                    width: parent.width*0.13
                    height: parent.height
                    _fontSize: main_home_view_id._fontSize
                    anchors.verticalCenter: parent.verticalCenter
                    _backgroundDefaultColor: ConfigView.addGrayColor
                    currentIndex: 0
                    onCurrentTextChanged: {
                        if(!recipeManagementVM.isEnableSelectRecipeSignal)
                            return;
                        _viewModel.loadRecipe_Qml_Slot(currentText)
                    }
                }

                Rectangle {
                    width: parent.width*0.005
                    height: parent.height
                    color:'transparent'
                }

                ButtonMaterialTextHorizontal{
                    id: edit_btn
                    width: parent.width*0.1
                    height: parent.height*0.9
                    _size: height*0.8
                    _text: qsTr("Edit")
                    _iconSourceOn: "contentSaveEdit"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: main_home_view_id._fontFamily
                    _textRatio: 0.32
                    onClicked: {
                        setout_grid.enabled = true;

                    }
                }

                ButtonMaterialTextHorizontal{
                    width: edit_btn.width
                    height: edit_btn.height
                    _size: height*0.8
                    _text: qsTr("Save")
                    _iconSourceOn: "contentSave"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: main_home_view_id._fontFamily
                    _textRatio: edit_btn._textRatio
                    onClicked: {
                        setout_grid.enabled = false;
                        _viewModel.saveMoldNumbers(setout_grid.getNumberMolds())
                    }
                }

                ButtonMaterialTextHorizontal{
                    width: edit_btn.width
                    height: edit_btn.height
                    _size: height*0.8
                    _text: qsTr("Clear All")
                    _iconSourceOn: "broom"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: main_home_view_id._fontFamily
                    _textRatio: edit_btn._textRatio
                    onClicked: {
                        message_dialog.openDialog(qsTr("Clear All Of Containers"),
                                                qsTr("Are you sure you want to clear all of the containers?"),
                                                StandardIcon.Question, StandardButton.Yes | StandardButton.No)
                    }
                }

                ButtonMaterialTextHorizontal{
                    width: edit_btn.width
                    height: edit_btn.height
                    _size: height*0.8
                    _text: qsTr("Machine \nInitialization")
                    _iconSourceOn: "home"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: main_home_view_id._fontFamily
                    _textRatio: edit_btn._textRatio
                    onClicked: {
                        feederAndPushersVM.machineHomePosition_Qml_Slot();
                    }
                }

                ButtonMaterialTextHorizontal{
                    width: edit_btn.width
                    height: edit_btn.height
                    _size: height*0.8
                    _text: qsTr("Reset")
                    _iconSourceOn: "alarmLight"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: main_home_view_id._fontFamily
                    _textRatio: edit_btn._textRatio
                    onClicked: {
                        _viewModel.resetAlarm_Qml_Slot()
                    }
                }

                ButtonMaterialTextHorizontal{
                    width: edit_btn.width
                    height: edit_btn.height
                    _size: height*0.8
                    _text: qsTr("Safety \nRelay Reset")
                    _iconSourceOn: "restart"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: main_home_view_id._fontFamily
                    _textRatio: edit_btn._textRatio
                    onClicked: {
                        _viewModel.safetyRelayReset_Qml_Slot()
                    }
                }

                Rectangle {
                    width: edit_btn.width
                    height: edit_btn.height
                    color: _viewModel.highPressureStatus === 0 ? ConfigView.warningSignalColor : ConfigView.acceptSignalColor
                    radius: 10
                    anchors.verticalCenter: parent.verticalCenter
                    Text {
                        text: qsTr("High Presssure")
                        font.pointSize: main_home_view_id._fontSize
                        color: _viewModel.highPressureStatus === 0 ? _textColor : ConfigView.mainWhiteColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.horizontalAlignment
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

            }

            Rectangle {

                    width: parent.width
                    height: parent.height * 0.467
                    color: ConfigView.mainBlueColor

                Row{
                    width: parent.width
                    height: parent.height
                    spacing: main_home_view_id.spacing*2
                    anchors.horizontalCenter: parent.horizontalCenter



                    GridView{
                        id: setout_grid
                        enabled: false
                        opacity: enabled ? 1 : 0.8
                        property int padding: parent.width*0.005
                        width: parent.width*0.77
                        height: parent.height
                        focus: true
                        model: _setoutModel
                        anchors.verticalCenter: parent.verticalCenter
                        cellHeight: height/_numberRow
                        cellWidth: width/_numberCol
                        clip: true
                        interactive: false
                        delegate:contacts_delegate
                        currentIndex: 0
                        cacheBuffer: setout_grid.cellHeight * setout_grid.numRow // Need to calculator with equation (_numVerticalCell_old*(_numVerticalCell_old*_numHorizontalCell_old)/_numVerticalCell_new)
                        flow: GridView.FlowLeftToRight
                        highlightRangeMode: GridView.ApplyRange
                        snapMode: GridView.SnapOneRow

                        function getNumberMolds(){
                            var data = []
                            for (var i = 0; i < _setoutModel.count; i++) {
                                data.push(_setoutModel.get(i).mold); // Get each element's name
                            }
                            return data;
                        }

                        Component{
                            id: contacts_delegate
                            Item {
                                width: setout_grid.cellWidth
                                height: setout_grid.cellHeight

                                Rectangle{
                                    width: setout_grid.cellWidth - setout_grid.padding
                                    height: setout_grid.cellHeight - setout_grid.padding
                                    color: getColor(value)
                                    radius: 5
                                    anchors{
                                        verticalCenter: parent.verticalCenter
                                        horizontalCenter: parent.horizontalCenter
                                    }
                                }

                                QC14.TextField{
                                    id: text_id
                                    text: mold
                                    textColor: "black"
                                    font.family: _fontFamily
                                    font.pointSize: _fontSize
                                    anchors.centerIn: parent
                                    width: setout_grid.cellWidth - setout_grid.padding
                                    height: parent.height*0.8
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    echoMode: TextInput.Normal
                                    validator: RegExpValidator{regExp: /\d+/}
                                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                                    style: QCS14.TextFieldStyle {
                                        background: Rectangle {
                                            color: "transparent"
                                        }
                                    }

                                    onTextChanged: {
                                        _setoutModel.set(index, {"mold": text_id.text})
                                    }
                                }
                            }
                        }
                    }

                    Rectangle {
                        width: parent.width*0.23 - parent.spacing
                        height: parent.height
                        color: "transparent"

                        DebugLogView{
                            id: debug_log_view
                            width: parent.width
                            height: parent.height
                            _fontSizeText: _fontSize - 2
                            _headerHeight: height*0.1
                            _model: DebugLogModel{
                                list: debugLogVM
                            }
                            onSwapDebugLogTab_Signal: () => {
                                plc_communication_log.visible = true;
                                debug_log_view.visible = false;
                            }
                        }

                        DebugLogView{
                            id: plc_communication_log
                            width: parent.width
                            height: parent.height
                            _fontSizeText: _fontSize - 2
                            _headerHeight: height*0.1
                            _headerName: qsTr("PLC Communication Log")
                            _model: DebugLogModel{
                                list: plcCommunicationLogVM
                            }
                            onSwapDebugLogTab_Signal: () => {
                                plc_communication_log.visible = false;
                                debug_log_view.visible = true;
                            }
                        }
                    }
                }
            }
        }

    }

    Connections {
        target: _viewModel

        function onInitSetoutMoldNumber_Signal(dataNumber, dataResult) {
            if(dataNumber.length === 0){
                initSetoutModel()
                return
            }
            for(var i = 0; i < dataNumber.length; i++){
                _setoutModel.set(i, {"mold": dataNumber[i], "value": dataResult[i]})
            }
        }

        function onUpdateMoldNumberResult_Signal(result, moldIndex) {
            _setoutModel.set(moldIndex, {"value": result})
        }

        function onSetCurrentJobName_Signal(index) {
            job_cbb.currentIndex = index
        }

    }

    DialogView {
        id: message_dialog
        onButtonClicked_Signal: (buttonType)=>{

            if(buttonType === StandardButton.Yes){
                // clear on c++
                main_home_view_id._viewModel.clearAllContainers_Qml_Slot();
                //
                initSetoutModel();
            }
            else if(buttonType === StandardButton.No){

            }
        }
    }

    Component.onCompleted: {
        initSetoutModel()
    }

}

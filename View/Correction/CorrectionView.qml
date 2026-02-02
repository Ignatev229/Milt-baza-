import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3


import ConfigView 1.0

import "../../Component/MaterialDesign"
import "../../Component"
import "../../View"

Item {
    id: correction_view_id
    width: parent.width
    height: parent.height
    property QtObject _viewModel: QtObject{}
    property QtObject _homeModel: mainHomeVM
    property string _fontFamily: ConfigView.fontFamily
    property int _fontSize: 12
    property color _textColor: ConfigView.mainBlueColor

    property int _currentDefectIdxSelected: -1

    ListModel {
        id: source_model
        ListElement { idx: 7; displayText: "F"}
        ListElement { idx: 8; displayText: "A"}
        ListElement { idx: 9; displayText: "T"}
        ListElement { idx: 10; displayText: "E"}
        ListElement { idx: 11; displayText: "D"}
        ListElement { idx: 12; displayText: "B"}
        // ListElement { idx: 13; displayText: "S"}
        ListElement { idx: 14; displayText: "H"}
        ListElement { idx: 15; displayText: "PlugT"}
        ListElement { idx: 16; displayText: "PlugT1"}
        ListElement { idx: 17; displayText: "D Angle"}
    }

    ListModel {
        id: dest_model
    }

    function moveItem(source, dest, index)
    {
        var item = source.get(index)
        // add item to dest
        var indices = item.idx
        var name = item.displayText

        if(dest.count === 0)
        {
            dest.append({idx: indices, displayText: name})
            source.remove(index, 1)
            return
        }

        for (var i=0; i < dest.count; i++){
            if(indices < dest.get(i).idx)
            {
                dest.insert(i, {idx: indices, displayText: name})
                source.remove(index, 1)
                return
            }
        }
        dest.append({idx: indices, displayText: name})
        source.remove(index, 1)
        return
    }

    Column {
        id: correction_layout
        width: parent.width*0.98
        height: parent.height*0.92
        anchors.centerIn: parent
        spacing: parent.width*0.01

        Row {
            width: parent.width
            height: parent.height*0.65
            spacing: width*0.02

            Track{
                width: parent.width*0.5
                height: parent.height
                _viewModel: _homeModel.listTrackVM[1]
                _numVerticalCell: _homeModel.numVerticalCell[1]
                _numHorizontalCell: _homeModel.numHorizontalCell[1]
                _isPickTrack: true
                onTrackMouseAction_Signal:(type) => {
                }
            }

            ListItemView {
                id: source_list_view
                width: parent.width*0.15
                height: parent.height
                _dataModel: source_model
            }

            Column {
                width: parent.width*0.05
                height: parent.height*0.5
                anchors.verticalCenter: parent.verticalCenter
                spacing: parent.height*0.3

                ButtonMaterial{
                    _width: parent.width*0.7
                    _height: parent.height*0.2
                    _size: _height*0.9
                    _iconSourceOn: "arrowRightBold"
                    _colorBGDefault: ConfigView.addLightBlueColor
                    _colorBGMouseOver: ConfigView.mainWhiteColor
                    _colorBGHigh: ConfigView.mainBlueColor
                    _colorBorder: ConfigView.addLightBlueColor
                    _colorIconHigh: ConfigView.mainBlueColor
                    _colorIconMouseOver: ConfigView.addLightBlueColor
                    _colorIconDefault: ConfigView.mainWhiteColor
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        moveItem(source_model, dest_model, source_list_view.getIndex())
                    }
                }

                ButtonMaterial{
                    _width: parent.width*0.7
                    _height: parent.height*0.2
                    _size: _height*0.9
                    _iconSourceOn: "arrowLeftBold"
                    _colorBGDefault: ConfigView.addLightBlueColor
                    _colorBGMouseOver: ConfigView.mainWhiteColor
                    _colorBGHigh: ConfigView.mainBlueColor
                    _colorBorder: ConfigView.addLightBlueColor
                    _colorIconHigh: ConfigView.mainBlueColor
                    _colorIconMouseOver: ConfigView.addLightBlueColor
                    _colorIconDefault: ConfigView.mainWhiteColor
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        moveItem(dest_model, source_model, dest_list_view.getIndex())
                    }
                }
            }

            ListItemView {
                id: dest_list_view
                width: parent.width*0.15
                height: parent.height
                _dataModel: dest_model
                onCurrentIndexChanged_Signal: (idx) => {
                    _viewModel.currentDefectChanged_Qml_Slot(idx)
                    _currentDefectIdxSelected = idx
                }
            }

            Rectangle {
                width: parent.width*0.07
                height: parent.height
                color: "transparent"


                ButtonMaterialTextHorizontal{
                    height: parent.height*0.1
                    width: parent.width
                    _size: height*0.8
                    _text: qsTr("Test")
                    _iconSourceOn: "tapeMeasure"
                    _colorIconDefault: ConfigView.addThinBlueColor
                    _colorIconMouseOver: _colorIconDefault
                    _colorIconHigh: ConfigView.mainBlueColor
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: ConfigView.mainBlueColor
                    _textRatio: 0.3
                    onClicked: {
                        var indeces = []
                        for (var i=0; i < dest_model.count; i++){
                            indeces.push(dest_model.get(i).idx)
                        }
                        waitTableMoveCompletePopUp.openDialog()
                        _viewModel.test_Qml_Slot(indeces)
                    }
                }

            }

        }

        Rectangle {
            width: parent.width
            height: parent.height*0.2
            radius: 5
            color: "transparent"
            border.width: 2
            border.color: "#7F7F7F"

            Column {
                width: parent.width*0.47
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.02

                Row {
                    width: parent.width
                    height: parent.height/3

                    Text {
                        text: qsTr("Current Value") + ": "
                        width: parent.width*0.4
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        text: qsTr("Max") + ": "
                        width: parent.width*0.1
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: max_value_text
                        text: ""
                        width: parent.width*0.23
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        text: qsTr("Min") + ": "
                        width: parent.width*0.1
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: min_value_text
                        text: ""
                        width: parent.width*0.2
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Row {
                    width: parent.width
                    height: parent.height/3

                    Text {
                        text: qsTr("Goal") + ": "
                        width: parent.width*0.73
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }


                    InputText{
                        id: goal_value_text
                        enabled: false
                        opacity: enabled ? 1 : 0.5
                        _width: parent.width*0.27
                        _height: parent.height*0.8
                        _fontSizeText: _fontSize
                        _text: "0"
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                        onTextChanged_Signals: (value) => {
                            _viewModel.parameterChanged_Qml_Slot(goal_value_text.getText(),
                                                                 distance_to_bottom_text.getText(),
                                                                 height_measurement_region_text.getText())
                        }
                    }
                }

                Row {
                    width: parent.width
                    height: parent.height/3

                    Text {
                        text: (_currentDefectIdxSelected === 14 ? qsTr("The Diameter to search for") : qsTr("Distance to bottom of Measurement Region")) + ": "
                        width: parent.width*0.73
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }


                    InputText{
                        id: distance_to_bottom_text
                        enabled: false
                        opacity: enabled ? 1 : 0.5
                        _width: parent.width*0.27
                        _height: parent.height*0.8
                        _fontSizeText: _fontSize
                        _text: "0"
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                        onTextChanged_Signals: (value) => {
                            _viewModel.parameterChanged_Qml_Slot(goal_value_text.getText(),
                                                                 distance_to_bottom_text.getText(),
                                                                 height_measurement_region_text.getText())
                        }
                    }
                }

            }


            Column {
                width: parent.width*0.47
                height: parent.height
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.02

                Rectangle {
                    width: parent.width*0.8
                    height: parent.height/3
                    color: "transparent"

                    ButtonMaterial{
                        _width: _height
                        _height: parent.height*0.8
                        _size: _height
                        _iconSourceOn: "plusBox"
                        _colorBGDefault: "transparent"
                        _colorBGMouseOver: ConfigView.mainBlueColor
                        _colorBGHigh: ConfigView.mainBlueColor
                        _colorBorder: "transparent"
                        _colorIconHigh: ConfigView.mainBlueColor
                        _colorIconDefault: ConfigView.addLightBlueColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        onClicked: {
                            height_measurement_region_text.setText((Number(height_measurement_region_text.getText()) + 0.01).toFixed(2))
                        }
                    }
                }

                Row {
                    width: parent.width
                    height: parent.height/3


                    Text {
                        text: qsTr("Height of Measurement Region") + ": "
                        width: parent.width*0.43
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }


                    InputText{
                        id: height_measurement_region_text
                        _width: parent.width*0.27
                        _height: parent.height*0.8
                        _fontSizeText: _fontSize
                        _text: "0"
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        _reg : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                        onTextChanged_Signals: (value) => {
                            _viewModel.parameterChanged_Qml_Slot(goal_value_text.getText(),
                                                                 distance_to_bottom_text.getText(),
                                                                 height_measurement_region_text.getText())
                        }
                    }
                }

                Rectangle {
                    width: parent.width*0.8
                    height: parent.height/3
                    color: "transparent"
                    ButtonMaterial{
                        _width: _height
                        _height: parent.height*0.8
                        _size: _height
                        _iconSourceOn: "minusBox"
                        _colorBGDefault: "transparent"
                        _colorBGMouseOver: ConfigView.mainBlueColor
                        _colorBGHigh: ConfigView.mainBlueColor
                        _colorBorder: "transparent"
                        _colorIconHigh: ConfigView.mainBlueColor
                        _colorIconDefault: ConfigView.addLightBlueColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        onClicked: {
                            height_measurement_region_text.setText((Number(height_measurement_region_text.getText()) - 0.01).toFixed(2))
                        }
                    }
                }
            }

        }

        Row {
            width: parent.width
            height: parent.height*0.1

            Rectangle {
                height: parent.height
                width: parent.width*0.28
                color: "transparent"
            }

            ButtonMaterialTextHorizontal{
                height: parent.height*0.9
                width: parent.width*0.12
                _size: height*0.8
                _text: qsTr("Save")
                _iconSourceOn: "contentSave"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: correction_view_id._fontFamily
                _textRatio: 0.3
                onClicked: {
                    _viewModel.saveSetting_Qml_Slot(true)
                }
            }

            Rectangle {
                height: parent.height
                width: parent.width*0.2
                color: "transparent"
            }

            ButtonMaterialTextHorizontal{
                height: parent.height*0.9
                width: parent.width*0.12
                _size: height*0.8
                _text: qsTr("Cancel")
                _iconSourceOn: "cancel"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: correction_view_id._fontFamily
                _textRatio: 0.3
                onClicked: {
                    _viewModel.saveSetting_Qml_Slot(false)
                }
            }
        }
    }


    Popup{
        id: waitTableMoveCompletePopUp
        width: 350
        height: 200
        modal: true
        focus: true
        anchors.centerIn: parent
        function openDialog(){
            busyAnimation.visible = true
            busyAnimation.running = true
            waitTableMoveCompletePopUp.open()
        }
        Column {
            width: parent.width
            height: parent.height
            spacing: 10

            Text {
                text: qsTr("Wait for Table movement to complete")
                width: parent.width
                font.pointSize: _fontSize
                color: _textColor
                font.family: _fontFamily
                verticalAlignment: Text.AlignVCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            BusyIndicator {
                id: busyAnimation
                visible: false
                anchors.horizontalCenter: parent.horizontalCenter
                width: height
                height: parent.height*0.55
                running: visible
            }

            ButtonMaterialTextHorizontal {
                width: parent.width*0.3
                height: parent.height*0.2
                _size: height*0.8
                _textRatio: 0.28
                _text: qsTr("Cancel")
                _iconSourceOn: "cancel"
                _colorIconDefault: ConfigView.cancelSignalColor
                _colorIconMouseOver: _colorIconDefault
                _colorIconHigh: ConfigView.cancelSignalColor
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    _viewModel.cancelWaitTableMoveComplete()
                    // waitTableMoveCompletePopUp.close()
                }
            }
        }
    }


    Connections {
        target: _viewModel

        function onUpdateDataUI(min, max, goal, distanceBottomRegion, heightBottomRegion)
        {
            min_value_text.text = min.toFixed(2)
            max_value_text.text = max.toFixed(2)
            goal_value_text.setText(goal)
            distance_to_bottom_text.setText(distanceBottomRegion)
            height_measurement_region_text.setText(heightBottomRegion)
        }

        function onCloseWaitTableMoveComplete()
        {
            waitTableMoveCompletePopUp.close()
        }
    }

}
